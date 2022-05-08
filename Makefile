CC = cc
CFLAGS = -g -w
Target = display

$(Target) : display.o
	$(CC) display.o -o $(Target)

display.o : display.c display.h
	$(CC) $(CFLAGS) -c display.c

.PHONY : clean
clean :
	rm -rf display.o $(Target)

