hanoi:	hanoi.o display.o autosolve.o
	gcc -o hanoi hanoi.o display.o autosolve.o

hanoi.o:	hanoi.c hanoi.h autosolve.h
	gcc -c hanoi.c

display.o:	display.c hanoi.h
	gcc -c display.c

autosolve:	autosolve.c autosolve.h
	gcc -c autosolve.c

clean:
	-rm -f *.o hanoi