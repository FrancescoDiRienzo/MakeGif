CC = cc
CFLAGS = -c -Wall -O2
LIBS = -lm
LDFLAGS = 

CFLAGS += `pkg-config --cflags MagickWand`
LDFLAGS += `pkg-config --libs MagickWand`

main: main.o libgif.o
	$(CC) main.o libgif.o -o main $(LDFLAGS) $(LIBS)

main.o: libgif.h
libgif.o: libgif.h

clean:
	rm -rf *.o
