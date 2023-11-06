CC=gcc -std=c++17
CFLAGS=-Wall -Werror -Wextra -lstdc++
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

TEST_PATH= google_tests/tests.cc

OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lgtest_main -lstdc++
else
	LIBFLAGS=-lgtest -lgtest_main -lm -lpthread -fprofile-arcs -ftest-coverage -lstdc++
endif

all: clean install

install: uninstall
	mkdir build
	cp -rf view/* build
	cd build && qmake 3D_viewer.pro
	make -C build
	cd build && make clean
	open ./build/3D_viewer.app/Contents/MacOS/3D_viewer

uninstall:
	rm -rf build
 
tests: clean
	$(CC) $(CFLAGS) $(TEST_PATH) model/model_viewer.cc -o test $(LIBFLAGS)
	./test

gcov_report:
	$(CC) $(CFLAGS) $(TEST_PATH) ./model/model_viewer.cc $(GCOV_FLAGS) -o test $(LIBFLAGS)
	./test
	gcov test
	lcov  -t "test" -c -d  ./  --no-external --output-file ./coverage.info
	genhtml coverage.info --output-directory ./report/
	# open ./report/index.html

dvi:
	open README_DVI.md

dist:
	mkdir archive
	cp -r build/3D_viewer.app archive
	tar -cvzf archive.tgz archive
	rm -fr archive

leaks: 
	CK_FORK=no valgrind --leak-check=yes --tool=memcheck ./test

clang: 
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n model/* controller/*
	clang-format -style=Google -n view/*.cc view/*.h
	clang-format -style=Google -n google_tests/*.cc
	rm -fr .clang-format

clean:
	@rm -rf *.a \
	*.o \
	*.info \
	*.gcda \
	*.gcno \
	*.gcov \
	*.gch  \
	report \
	test 

.PHONY: dvi clean install
