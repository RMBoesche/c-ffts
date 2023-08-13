#include "fft.h"
#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM 30
#define REAL 0
#define IMAG 1

int main(void) {
    struct complex_t* input1 = (struct complex_t*) malloc(sizeof(struct complex_t) * 30);
    struct complex_t* input2 = (struct complex_t*) malloc(sizeof(struct complex_t) * 30);
    struct complex_t* result1 = (struct complex_t*) malloc(sizeof(struct complex_t) * 30);
    struct complex_t* result2 = (struct complex_t*) malloc(sizeof(struct complex_t) * 30);
    fftw_complex* input3 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NUM);
    fftw_complex* result3 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NUM);
    
    /* Init inputs */
    for (int i=0; i < NUM; i++) {
        input1[i].re = (double) i;
        input1[i].im = 0.0;
        input2[i].re = (double) i;
        input2[i].im = 0.0;
        input3[i] = (double)i + 0.0 * I;
    }
    
    /* Do FFT */
    result1 = FFT_CooleyTukey(input1, NUM, 6, 5);
    result2 = FFT_GoodThomas(input2, NUM, 6, 5);

    fftw_plan plan = fftw_plan_dft_1d(NUM, input3, result3, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    
    /* Compare results */
    printf("Index \t Cooley-Tukey Output \t \t Good-Thomas Output \t \t FFTW Output \n");
    for (int i=0; i < NUM; i++) {
        printf("%d: \t %f + %fi \t %f + %fi \t %f + %fi \n", 
                i, result1[i].re, result1[i].im, 
                   result2[i].re, result2[i].im, 
                   creal(result3[i]), cimag(result3[i]));
    }
    fftw_free(input3); fftw_free(result3);
    return 0;
}

