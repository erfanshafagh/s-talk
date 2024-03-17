all: s-talk

s-talk: list.o socket.o sender.o input.o receive.o output.o s-talk-main.o   
	gcc -Wall -o s-talk list.o s-talk-main.o socket.o sender.o input.o receive.o output.o -pthread 

s-talk-main.o: s-talk-main.c socket.h
	gcc -Wall -c s-talk-main.c

socket.o: socket.c socket.h
	gcc -Wall -c socket.c

receive.o: receive.h receive.c
	gcc -Wall -c receive.c

sender.o: sender.h sender.c
	gcc -Wall -c sender.c

output.o: output.h output.c
	gcc -Wall -c output.c

input.o: input.h input.c
	gcc -Wall -c input.c

list.o: list.h list.c
	gcc -w    -c list.c

clean:
	rm -f s-talk *.o
