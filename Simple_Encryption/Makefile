CC = gcc
LIBS = -lreadline

simple_encryption : simple_encryption.o
	$(CC) simple_encryption.o -o simple_encryption $(LIBS)

simple_encryption.o : simple_encryption.c
	$(CC) -c simple_encryption.c $(LIBS)

clean:
	rm -f *.o simple_encryption
