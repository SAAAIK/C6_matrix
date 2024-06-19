CC = gcc
CC_FLAGS = -Wall -Werror -Wextra -std=c11
LIB_NAME = s21_matrix
CODE_PATH = ./code
TESTS_PATH = ./tests
COMMON_PATH = ./common
BUILD_PATH = ./build
TEST= tests.sh
TEST_FLAGS = -std=c11 -g
GCOVFLAGS = -L. -l$(LIB_NAME) --coverage
OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck 
endif

UTIL = -fsanitize=address

TEST_COMPILE = $(CC) $(CC_FLAGS) $(TEST_FLAGS) tests/test*.c lib$(LIB_NAME).a $(CHECK_FLAGS) -L. -l$(LIB_NAME)

all: style test clean

peer: gcov_report

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM debug *.txt $(TESTS_PATH)/make* ./report/*

style:
	cp ../materials/linters/.clang-format .
	clang-format -i $(CODE_PATH)/*.c  ./*.h $(TESTS_PATH)/*.c $(TESTS_PATH)/*.h $(COMMON_PATH)/*.c $(COMMON_PATH)/*.h
	clang-format -n $(CODE_PATH)/*.c  ./*.h $(TESTS_PATH)/*.c $(TESTS_PATH)/*.h $(COMMON_PATH)/*.c $(COMMON_PATH)/*.h

leaks: clean $(LIB_NAME).a
	$(TEST_COMPILE)
	leaks -atExit -- ./a.out
	make clean

vg:	clean $(LIB_NAME).a
	$(TEST_COMPILE)
	valgrind --tool=memcheck --leak-check=yes  ./a.out
	make clean
	
good: clean all test
	sleep 3
	clear

build:
	gcc $(CC_FLAGS) $(CODE_PATH)/common.c $(CODE_PATH)/s21_decimal.c  $(CODE_PATH)/s21_div_big.c $(CODE_PATH)/s21_is* $(CODE_PATH)/s21_from_decimal_to_int.c $(CODE_PATH)/s21_truncate* $(CODE_PATH)/fast_code.c -lm
	./a.out

rebuild: clean all


test: $(LIB_NAME).a
	$(TEST_COMPILE)
	-./a.out
	make clean

$(LIB_NAME).a: $(LIB_NAME).o
	ar rcs lib$(LIB_NAME).a *.o
	rm -rf *.o
	ranlib lib$(LIB_NAME).a
	cp lib$(LIB_NAME).a $(LIB_NAME).a
	cp lib$(LIB_NAME).a l$(LIB_NAME).a

$(LIB_NAME).o:  
	$(CC) $(CC_FLAGS) -c $(COMMON_PATH)/*.c $(CODE_PATH)/*.c 

gcov_report: clean
	#$(CC) $(CC_FLAGS) -c $(CODE_PATH)/s21*.c $(COMMON_PATH)/*.c  $(GCOVFLAGS)
	#$(CC) -c $(CODE_PATH)/s21*.c $(GCOVFLAGS)
	$(CC) -c $(CODE_PATH)/*.c $(COMMON_PATH)/*.c $(GCOVFLAGS)
	ar rcs lib$(LIB_NAME).a *.o
	rm -rf *.o
	ranlib lib$(LIB_NAME).a
	cp lib$(LIB_NAME).a $(LIB_NAME).a
	cp lib$(LIB_NAME).a l$(LIB_NAME).a
	gcc $(TEST_FLAGS) $(TESTS_PATH)/test*.c lib$(LIB_NAME).a $(CHECK_FLAGS) $(GCOVFLAGS)
	-./a.out
	lcov -t a.out -o all_test.info -c -d .
	genhtml -o report all_test.info
	rm -rf *.gcda *.gcno ./a.out *.info $(TESTS_PATH)/*.a $(TESTS_PATH)/*.o ./*.a
	#-open ./report/index.html
	#vivaldi ./report/index.html