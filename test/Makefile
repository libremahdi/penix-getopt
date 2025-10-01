output ?= "./build"


clean:
	@if [ -d "./build" ]; then\
		rm -R ./build; \
		printf "Build is clean\n"; \
	fi

%:
	@if [ -f $@.c ]; then \
		mkdir -p $(output); \
		gcc -g -O0 -Iinclude -I ../include ./$@.c ../src/pclass.c ../src/perror.c ../src/pinit.c ../src/pkey.c -o $(output)/$@; \
	else \
		printf "Makefile Error:\n$@.c does not exist.\n"; \
	fi
