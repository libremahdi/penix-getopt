install:
	gcc -g -O0 -Iinclude test/test.c src/pclass.c src/pinit.c -o build/test/test && ./build/test/test
