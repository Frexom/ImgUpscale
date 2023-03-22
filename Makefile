CC=gcc
CFLAGS= -Wall -Werror


#Compiling file
imgUpscale: imgUpscale.o
	$(CC) bin/imgUpscale.o -o exec/imgUpscale

imgUpscale.o: files/imgUpscale.c
	$(CC) -c files/imgUpscale.c -o bin/imgUpscale.o $(CFLAGS)

#Running it (with exmaple image)
run:
	./exec/imgUpscale flower.ppm

#Clear the unnecessary files
clean:
	rm bin/*.o
