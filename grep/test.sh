#!/bin/bash

./s21_grep ab 1 > s21_grep.txt
grep ab 1 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep '[d-e]' 1 > s21_grep.txt
grep '[d-e]' 1 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep ab 1 2 > s21_grep.txt
grep ab 1 2 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep de 1 2 > s21_grep.txt
grep de 1 2 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep '[d-e]' 2 1 > s21_grep.txt
grep '[d-e]' 2 1 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep '[d-e]' 1 2 > s21_grep.txt
grep '[d-e]' 1 2 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -e ab 1 -e d > s21_grep.txt
grep -e ab 1 -e d > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -i DE 1 2 > s21_grep.txt
grep -i DE 1 2 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -v e 2 > s21_grep.txt
grep -v e 2 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -c de 1 2 > s21_grep.txt
grep -c de 1 2 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -l de 1 2 > s21_grep.txt
grep -l de 1 2 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -n de 1 2 > s21_grep.txt
grep -n de 1 2 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -h de 1 2 > s21_grep.txt
grep -h de 1 2 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -s de 4 > s21_grep.txt
grep -s de 4 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -f 3 1 2 > s21_grep.txt
grep -f 3 1 2 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -o de 1 > s21_grep.txt
grep -o de 1 > grep.txt
diff -s s21_grep.txt grep.txt

./s21_grep -o de 1 2 > s21_grep.txt
grep -o de 1 2 > grep.txt
diff -s s21_grep.txt grep.txt
