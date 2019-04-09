all: main.o sort.o sort.h
	gcc -Wall -pedantic -pthread -o sort main.o sort.o

main.o: main.c
	gcc -Wall -pedantic -c main.c

sort.o: sort.c
	gcc -Wall -pedantic -c sort.c

run: sort
	./sort 
	./sort 2 
	./sort 3 

clean: main.o sort.o sort
	rm main.o sort.o sort
