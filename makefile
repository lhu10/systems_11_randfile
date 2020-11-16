all: main.o
	gcc -o work11 main.o

main.o: main.c 
	gcc -c main.c

clean:
	rm *.o
run:
	./work11
