CC = gcc
FLAGS = -Wall -Wextra -Werror
COMMON = ../common/
CAT = ../cat/

all: s21_cat s21_grep

s21_cat: fileIO.o
	$(CC) $(FLAGS) $(CAT)cat.c fileIO.o $(CAT)main.c -o $(CAT)s21_cat

s21_grep: fileIO.o
	$(CC) $(FLAGS) grep.c fileIO.o main.c -o s21_grep

fileIO.o: $(COMMON)fileIO.c
	$(CC) $(FLAGS) -c $(COMMON)fileIO.c

rebuild: clean all

clean:
	rm -rf *.o $(CAT)s21_cat s21_grep

test_grep: s21_grep
	bash Test/test_func_grep.sh

test_cat: s21_cat
	cd $(CAT); bash Test/test_func_cat.sh; cd ../grep/

test: test_cat test_grep clean
