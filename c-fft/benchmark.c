#include "fft.h"
#include "pocketfft.h"
#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

void timeSubtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;
}

int main(void) {
    struct timeval tvBegin, tvEnd, tvDiff;

    struct complex_t* input = (struct complex_t*) malloc(sizeof(struct complex_t) * 30);
    struct complex_t* result_naive = (struct complex_t*) malloc(sizeof(struct complex_t) * 30);
    struct complex_t* result_cooley_tukey = (struct complex_t*) malloc(sizeof(struct complex_t) * 30);
    struct complex_t* result_good_thomas = (struct complex_t*) malloc(sizeof(struct complex_t) * 30);
    fftw_complex* input2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 30);   
    fftw_complex* result_fftw = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 30);
    double input3[2*30];

    /* Init inputs */
    for (int i=0; i < 30; i++) {
        input[i].re = (double) i;
        input[i].im = 0.0;
        input2[i] = (double)i + 0.0 * I;
        input3[2*i] = (double) i;
        input3[2*i+1] = 0.0;
    }

    /* Naive DFT */
    gettimeofday(&tvBegin, NULL);
    for (int i=0; i < 10000; i++) {
        result_naive = DFT_naive(input, 30);
    }
    gettimeofday(&tvEnd, NULL);

    timeSubtract(&tvDiff, &tvEnd, &tvBegin);
    printf("100000 x Naive: \t %ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);
  
    
    /* Cooley-Tukey */
    gettimeofday(&tvBegin, NULL);
    for (int i=0; i < 10000; i++) {
        result_cooley_tukey = FFT_CooleyTukey(input, 30, 6, 5);
    }
    gettimeofday(&tvEnd, NULL);

    timeSubtract(&tvDiff, &tvEnd, &tvBegin);
    printf("100000 x Cooley-Tukey: \t %ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);

    /* Good-Thomas */
    gettimeofday(&tvBegin, NULL);
    for (int i=0; i < 10000; i++) {
        result_good_thomas = FFT_GoodThomas(input, 30, 6, 5);
    }
    gettimeofday(&tvEnd, NULL);

    timeSubtract(&tvDiff, &tvEnd, &tvBegin);
    printf("100000 x Good-Thomas: \t %ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);

    /* FFTW */
    fftw_plan plan = fftw_plan_dft_1d(30, input2, result_fftw, FFTW_FORWARD, FFTW_ESTIMATE);
    gettimeofday(&tvBegin, NULL);
    for (int i=0; i < 10000; i++) {
        fftw_execute(plan);
    }
    gettimeofday(&tvEnd, NULL);
    fftw_destroy_plan(plan);    
    
    timeSubtract(&tvDiff, &tvEnd, &tvBegin);
    printf("100000 x FFTW: \t %ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);

    /* PocketFFT*/
    cfft_plan pocketplan = make_cfft_plan(30);
    gettimeofday(&tvBegin, NULL);
    for (int i=0; i < 10000; i++) {
        cfft_forward(pocketplan, input3, 1.);
    }
    gettimeofday(&tvEnd, NULL);
    destroy_cfft_plan(pocketplan);

    timeSubtract(&tvDiff, &tvEnd, &tvBegin);
    printf("100000 x PocketFFT: \t %ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);


    free(input);
    free(result_naive);
    free(result_cooley_tukey);
    free(result_good_thomas);
    fftw_free(input2); fftw_free(result_fftw);
    return 0;
}

