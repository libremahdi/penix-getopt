install:
	echo nothing yet

test_main:
	gcc -g -O0 -Iinclude test/test_main.c src/pkey.c src/pgoerror.c src/pclass.c src/pinit.c -o build/test/test_main

test_cloneoption_flag:
	gcc -g -O0 -Iinclude test/test_cloneoption_flag.c src/pkey.c src/pgoerror.c src/pclass.c src/pinit.c -o build/test/test_cloneoption_flag
