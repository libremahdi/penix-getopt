output ?= "./output"


clean:
	@if [ -d "./output" ]; then\
		rm -R ./output; \
		printf "'output' is clean\n"; \
	fi

%:
	@if [ -f $@.c ]; then \
		mkdir -p $(output); \
	gcc -g -O0 -I../include -I../src/lib/ \
	-I../../parabyte-pstring/include -I../../parabyte-pstring/src/lib -I../../parabyte-pstring/src ../../parabyte-pstring/src/*.c \
	./$@.c \
	../src/*.c \
	../src/pclass/*.c \
	../src/lib/*.c \
	../src/pinit/*.c -o $(output)/$@; \
	else \
		printf "Makefile Error:\n$@.c does not exist.\n"; \
	fi
