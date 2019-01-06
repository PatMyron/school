HEADERS = gfx2.h
OBJECTS = carnival.o gfx2.o
FLAGS   = -lX11 -L/usr/X11/lib -I/usr/X11/include -w

default: program

%.o: %.c $(HEADERS)
	gcc -c $< $(FLAGS) -o $@

program: $(OBJECTS)
	gcc $(OBJECTS) $(FLAGS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f program
