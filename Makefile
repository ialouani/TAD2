CFLAG=-std=c99 -g3

.PHONY: test_all build clean
all: build
test.o: ./tests_dliste.c 
	cc -c ${CFLAG} -I . $< -o $@
liste_doublement_chainee.o: ./liste_doublement_chainee.c 
	cc -c ${CFLAG} -I . $< -o $@
test_all: test.o liste_doublement_chainee.o
	gcc ${CFLAG} $^ -o $@
build: test_all
	./test_all
valgrind_check: test_all
	valgrind --leak-check=full ./test_all
clean:
	rm -f *.c~ Makefile~ *.o test_all *.h~
