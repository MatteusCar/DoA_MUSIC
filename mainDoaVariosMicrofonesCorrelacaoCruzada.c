#include <stdio.h>
#include <math.h>

#define SIGNAL_LENGTH 1000     // Comprimento dos sinais
#define SIGNAL_FREQUENCY 1000  // Frequ�ncia dos sinais em Hz
#define SPEED_OF_SOUND 343.0   // Velocidade do som em metros por segundo
#define PI 3.141592653589793

int i,j;

// Fun��o para calcular a defasagem angular entre dois sinais
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

// Fun��o para estimar o �ngulo de chegada
double estimateAngle(double microphoneDistance, double phaseShift)
{
    double wavelength = SPEED_OF_SOUND / SIGNAL_FREQUENCY;
    double angle = asin(phaseShift * wavelength / (2 * PI * microphoneDistance));
    
    return angle;
}

int main()
{
    int numMicrophones = 4;  // N�mero de microfones
    double signals[numMicrophones][SIGNAL_LENGTH];  // Matriz para armazenar os sinais
    double microphoneDistance = SPEED_OF_SOUND/(2*SIGNAL_FREQUENCY);  //dist�ncia entre os microfones em metros
    double phaseShifts[numMicrophones - 1];  // Vetor para armazenar as defasagens angulares
    double angles[numMicrophones - 1];  // Vetor para armazenar os �ngulos de chegada

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

    // Calcular os �ngulos de chegada estimados
    for (i = 0; i < numMicrophones - 1; i++)
    {
        angles[i] = estimateAngle(microphoneDistance, phaseShifts[i]);
    }

    // Imprimir os �ngulos de chegada estimados
    printf("�ngulos de chegada estimados:\n");
    for (i = 0; i < numMicrophones - 1; i++)
    {
        double angleDegrees = angles[i] * 180.0 / PI;
        printf("�ngulo entre os microfones %d e %d: %.2lf graus\n", i + 1, i + 2, angleDegrees);
    }

    return 0;
}

/*
Se voc� deseja captar um sinal com v�rias frequ�ncias, a escolha da dist�ncia entre os microfones pode ser um pouco mais complexa. 
Nesse caso, � importante considerar a faixa de frequ�ncia do sinal e as diferentes componentes de frequ�ncia presentes. Uma abordagem
comum � determinar a frequ�ncia mais alta presente no sinal e calcular a dist�ncia entre os microfones com base nessa frequ�ncia. 
No entanto, isso pode resultar em uma resolu��o angular adequada apenas para frequ�ncias mais altas, enquanto as componentes de frequ�ncia
mais baixas podem n�o ser bem resolvidas. Para capturar adequadamente uma faixa de frequ�ncia ampla, voc� pode adotar uma abordagem baseada
no conceito de resolu��o angular.A resolu��o angular � inversamente proporcional � dist�ncia entre os microfones. Portanto, quanto menor for
a dist�ncia entre os microfones, melhor ser� a resolu��o angular e a capacidade de distinguir �ngulos pr�ximos. Uma alternativa � usar um 
arranjo de microfones com espa�amentos diferentes entre eles, de modo a cobrir uma faixa de frequ�ncia ampla. Por exemplo, voc� pode ter um
par de microfones com uma dist�ncia menor para capturar componentes de alta frequ�ncia e outro par de microfones com uma dist�ncia maior para
capturar componentes de baixa frequ�ncia. Em resumo, ao captar um sinal com v�rias frequ�ncias, � necess�rio considerar a resolu��o angular 
desejada e a faixa de frequ�ncia do sinal. A escolha da dist�ncia entre os microfones depender� da rela��o entre esses fatores e pode envolver
o uso de arranjos de microfones com espa�amentos diferentes para cobrir uma faixa ampla de frequ�ncias.
*/

