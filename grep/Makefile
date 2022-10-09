CC= gcc -std=c11
CFLAGS= -Wall -Wextra -Werror -g
OS := $(shell uname -s)

all: s21_grep

s21_grep:
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep -lpcre

test: s21_grep
	chmod 777 test.sh
	-./test.sh

clean:
	rm -rf s21_grep *.a *.out *.o *.txt *.dSYM 

check: s21_grep
	-cppcheck --enable=all --suppress=missingIncludeSystem ../../src/grep/
	cp ../../materials/linters/CPPLINT.cfg ./
	-python3 ../../materials/linters/cpplint.py --extensions=c ./*.c
	rm 	./CPPLINT.cfg
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./s21_grep -f 3 -e a -c -v 1 2
else
	valgrind --leak-check=full --quiet ./s21_grep -f 3 -e a -c -v 1 2
endif
	rm -rf s21_cat *.a *.out *.o *txt *.dSYM

.PHONY: all clean rebuild

rebuild: clean all