WWW = -std=c11 -Wall -Werror -Wextra
OS := $(shell uname)

ifeq ($(OS),Linux)
 CHFLAGS = -lcheck -lm -lpthread -lrt -lsubunit
 GCFLAGS = --coverage -lcheck -lm -lsubunit
else
 CHFLAGS = -lcheck -lm -lpthread
 GCFLAGS = --coverage -lcheck
endif

all: clean install tests gcov_report

pol.a: clean SmartCalc/pol/pol.o
	ar -crs SmartCalc/pol/pol.a SmartCalc/pol/pol.o
	rm -rf SmartCalc/*.o
pol.o:
	gcc $(WWW) -c SmartCalc/pol/pol.c

tests: clean pol.a
	gcc $(WWW) unit_test.c SmartCalc/pol/pol.a $(CHFLAGS) -o unit_test
	rm -rf SmartCalc/pol/pol.a
	./unit_test
	
gcov_report: clean pol.a
	gcc unit_test.c SmartCalc/pol/pol.c $(GCFLAGS) -o ./gcov
	./gcov
	lcov -t "./unit_test" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gcov

clean:
	rm -rf *.o *.a
	rm -rf SmartCalc/pol/*.o *.a
	rm -rf *.gcno *gcda *.gcov gcov 
	rm -rf report report.info
	rm -rf unit_test install_release myapp_release my_app.tar.gz

install: clean
	mkdir install_release
	mkdir myapp_release
	cd install_release && \
		cmake -DCMAKE_BUILD_TYPE=Release -D EXECUTABLE_OUTPUT_PATH="../myapp_release" ../SmartCalc &&  \
		cmake --build ../install_release/. && \
		rm -rf ../install_release

uninstall:
	rm -rf myapp_release

del_lib:
	rm -rf pol.a

dist: install
	tar -cf my_app.tar.gz myapp_release/
	rm -rf myapp_release
