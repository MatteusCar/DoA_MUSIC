#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//Dist�ncia entre os microfones = Velocidade do som / (2 * Frequ�ncia do sinal)

#include <stdio.h>
#include <math.h>

#define SPEED_OF_SOUND 343.0  // Velocidade do som em metros por segundo


//Dist�ncia entre os microfones = Velocidade do som / (2 * Frequ�ncia do sinal)


// Fun��o para estimar o �ngulo de chegada
double estimateAngle(double microphoneDistance, double delay)
{
    double angle = atan(delay / (microphoneDistance * SPEED_OF_SOUND));
    return angle;
}

/*int main()
{
    double signalFrequency = 1000.0;  // Frequ�ncia do sinal em Hz
    double microphoneDistance =  SPEED_OF_SOUND/(2 * signalFrequency);  // Dist�ncia entre os microfones em metros
    double delay;                     // Atraso de tempo entre os microfones em segundos
    double angle;                     // �ngulo de chegada estimado em radianos

    // Simula��o do atraso de tempo
    delay = 4;

    // Estimativa do �ngulo de chegada
    angle = estimateAngle(microphoneDistance, delay);

    // Convers�o do �ngulo para graus
    angle = angle * 180.0 / M_PI;

    // Imprime o �ngulo estimado
    printf("�ngulo estimado de chegada: %.2lf graus\n", angle);

    return 0;
}
*/

