CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

png2txt.o: png2txt.c pnglite.h cs220_paint.h
	$(CC) $(CFLAGS) -c png2txt.c
txt2png.o: txt2png.c pnglite.h cs220_paint.h
	$(CC) $(CFLAGS) -c txt2png.c
pnglite.o: pnglite.c pnglite.h 
	$(CC) $(CFLAGS) -c pnglite.c
cs220_paint.o: cs220_paint.c cs220_paint.h 
	$(CC) $(CFLAGS) -c cs220_paint.c 
cs220_paint: cs220_paint.o driver.o
	$(CC) -o cs220_paint driver.o cs220_paint.o -lm
png2txt: png2txt.o pnglite.o cs220_paint.o
	$(CC) png2txt.o pnglite.o cs220_paint.o -o png2txt -lz -lm
txt2png: txt2png.o pnglite.o cs220_paint.o
	$(CC) txt2png.o pnglite.o cs220_paint.o -o txt2png -lz -lm
clean:
	rm -f *.o driver
