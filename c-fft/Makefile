FLAGS = -std=c99 -Wall -lfftw3_threads -lfftw3 -lm

all: complex.c fft.c pocketfft.c test.c
	gcc complex.c $(FLAGS) -c
	gcc fft.c $(FLAGS) -c 
	gcc pocketfft.c $(FLAGS) -c 
	gcc test.c complex.o fft.o pocketfft.o $(FLAGS) -o test
	gcc benchmark.c complex.o fft.o pocketfft.o $(FLAGS) -o benchmark

clean:
	rm complex.o fft.o test benchmark
