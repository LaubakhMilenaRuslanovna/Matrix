CC = gcc
CC_FLAGS = -Wall -Wextra -Werror -std=c11
NAME = s21_matrix.a test
OS=$(shell uname -s)
ifeq ($(OS), Linux)
	FLAGS_PLATFORM = -lcheck -lm -lpthread -lrt -lsubunit
else
	FLAGS_PLATFORM = -lcheck -lm -lpthread
endif

OBJECTS = s21*.o
SOURSES = s21*.c

.PHONY: all clean test s21_matrix.a gcov_report

all: clean s21_matrix.a

test: test_matrix.o s21_matrix.a $(OBJECTS)
	$(CC) $(OBJECTS) test_matrix.o s21_matrix.a $(FLAGS_PLATFORM) -o test
	./test

	
main: s21_create_matrix.o s21_remove_matrix.o 
	$(CC) s21_create_matrix.o s21_remove_matrix.o  -o main
	./main

s21_create_matrix.o: s21_create_matrix.c
	$(CC) $(CC_FLAGS) -c s21_create_matrix.c -g

s21_remove_matrix.o: s21_remove_matrix.c
	$(CC) $(CC_FLAGS) -c s21_remove_matrix.c -g

test_matrix.o: test_matrix.c	
	$(CC) $(CC_FLAGS) -c test_matrix.c

gcov_report: s21_matrix.a 
	$(CC) $(CC_FLAGS) --coverage $(SOURSES) test_matrix.c $(FLAGS_PLATFORM) -o gcov_report.o
	@./gcov_report.o
	@lcov -t test_matrix -o test_matrix.info -c -d .
	@genhtml -o gcov_report test_matrix.info
	@open ./gcov_report/index.html


check: s21_matrix.a
	cppcheck *.h *.c
	cp ../materials/linters/.clang-format ../src
	clang-format -n *.h *.c
	$(CC) test_matrix.c s21_matrix.a -lcheck
	$(CC) $(CC_FLAGS) -c test_matrix.c -o test.o
	$(CC) test.o s21_matrix.a $(FLAGS_PLATFORM) -o test
	CK_FORK=no leaks --atExit -- ./test
	rm -rf .clang-format

s21_matrix.a: s21_create_matrix.o s21_remove_matrix.o 
	$(CC) -c $(SOURSES)
	ar rcs s21_matrix.a $(OBJECTS)

clean:
	@rm -f *.a
	@rm -f s21_matrix
	@rm -f *.o
	@rm -f *.txt
	@rm -f *.gcda
	@rm -f *.gcdo
	@rm -f *.gcno
	@rm -f *.info
	@rm -rf *.dSYM
	@rm -rf ./gcov_report
	@rm -f test
	@rm -f *.out

vg: s21_matrix.a
	CK_FORK=no valgrind --tool=memcheck ./test

lik: s21_matrix.a
	CK_FORK=no leaks -atExit -- ./test

install lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

clang:
	cp ../materials/linters/.clang-format ../src
	clang-format -i *.h *.c
	rm -rf .clang-format

push:
	make clean
	make clang
	git add *.c *.h Makefile
	git commit -m "Update"
	git push origin develop


