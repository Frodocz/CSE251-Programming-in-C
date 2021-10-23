scheduler: scheduler.o io.o schedule.o event.o
	gcc -o scheduler scheduler.o io.o schedule.o event.o

scheduler.o: scheduler.c
	gcc -c scheduler.c

schedule.o: schedule.c schedule.h
	gcc -c schedule.c

event.o: event.c event.h
	gcc -c event.c

io.o: io.c io.h
	gcc -c io.c

clean:
	rm -f *.o scheduler