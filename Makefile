CC = g++
CFLAGS = -g -w
Target = display

$(Target) : display.o
	$(CC) display.o -o $(Target)

display.o : display.cpp display.h
	$(CC) $(CFLAGS) -c display.cpp

.PHONY : clean
clean :
	rm -rf display.o $(Target)

