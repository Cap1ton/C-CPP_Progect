WWW = -Wall -Wextra -Werror -std=c11
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

all: s21_matrix.a gcov_report clean_obj

s21_matrix.a: clean_obj clean_lib
	gcc -c s21_*.c
	ar rcs s21_matrix.a s21_*.o
	ranlib s21_matrix.a

test: s21_matrix.a
ifeq ($(OS), Darwin)
	gcc $(WWW) unit_test.c s21_matrix.a -o unit_test $(LIBS)
else
	gcc $(WWW) unit_test.c s21_matrix.a -o unit_test $(LIBS) $(LINUX)
endif
	./unit_test

gcov_report: clean_test
ifeq ($(OS), Darwin)
	gcc $(WWW) -fprofile-arcs -ftest-coverage unit_test.c s21_*.c -o unit_test $(LIBS)
else
	gcc $(WWW) -fprofile-arcs -ftest-coverage unit_test.c s21_*.c -o unit_test $(LIBS) $(LINUX)
endif
	./unit_test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

valg: s21_matrix.a
ifeq ($(OS), Darwin)
	gcc $(WWW) unit_test.c s21_matrix.a -o unit_test $(LIBS)
	CK_FORK=no valgrind --leak-check=full -s ./unit_test
else
	gcc $(WWW) unit_test.c s21_matrix.a -o unit_test $(LIBS) $(LINUX)
	K_FORK=no valgrind --leak-check=full -s ./unit_test
endif

check:
	cp ../materials/linters/.clang-format .clang-format
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	clang-format -i *.c *.h
	sleep 0.5
	clang-format -i *.c *.h
	rm -rf .clang-format

clean: clean_lib clean_lib clean_test clean_obj 
	rm -rf unit_test

clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
