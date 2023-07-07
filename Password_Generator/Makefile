CC = gcc

password_generator : password_generator.o ../user_input.o
	$(CC) password_generator.o ../user_input.o -o password_generator

password_generator.o : password_generator.c
	$(CC) -c password_generator.c

../user_input.o : ../user_input.c
	$(CC) -c ../user_input.c -o user_input.o

clean:
	rm -f *.o password_generator
