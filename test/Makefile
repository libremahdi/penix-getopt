output ?= "./build"


clean:
	@if [ -d "./build" ]; then\
		rm -R ./build; \
		printf "Build is clean\n"; \
	fi

%:
	@if [ -f $@.c ]; then \
		mkdir -p $(output); \
	gcc -g -O0 -Iinclude -I ../include -I ../src/lib/mem_manage ./$@.c ../src/pclass.c ../src/perror.c ../src/pinit.c ../src/pkey.c ../src/pclass/pclass_create.c ../src/lib/mem_manage/salloc.c -o $(output)/$@; \
	else \
		printf "Makefile Error:\n$@.c does not exist.\n"; \
	fi
