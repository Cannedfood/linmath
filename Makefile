ifeq ($(origin CXX), default)
    CXX = clang++
endif

INCLUDES+= -Iinclude -I../stx/include

DEFINES+= -DSTX_DEBUG=2

CXX_FLAGS+= --std=c++14\
	 -Wall -Wextra -Wno-unused-parameter\
	 -O3\
	 -ggdb -g3

LD_FLAGS+= -lpthread -ldl

test.run: $(wildcard test/*.cpp) $(wildcard include/stx/*.hpp) $(wildcard include/stx/*.inl) $(wildcard include/stx/wip/*.hpp) $(wildcard include/stx/wip/*.inl) Makefile
	${CXX}\
	 ${INCLUDES}\
	 ${DEFINES}\
	 ${CXX_FLAGS}\
	 ${LD_FLAGS}\
	 $(wildcard test/*.cpp)\
	 -o $@
	-+make run

run: test.run
	./test.run

clean:
	-rm test.run

.PHONY: run_test
