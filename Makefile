PROGRAM = main
CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lGL -lGLU -lglut -lm

$(PROGRAM): main.o display.o globalvars.o timers.o keyboard.o bullet.o
	$(CC) $(CFLAGS) -o $(PROGRAM) $^ $(LDFLAGS)

main.o: main.c
	$(CC) -c $(CFLAGS) $^

display.o: display.c display.h
	$(CC) -c $(CFLAGS) $<

globalvars.o: globalvars.c globalvars.h
	$(CC) -c $(CFLAGS) $<

timers.o: timers.c timers.h
	$(CC) -c $(CFLAGS) $<

keyboard.o: keyboard.c keyboard.h
		$(CC) -c $(CFLAGS) $^

bullet.o: bullet.c bullet.h
				$(CC) -c $(CFLAGS) $^

.PHONY: clean

clean:
	-rm *.o $(PROGRAM) *.gch
