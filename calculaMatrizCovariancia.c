#include <stdio.h>

#define NUM_SAMPLES 1000   // Número de amostras
#define NUM_SENSORS 4      // Número de sensores

// Função para calcular a média dos valores de um vetor
double calculateMean(double* data, int length)
{
    double sum = 0.0;
    for (i = 0; i < length; i++)
    {
        sum += data[i];
    }
    return sum / length;
}

// Função para calcular a matriz de covariância

/*
Aqui cada sensor é uma linha da matriz, ou seja, o número de linhas é o número de sensores e o número de colunas é
o número de pontos em que o sinal foi amostrado. Todos os sinais tem o mesmo número de pontos
*/
void calculateCovarianceMatrix(double** sensorData, int numSamples, int numSensors, double** covarianceMatrix)
{
    // Calcula as médias dos sinais em cada sensor
    double means[numSensors];
    for (i = 0; i < numSensors; i++)
    {
        means[i] = calculateMean(sensorData[i], numSamples);
    }

    // Inicializa a matriz de covariância com zeros
    for (i = 0; i < numSensors; i++)
    {
        for (j = 0; j < numSensors; j++)
        {
            covarianceMatrix[i][j] = 0.0;
        }
    }

    // Calcula os elementos da matriz de covariância
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
    double covarianceMatrix[NUM_SENSORS][NUM_SENSORS];  // Matriz de covariância

    // Popula a matriz de dados dos sensores (exemplo hipotético)
    for (i = 0; i < NUM_SENSORS; i++)
    {
        for (j = 0; j < NUM_SAMPLES; j++)
        {
            // Aqui você pode inserir os dados reais coletados pelos sensores
            sensorData[i][j] = ...;  // Insira o valor do sensor i na amostra j
        }
    }

    // Calcula a matriz de covariância
    calculateCovarianceMatrix(sensorData, NUM_SAMPLES, NUM_SENSORS, covarianceMatrix);

    // Imprime a matriz de covariância
    printf("Matriz de covariância:\n");
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

