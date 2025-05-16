NAME=s21_grep
CC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11 -g 
rebuild: clean all

all: ${NAME}

${NAME}:
	${CC} ${CFLAGS} ${NAME}.c -o ${NAME}
clean:
	rm -fr ${NAME}
test:
	bash t_grep.sh
clang:
	cp ../../materials/linters/.clang-format ./
	clang-format -n *.c *.h
	clang-format -style=Google -n *.c *.h
	rm -rf .clang-format
leaks:
	leaks -atExit -- ./${NAME}