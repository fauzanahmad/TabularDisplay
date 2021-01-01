CC = cc
CFLAGS = -g -w
Target = graph

$(Target) : graph.o
	$(CC) graph.o -o $(Target)

graph.o : graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

.PHONY : clean
clean :
	rm -rf graph.o $(Target)

