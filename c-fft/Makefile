FLAGS = -std=c99 -Wall -lfftw3_threads -lfftw3 -lm

all: complex.c fft.c test.c
	gcc complex.c $(FLAGS) -c
	gcc fft.c $(FLAGS) -c 
	gcc test.c complex.o fft.o $(FLAGS) -o test
	gcc benchmark.c complex.o fft.o $(FLAGS) -o benchmark

clean:
	rm complex.o fft.o test benchmark
