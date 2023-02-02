##
## EPITECH PROJECT, 2023
## GenericC-DS
## File description:
## Makefile
##

LIBSRC	=	source/generic_list.c

LIBOBJ	=	$(LIBSRC:.c=.o)

TESTSRC	=	tests/test.c

TESTOBJ	=	$(TESTSRC:.c=.o)

LIB	=	libgencds.so

TEST	=	unit_tests

CC	=	gcc

LDFLAGS	=	-L. -lgencds -lcriterion

CFLAGS	=	-Wall -Wextra --coverage

CPPFLAGS	=	-Iinclude -fpic

all: $(LIB)

.o:
	$(CC) -c -o $< $@ $(CPPFLAGS)

$(LIB): CFLAGS += -shared
$(LIB): $(LIBOBJ)
	$(CC) -o $(LIB) $(LIBOBJ) $(CFLAGS)

clean:
	$(RM) $(LIBOBJ) $(TESTOBJ)  */*.gcno */*.gcda

fclean: clean
	$(RM) $(LIB) $(TEST)

re: fclean all

build_tests: $(LIB) $(TESTOBJ)
	$(CC) -o $(TEST) $(TESTOBJ) $(LDFLAGS) $(CFLAGS)

tests_run: build_tests
	@bash -c "export LD_LIBRARY_PATH=$$PWD && ./$(TEST)"

.PHONY: all clean fclean re
