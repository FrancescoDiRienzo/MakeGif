CC = cc
CFLAGS = -c -Wall -O3
LIBS = -lm
LDFLAGS = 

CFLAGS += `pkg-config --cflags MagickWand`
LDFLAGS += `pkg-config --libs MagickWand`

main: main.o makeGif.o libgif.o
	$(CC) main.o makeGif.o libgif.o -o main $(LDFLAGS) $(LIBS)

main.o: main.c 
	$(CC) $(CFLAGS) main.c
makeGif.o: makeGif.c
	$(CC) $(CFLAGS) makeGif.c 
libgif.o: libgif.c
	$(CC) $(CFLAGS) libgif.c

clean:
	rm -rf *.o
