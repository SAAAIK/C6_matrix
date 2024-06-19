FROM srzzumix/googletest:latest

COPY ./src/ /code/src/

RUN apt update && apt install -y valgrind check

WORKDIR /code/src/
ENTRYPOINT ["make", "vg"]