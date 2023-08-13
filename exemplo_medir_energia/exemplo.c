/*
* EXEMPLO: Multiplica��o de matriz medindo consumo de energia e tempo de execu��o
*
* Arquivo com exemplo de como utilizar a biblioteca para ler consumo de energia.
*
* COMO COMPILAR usando a lib para ler consumo de energia:  
* $ gcc exemplo.c energia.c -o mmatriz
* onde:
*   "exemplo.c" � o arquivo da sua aplica��o
*   "energia.c" � o arquivo com o c�digo da lib do RAPL (deve estar no mesmo diret�rio)
*   "mmatriz" � o nome do arquivo execut�vel de saida
*
* Obs. IMPORTANTE: os contadores de energia n�o tem precis�o para execu��es com tempo menor que 0.001 segundos. 
*/

/* (1) Incluir Header file para ter acesso as fun��es para ter o consumo de energia */
#include "energia.h" 
#include "../c-fft/fft.h"
#include <complex.h>
#include <fftw3.h>

#define NUM 9999
#define NUM_ALG 3

void initialize_matrices();
void multiply_matrices();

int main(int argc, char* argv[])
{
    struct complex_t* input1 = (struct complex_t*) malloc(sizeof(struct complex_t) * NUM);
    struct complex_t* input2 = (struct complex_t*) malloc(sizeof(struct complex_t) * NUM);
    struct complex_t* result1 = (struct complex_t*) malloc(sizeof(struct complex_t) * NUM);
    struct complex_t* result2 = (struct complex_t*) malloc(sizeof(struct complex_t) * NUM);
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

    fftw_plan plan = fftw_plan_dft_1d(NUM, input3, result3, FFTW_FORWARD, FFTW_ESTIMATE);

    rapl_init();

    for (int i=0; i<NUM_ALG; i++){
        /* (2) chamar esta funcao no inicio do main para inicializar a lib do RAPL */
        start_rapl_sysfs(); // (3) Iniciar a contagem de consumo de energia
        clock_t t = clock(); // Iniciar a contagem de tempo
        /* (4) Chamar aqui a fun��o que faz o que voc� deseja medir o tempo e a energia */
        switch (i) {
            case 0: 
                result1 = FFT_CooleyTukey(input1, NUM, 101, 99);
            break;

            case 1:
                result2 = FFT_GoodThomas(input2, NUM, 101, 99);
            break;

            case 2:
                fftw_execute(plan);
            break;
        }
        /*************************************************/
        t = clock() - t; // Finalizar contagem do tempo
        double energy = end_rapl_sysfs();   // (5) Finalizar a contagem dos contadores de energia
        double tempo = ((double)t)/CLOCKS_PER_SEC; // transforma tempo para segundos
        printf("Tempo de execucao em segundos: %.5f\n", tempo);
        printf("Energia consumida em Joules:   %.5f\n", energy); // (6) imprimir consumo de energia em Joules
    }
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

