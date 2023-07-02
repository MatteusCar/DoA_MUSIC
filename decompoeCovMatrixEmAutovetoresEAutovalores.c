#include <stdio.h>
#include "lapacke.h"

#define NUM_SENSORS 4      // Número de sensores

/*

Para decompor a matriz de covariância em autovetores e autovalores, você pode utilizar a biblioteca de álgebra
linear chamada LAPACK (Linear Algebra PACKage) em C. A biblioteca LAPACK fornece uma série de funções para cálculos
matriciais, incluindo a decomposição espectral.

*/

int main()
{
    double covarianceMatrix[NUM_SENSORS][NUM_SENSORS];  // Matriz de covariância

    // Popula a matriz de covariância (exemplo hipotético)
    for (i = 0; i < NUM_SENSORS; i++)
    {
        for (j = 0; j < NUM_SENSORS; j++)
        {
            covarianceMatrix[i][j] = ...;  // Insira o valor da matriz de covariância
        }
    }

    // Variáveis para armazenar os resultados da decomposição espectral
    double eigenvalues[NUM_SENSORS];
    double eigenvectors[NUM_SENSORS][NUM_SENSORS];

    // Executa a decomposição espectral usando LAPACK, "U" é usado porque a matriz resultante é simétrica, então armazenamos apenas a parte triangular superior
    LAPACKE_dsyev(LAPACK_COL_MAJOR, 'V', 'U', NUM_SENSORS, &covarianceMatrix[0][0], NUM_SENSORS, eigenvalues);

    // Imprime os autovalores
    printf("Autovalores:\n");
    for (i = 0; i < NUM_SENSORS; i++)
    {
        printf("%.2lf\n", eigenvalues[i]);
    }

    // Imprime os autovetores
    printf("Autovetores:\n");
    for (i = 0; i < NUM_SENSORS; i++)
    {
        for (j = 0; j < NUM_SENSORS; j++)
        {
            printf("%.2lf ", covarianceMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
