CC=gcc
CFLAGS=-Wall
SECURITY=-z execstack
LDFLAGS=-lportaudio -ljack 

all:
	$(CC) $(CFLAGS) main.c waves.c -o runme $(SECURITY) $(LDFLAGS)

debug:
	$(CC) $(CFLAGS) -g3 main.c waves.c -o runme $(SECURITY) $(LDFLAGS) 

clean:
	rm -rf *.o runme

