CC = cc
CFLAGS = -c -Wall -O2
LIBS = -lm
LDFLAGS = 

CFLAGS += `pkg-config --cflags MagickWand`
LDFLAGS += `pkg-config --libs MagickWand`

makeGif: makeGif.o libgif.o 
	$(CC) $^ -o $@ $(LDFLAGS) $(LIBS)

makeGif.o: libgif.h constant.h
libgif.o: libgif.h constant.h

clean:
	rm -rf *.o
