CC = gcc
FLAGS = -Wall -Wextra -Werror
COMMON = ../common/
GREP = ../grep/

all: s21_cat s21_grep

s21_cat: fileIO.o
	$(CC) $(FLAGS) cat.c fileIO.o main.c -o s21_cat

s21_grep: fileIO.o
	$(CC) $(FLAGS) $(GREP)grep.c fileIO.o $(GREP)main.c -o $(GREP)s21_grep

fileIO.o: $(COMMON)fileIO.c
	$(CC) $(FLAGS) -c $(COMMON)fileIO.c

rebuild: clean all

clean:
	rm -rf *.o s21_cat $(GREP)s21_grep

test_cat: s21_cat
	bash Test/test_func_cat.sh

test_grep: s21_grep
	cd $(GREP); bash Test/test_func_grep.sh; cd ../cat/

test: test_cat test_grep clean
