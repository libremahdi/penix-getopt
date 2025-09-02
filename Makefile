install:
	gcc -g -O0 -Iinclude test/test_simple.c src/pclass.c src/pinit.c -o build/test/test && ./build/test/test
