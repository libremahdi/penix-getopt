install:
	echo nothing yet

main:
	gcc -g -O0 test/main_test.c -o test/build/main_test -L/usr/local/lib -lpgetopt -Wl,-rpath,/usr/local/lib
