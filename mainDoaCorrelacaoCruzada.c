#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//Distância entre os microfones = Velocidade do som / (2 * Frequência do sinal)

#include <stdio.h>
#include <math.h>

#define SPEED_OF_SOUND 343.0  // Velocidade do som em metros por segundo


//Distância entre os microfones = Velocidade do som / (2 * Frequência do sinal)


// Função para estimar o ângulo de chegada
double estimateAngle(double microphoneDistance, double delay)
{
    double angle = atan(delay / (microphoneDistance * SPEED_OF_SOUND));
    return angle;
}

/*int main()
{
    double signalFrequency = 1000.0;  // Frequência do sinal em Hz
    double microphoneDistance =  SPEED_OF_SOUND/(2 * signalFrequency);  // Distância entre os microfones em metros
    double delay;                     // Atraso de tempo entre os microfones em segundos
    double angle;                     // Ângulo de chegada estimado em radianos

    // Simulação do atraso de tempo
    delay = 4;

    // Estimativa do ângulo de chegada
    angle = estimateAngle(microphoneDistance, delay);

    // Conversão do ângulo para graus
    angle = angle * 180.0 / M_PI;

    // Imprime o ângulo estimado
    printf("Ângulo estimado de chegada: %.2lf graus\n", angle);

    return 0;
}
*/

