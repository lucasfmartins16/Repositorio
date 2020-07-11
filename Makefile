tabuleiro.o: tabuleiro.c
	gcc -o tabuleiro.o -c tabuleiro.c

pecas.o: pecas.c
	gcc -o pecas.o -c pecas.c

interface.o: interface.c
	gcc -o interface.o -c interface.c  

dinamica.o: dinamica.c
	gcc -o dinamica.o -c dinamica.c
main.o: main.c
	gcc -o main.o -c main.c

main: main.o tabuleiro.o pecas.o interface.o dinamica.o
	gcc -o main main.o tabuleiro.o pecas.o interface.o dinamica.o
all: main

run: main 
	./main

clean:
	rm *.o
