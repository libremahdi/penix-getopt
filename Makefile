install:
	echo nothing yet

main_test:
	gcc -g -O0 -Iinclude test/main_test.c src/pinit.c src/pclass.c -o build/test/main_test
