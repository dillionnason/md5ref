CC = gcc

CFLAGS = -Wextra -Wall -O2

TARGET = md5

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

all: ${BIN} ${TARGET}

${TARGET}: ${OBJ}
	${CC} -o ${BIN}/${TARGET} ${OBJ} ${CFLAGS}

${BIN}:
	mkdir -p ${BIN}

clean:
	rm -rf ${BIN} ${OBJ}
