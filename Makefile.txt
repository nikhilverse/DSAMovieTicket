CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJS = main.o movie.o booking.o

# Default target to build the executable
all: movie_ticket

movie_ticket: $(OBJS)
	$(CC) $(CFLAGS) -o movie_ticket $(OBJS)

main.o: main.c movie.h booking.h
movie.o: movie.c movie.h
booking.o: booking.c booking.h movie.h

# Clean compiled files
clean:
	rm -f *.o movie_ticket
