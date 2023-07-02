#include <stdio.h>
#include <math.h>

#define SIGNAL_LENGTH 1000     // Comprimento dos sinais
#define SIGNAL_FREQUENCY 1000  // Frequência dos sinais em Hz
#define PI 3.141592653589793

int i = 0;

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

/*int main()
{
    double signal1[SIGNAL_LENGTH];
    double signal2[SIGNAL_LENGTH];

    // Gerar sinais senoidais com defasagem angular conhecida
    for (i = 0; i < SIGNAL_LENGTH; i++)
    {
        signal1[i] = sin(2 * PI * SIGNAL_FREQUENCY * i / SIGNAL_LENGTH);
        signal2[i] = sin(2 * PI * SIGNAL_FREQUENCY * (i + 1) / SIGNAL_LENGTH);
    }

    // Estimar a defasagem angular entre os sinais
    double phaseShift = estimatePhaseShift(signal1, signal2, SIGNAL_LENGTH);

    // Converter a defasagem angular de radianos para graus
    double phaseShiftDegrees = phaseShift * 180.0 / PI;

    // Imprimir a defasagem angular estimada
    printf("Defasagem angular estimada: %.2lf graus\n", phaseShiftDegrees);

    return 0;
}
*/
