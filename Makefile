CC=gcc
CFLAGS= -I ./libjpeg/include
LIBS=-lX11	-ljpeg -L./libjpeg/lib
source=$(wildcard ./*.c)
objects=$(patsubst %.c,%.o,$(source))
targets=capture_screen
.PHONY:clean

$(targets) : $(objects)
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

clean:
	-rm $(objects) $(targets) -f
