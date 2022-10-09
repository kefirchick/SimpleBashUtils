#!/bin/bash

./s21_cat 1 > s21_cat.txt
cat 1 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat 1 2 3 > s21_cat.txt
cat 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat 4 > s21_cat.txt
cat 4 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat -b 1 > s21_cat.txt
cat -b 1 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat -b 1 2 3 > s21_cat.txt
cat -b 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat -e 1 2 3 > s21_cat.txt
cat -e 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat -n 1 2 3 > s21_cat.txt
cat -n 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat -s 1 2 3 > s21_cat.txt
cat -s 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat -t 1 2 3 > s21_cat.txt
cat -t 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat -v 1 2 3 > s21_cat.txt
cat -v 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat -est 1 2 3 > s21_cat.txt
cat -est 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

if [[ $(uname -s) != "Darwin" ]]
then

./s21_cat --number-nonblank 1 2 3 > s21_cat.txt
cat --number-nonblank 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat --number 1 2 3 > s21_cat.txt
cat --number 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat --squeeze-blank 1 2 3 > s21_cat.txt
cat --squeeze-blank 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat -E 1 2 3 > s21_cat.txt
cat -E 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

./s21_cat -T 1 2 3 > s21_cat.txt
cat -T 1 2 3 > cat.txt
diff -s s21_cat.txt cat.txt

fi