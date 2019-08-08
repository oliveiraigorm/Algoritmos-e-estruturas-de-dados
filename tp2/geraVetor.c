/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Igor Miranda Oliveira
Matricula: 201312040080
Data: 10/11/2017
************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define ERR_NO_NUM -1
#define ERR_NO_MEM -2

int myRandom (int size) {

    int i, n;
    static int numNums = 0;
    static int *numArr = NULL;

    // Initialize with a specific size.

    if (size >= 0) {
        if (numArr != NULL)
            free (numArr);
        if ((numArr = malloc (sizeof(int) * size)) == NULL)
            return ERR_NO_MEM;
        for (i = 0; i  < size; i++)
            numArr[i] = i;
        numNums = size;
    }

    // Error if no numbers left in pool.

    if (numNums == 0)
       return ERR_NO_NUM;

    // Get random number from pool and remove it (rnd in this
    //   case returns a number between 0 and numNums-1 inclusive).

    n = rand() % numNums;
    i = numArr[n];
    numArr[n] = numArr[numNums-1];
    numNums--;
    if (numNums == 0) {
        free (numArr);
        numArr = 0;
    }

    return i;
}

int* semRep (int n) {
    int i, c=0;
    int* vetor;
    vetor = (int) malloc(sizeof(int) * n);
    srand (time (NULL));
    i = myRandom (n);
    while (i >= 0) {
        vetor[c] = i;
        i = myRandom (-1);
        c++;
    }
    return vetor;
}

int* vetAle (int n) {
    int i, c=0;
    int* vetor;
    vetor = (int*) malloc(sizeof(int) * n);
    srand (time (NULL));
    for(c=0;c<n;c++) {
        vetor[c] = rand();
    }
    return vetor;
}

