#include <stdio.h>
#include <math.h>

#define SIGNAL_LENGTH 1000     // Comprimento dos sinais
#define SIGNAL_FREQUENCY 1000  // Frequência dos sinais em Hz
#define SPEED_OF_SOUND 343.0   // Velocidade do som em metros por segundo
#define PI 3.141592653589793

int i,j;

// Função para calcular a defasagem angular entre dois sinais
double estimatePhaseShift(double* signal1, double* signal2, int length)
{
    double sumReal = 0.0;
    double sumImag = 0.0;

    for (i = 0; i < length; i++)
    {
        sumReal += signal1[i] * signal2[i];
        sumImag += signal1[i] * signal2[i + 1];
    }

    double phaseShift = atan2(sumImag, sumReal);

    return phaseShift;
}

// Função para estimar o ângulo de chegada
double estimateAngle(double microphoneDistance, double phaseShift)
{
    double wavelength = SPEED_OF_SOUND / SIGNAL_FREQUENCY;
    double angle = asin(phaseShift * wavelength / (2 * PI * microphoneDistance));
    
    return angle;
}

int main()
{
    int numMicrophones = 4;  // Número de microfones
    double signals[numMicrophones][SIGNAL_LENGTH];  // Matriz para armazenar os sinais
    double microphoneDistance = SPEED_OF_SOUND/(2*SIGNAL_FREQUENCY);  //distância entre os microfones em metros
    double phaseShifts[numMicrophones - 1];  // Vetor para armazenar as defasagens angulares
    double angles[numMicrophones - 1];  // Vetor para armazenar os ângulos de chegada

    // Gerar sinais senoidais com defasagens angulares conhecidas
    for (i = 0; i < SIGNAL_LENGTH; i++)
    {
        for (j = 0; j < numMicrophones; j++)
        {
            signals[j][i] = sin(2 * PI * SIGNAL_FREQUENCY * (j + 1) * i / SIGNAL_LENGTH);
        }
    }

    // Estimar as defasagens angulares entre os sinais
    for (i = 0; i < numMicrophones - 1; i++)
    {
        phaseShifts[i] = estimatePhaseShift(signals[i], signals[i + 1], SIGNAL_LENGTH);
    }

    // Calcular os ângulos de chegada estimados
    for (i = 0; i < numMicrophones - 1; i++)
    {
        angles[i] = estimateAngle(microphoneDistance, phaseShifts[i]);
    }

    // Imprimir os ângulos de chegada estimados
    printf("Ângulos de chegada estimados:\n");
    for (i = 0; i < numMicrophones - 1; i++)
    {
        double angleDegrees = angles[i] * 180.0 / PI;
        printf("Ângulo entre os microfones %d e %d: %.2lf graus\n", i + 1, i + 2, angleDegrees);
    }

    return 0;
}

/*
Se você deseja captar um sinal com várias frequências, a escolha da distância entre os microfones pode ser um pouco mais complexa. 
Nesse caso, é importante considerar a faixa de frequência do sinal e as diferentes componentes de frequência presentes. Uma abordagem
comum é determinar a frequência mais alta presente no sinal e calcular a distância entre os microfones com base nessa frequência. 
No entanto, isso pode resultar em uma resolução angular adequada apenas para frequências mais altas, enquanto as componentes de frequência
mais baixas podem não ser bem resolvidas. Para capturar adequadamente uma faixa de frequência ampla, você pode adotar uma abordagem baseada
no conceito de resolução angular.A resolução angular é inversamente proporcional à distância entre os microfones. Portanto, quanto menor for
a distância entre os microfones, melhor será a resolução angular e a capacidade de distinguir ângulos próximos. Uma alternativa é usar um 
arranjo de microfones com espaçamentos diferentes entre eles, de modo a cobrir uma faixa de frequência ampla. Por exemplo, você pode ter um
par de microfones com uma distância menor para capturar componentes de alta frequência e outro par de microfones com uma distância maior para
capturar componentes de baixa frequência. Em resumo, ao captar um sinal com várias frequências, é necessário considerar a resolução angular 
desejada e a faixa de frequência do sinal. A escolha da distância entre os microfones dependerá da relação entre esses fatores e pode envolver
o uso de arranjos de microfones com espaçamentos diferentes para cobrir uma faixa ampla de frequências.
*/

