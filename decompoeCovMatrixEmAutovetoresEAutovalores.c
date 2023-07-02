#include <stdio.h>
#include "lapacke.h"

#define NUM_SENSORS 4      // N�mero de sensores

/*

Para decompor a matriz de covari�ncia em autovetores e autovalores, voc� pode utilizar a biblioteca de �lgebra
linear chamada LAPACK (Linear Algebra PACKage) em C. A biblioteca LAPACK fornece uma s�rie de fun��es para c�lculos
matriciais, incluindo a decomposi��o espectral.

*/

int main()
{
    double covarianceMatrix[NUM_SENSORS][NUM_SENSORS];  // Matriz de covari�ncia

    // Popula a matriz de covari�ncia (exemplo hipot�tico)
    for (i = 0; i < NUM_SENSORS; i++)
    {
        for (j = 0; j < NUM_SENSORS; j++)
        {
            covarianceMatrix[i][j] = ...;  // Insira o valor da matriz de covari�ncia
        }
    }

    // Vari�veis para armazenar os resultados da decomposi��o espectral
    double eigenvalues[NUM_SENSORS];
    double eigenvectors[NUM_SENSORS][NUM_SENSORS];

    // Executa a decomposi��o espectral usando LAPACK, "U" � usado porque a matriz resultante � sim�trica, ent�o armazenamos apenas a parte triangular superior
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
