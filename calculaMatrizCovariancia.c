#include <stdio.h>

#define NUM_SAMPLES 1000   // N�mero de amostras
#define NUM_SENSORS 4      // N�mero de sensores

// Fun��o para calcular a m�dia dos valores de um vetor
double calculateMean(double* data, int length)
{
    double sum = 0.0;
    for (i = 0; i < length; i++)
    {
        sum += data[i];
    }
    return sum / length;
}

// Fun��o para calcular a matriz de covari�ncia

/*
Aqui cada sensor � uma linha da matriz, ou seja, o n�mero de linhas � o n�mero de sensores e o n�mero de colunas �
o n�mero de pontos em que o sinal foi amostrado. Todos os sinais tem o mesmo n�mero de pontos
*/
void calculateCovarianceMatrix(double** sensorData, int numSamples, int numSensors, double** covarianceMatrix)
{
    // Calcula as m�dias dos sinais em cada sensor
    double means[numSensors];
    for (i = 0; i < numSensors; i++)
    {
        means[i] = calculateMean(sensorData[i], numSamples);
    }

    // Inicializa a matriz de covari�ncia com zeros
    for (i = 0; i < numSensors; i++)
    {
        for (j = 0; j < numSensors; j++)
        {
            covarianceMatrix[i][j] = 0.0;
        }
    }

    // Calcula os elementos da matriz de covari�ncia
    for (i = 0; i < numSensors; i++)
    {
        for (j = 0; j < numSensors; j++)
        {
            for (k = 0; k < numSamples; k++)
            {
                covarianceMatrix[i][j] += (sensorData[i][k] - means[i]) * (sensorData[j][k] - means[j]);
            }
            covarianceMatrix[i][j] /= (numSamples - 1);
        }
    }
}

int main()
{
    double sensorData[NUM_SENSORS][NUM_SAMPLES];     // Matriz para armazenar os dados dos sensores sensors[4][256] para 4 microfones e 256 amostras
    double covarianceMatrix[NUM_SENSORS][NUM_SENSORS];  // Matriz de covari�ncia

    // Popula a matriz de dados dos sensores (exemplo hipot�tico)
    for (i = 0; i < NUM_SENSORS; i++)
    {
        for (j = 0; j < NUM_SAMPLES; j++)
        {
            // Aqui voc� pode inserir os dados reais coletados pelos sensores
            sensorData[i][j] = ...;  // Insira o valor do sensor i na amostra j
        }
    }

    // Calcula a matriz de covari�ncia
    calculateCovarianceMatrix(sensorData, NUM_SAMPLES, NUM_SENSORS, covarianceMatrix);

    // Imprime a matriz de covari�ncia
    printf("Matriz de covari�ncia:\n");
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

