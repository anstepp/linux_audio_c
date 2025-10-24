CC=gcc
SRC= main.c synthesis/waves.c
CFLAGS=-Wall -Wextra
SECURITY=-z execstack
LDFLAGS=-lportaudio -ljack 


all: pa_err_custom.o waves.o
	$(CC)  main.c pa_err_custom.o waves.o $(SECURITY) $(LDFLAGS) -o runme

verbose: pa_err_custom.o waves.o
	$(CC) $(CFLAGS) main.c pa_err_custom.o waves.o $(SECURITY) $(LDFLAGS) -o runme

debug:
	$(CC) $(CFLAGS) -g3 $(SRC) -o runme $(SECURITY) $(LDFLAGS) 

waves.o: 
	$(CC) $(CFLAGS) -c synthesis/waves.c $(SECURITY) $(LDFLAGS) -o waves.o

pa_err_custom.o:
	$(CC) $(CFLAGS) -c pa_custom/pa_err_custom.c $(SECURITY) $(LDFLAGS) -I./pa_custom -o pa_err_custom.o

clean:
	rm -rf *.o runme

