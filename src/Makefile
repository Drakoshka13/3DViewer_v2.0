CC=gcc -std=c++17
CFLAGS=-Wall -Werror -Wextra -lstdc++
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

TEST_PATH=./Google_Tests/*

OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lgtest_main -lstdc++
else
	LIBFLAGS=-lgtest -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
endif

all: clean install

install: uninstall
	mkdir build
	cp -rf View/* build
	cd build && qmake 3D_viewer.pro
	make -C build
	cd build && make clean
	open ./build/3D_viewer.app/Contents/MacOS/3D_viewer

uninstall:
	rm -rf build
 
test: clean
	$(CC) $(CFLAGS) $(LIBFLAGS) $(TEST_PATH) ./Model/Model.cc -o test
	./test

gcov_report:
	$(CC) $(TEST_PATH) ./Model/Model.cc  $(LIBFLAGS) $(GCOV_FLAGS) -lcheck -o test
	./test
	gcov test
	lcov --ignore-errors mismatch -t "test" -c -d  ./  --no-external --output-file ./coverage.info
	genhtml coverage.info --output-directory ./report/
	open ./report/index.html

dvi:
	open README_DVI.md

dist:
	mkdir archive
	cp -r build/3D_viewer.app archive
	tar -cvzf archive.tgz archive
	rm -fr archive

leaks: test
	CK_FORK=no leaks --atExit -- ./test

clang: 
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n Model/* Controller/*
	clang-format -style=Google -n View/*.ccp View/*.h
	clang-format -style=Google -n controller/*.h 
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
