output ?= "./build"


clean:
	@if [ -d "./build" ]; then\
		rm -R ./build; \
		printf "Build is clean\n"; \
	fi

%:
	@if [ -f $@.c ]; then \
		mkdir -p $(output); \
	gcc -g -O0 -I../include -I../src/lib/ ./$@.c \
	../src/*.c \
	../src/pclass/*.c \
	../src/lib/*.c \
	../src/pinit/*.c -o $(output)/$@; \
	else \
		printf "Makefile Error:\n$@.c does not exist.\n"; \
	fi
