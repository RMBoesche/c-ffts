#include "fft.h"
#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
// #include <mkl.h>
#include "pocketfft.h"

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
    double result4[2*NUM];
    // MKL_Complex8* input4 = (MKL_Complex8*) fftw_malloc(sizeof(MKL_Complex8) * NUM);
    // MKL_Complex8* result4 = (MKL_Complex8*) fftw_malloc(sizeof(MKL_Complex8) * NUM);
    
    /* Init inputs */
    for (int i=0; i < NUM; i++) {
        input1[i].re = (double) i;
        input1[i].im = 0.0;
        input2[i].re = (double) i;
        input2[i].im = 0.0;
        input3[i] = (double)i + 0.0 * I;
        result4[2*i] = (double) i;
        result4[2*i+1] = 0.0;
        // input4[i].real = (double) i;
        // input4[i].imag = 0.0;
    }
    
    /* Do FFT */
    result1 = FFT_CooleyTukey(input1, NUM, 6, 5);
    result2 = FFT_GoodThomas(input2, NUM, 6, 5);

    fftw_plan plan = fftw_plan_dft_1d(NUM, input3, result3, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);

    cfft_plan pocketplan = make_cfft_plan(NUM);
    cfft_forward(pocketplan, result4, 1.);
    destroy_cfft_plan(pocketplan);

    // DFTI_DESCRIPTOR_HANDLE handle;
    // DftiCreateDescriptor(&handle, DFTI_SINGLE, DFTI_COMPLEX, 1, NUM);
    // DftiComputeForward(handle, input4, result4);
    
    // Clean up
    
    /* Compare results */
    printf("Index \t Cooley-Tukey Output \t \t Good-Thomas Output \t \t FFTW Output \t \t PocketFFT Output \\n");
    for (int i=0; i < NUM; i++) {
        printf("%d: \t %f + %fi \t %f + %fi \t %f + %fi \t %f + %fi \n", 
                i, result1[i].re, result1[i].im, 
                   result2[i].re, result2[i].im, 
                   creal(result3[i]), cimag(result3[i]),
                //    result4[i].real, result4[i].imag,,
                   result4[2*i], result4[2*i+1]);
    }
    fftw_free(input3); fftw_free(result3);
    // DftiFreeDescriptor(&handle);
    // free(input4); free(result4);
    return 0;
}

