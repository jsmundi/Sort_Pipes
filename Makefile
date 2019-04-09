all: main.o sort.o sort.h
	gcc -o sort main.o sort.o

main.o: main.c
	gcc -c main.c

sort.o: sort.c
	gcc -c sort.c

run: sort
	./sort 
	./sort 2 
	./sort 3 

clean: main.o sort.o sort
	rm main.o sort.o sort
