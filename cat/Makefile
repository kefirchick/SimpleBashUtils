CC= gcc -std=c11
CFLAGS= -Wall -Wextra -Werror -g
OS := $(shell uname -s)

all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat -lm

test: s21_cat
	chmod 777 test.sh
	-./test.sh

clean:
	rm -rf s21_cat *.a *.out *.o *txt *.dSYM

check: s21_cat
	-cppcheck --enable=all --suppress=missingIncludeSystem ../../src/grep/
	cp ../../materials/linters/CPPLINT.cfg ./
	-python3 ../../materials/linters/cpplint.py --extensions=c ./*.c
	rm 	./CPPLINT.cfg
ifeq ($(OS), Darwin)
	-CK_FORK=no leaks --atExit -- ./s21_cat -betns 1 2 3 4
else
	-valgrind --leak-check=full --quiet ./s21_cat -betns 1 2 3 4
endif
	rm -rf s21_cat *.a *.out *.o *txt *.dSYM

.PHONY: all clean rebuild

rebuild: clean all