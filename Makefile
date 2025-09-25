install:
	echo nothing yet

main_test:
	gcc -g -O0 -Iinclude test/main_test.c src/pinit.c src/pclass.c src/pkey.c src/perror.c -o build_test/main_test

main:
	gcc -g -O0 test/main_test.c -o build_test/main_test -L/usr/local/lib -lpgetopt -Wl,-rpath,/usr/local/lib