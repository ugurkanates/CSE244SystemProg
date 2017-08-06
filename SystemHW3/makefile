all: list

list: main.o 
	gcc main.o -o exe

main.o: main.c
	rm -f odev.txt
	rm -f log.log
	gcc -c main.c

clean:
	rm *.o exe
	rm -f odev.txt
