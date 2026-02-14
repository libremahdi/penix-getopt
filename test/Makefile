##
 # Copyright (C) Mahdi Hosseini Asaad, All rights reserved.
 # For more information, please read LICENSE file.
##

output ?= "./output"
.PHONY: clean main

clean:
	@if [ -d "./output" ]; then\
		rm -R ./output; \
		printf "'output' is clean\n"; \
	fi

# -I../../parabyte-pstring/include -I../../parabyte-pstring/src/lib -I../../parabyte-pstring/src ../../parabyte-pstring/src/*.c \

main:
	@if [ -f main.c ]; then \
		mkdir -p $(output); \
	clang -g -O0 -I../include -I../src/lib/ -I./t-lib/ \
	./t-lib/*.c \
	./main.c \
	../src/*.c \
	../src/pclass/*.c \
	../src/lib/*.c \
	../src/pinit/*.c -o $(output)/main; \
	else \
		printf "Makefile Error:\nmain.c does not exist.\n"; \
	fi

%:
	@if [ -f $@.c ]; then \
		mkdir -p $(output); \
	clang -g -O0 -I../include -I../src/lib/ \
	./$@.c \
	../src/*.c \
	../src/pclass/*.c \
	../src/lib/*.c \
	../src/pinit/*.c -o $(output)/$@; \
	else \
		printf "Makefile Error:\n$@.c does not exist.\n"; \
	fi
