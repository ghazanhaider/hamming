.DEFAULT_GOAL := hamming

CC = cc
RM = rm -f

engine:
	${CC} -c engine.c -o engine.o

hamming: engine
	@echo "\nBuilding hamming"
	${CC} hamming.c engine.o -o hamming

clean:
	@echo "\nCleaning up..."
	${RM} hamming.o engine.o hamming

test: hamming
	@echo "\n\nTest1: Input type is file\n"
	./hamming -f testdata.bin
	@echo "\n\nTest2: Input type is stdin\n"
	cat testdata.bin | ./hamming -i

