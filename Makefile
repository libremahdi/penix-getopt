install:
	gcc -g -O0 -Iinclude test/test.c src/pkey.c src/pclass.c src/pinit.c -o build/test/test
