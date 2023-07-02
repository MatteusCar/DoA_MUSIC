#include <stdio.h>
#include <math.h>

#define NUM_MICROPHONES 4
#define ANGLE_MIN -90
#define ANGLE_MAX 90
#define ANGLE_RESOLUTION 0.01
#define FREQUENCY 5000
#define SPEED_OF_SOUND 343

void constructMUSIC(float eigenvalues[NUM_MICROPHONES], float eigenvectors[NUM_MICROPHONES][NUM_MICROPHONES], float spectrum[(int)((ANGLE_MAX - ANGLE_MIN) / ANGLE_RESOLUTION) + 1])
{
    float angle;
    float steeringVector[NUM_MICROPHONES];
	float deltaD = SPEED_OF_SOUND/(FREQUENCY*2*sin(ANGLE_RESOLUTION)); //dist�ncia entre os microfones
	float lambda = SPEED_OF_SOUND/FREQUENCY;
	
    int index = 0;

    for (angle = ANGLE_MIN; angle <= ANGLE_MAX; angle += ANGLE_RESOLUTION)
    {
        float phase = angle * M_PI / 180.0;
		phase = 2*M_PI*deltaD*sin(phase)/lambda; //calcula a defafasem angular e insere em phase mesmo 
		
        for (int i = 0; i < NUM_MICROPHONES; i++)
        {
            // Dist�ncia entre os microfones. Ao multiplicar o denominador por 2, estamos levando em conta que a dist�ncia entre os microfones � igual a metade do comprimento de onda para cada �ngulo em fun��o da resolu��o desejada.
            steeringVector[i] = cos(i*phase);
        }

        float spectrumValue = 0.0;

        for (int i = 0; i < NUM_MICROPHONES; i++)
        {
            float dotProduct = 0.0;

            for (int j = 0; j < NUM_MICROPHONES; j++)
            {
                dotProduct += eigenvectors[j][i] * steeringVector[j];
            }

            spectrumValue += powf(fabs(dotProduct), 2) / eigenvalues[i]; //dividi pois se o autovalor for baixo ent�o � ru�do, isso vai ajudar a distinguir, caso contr�rio se o autovalor for alto, � sinal, tamb�m vai ajudar ainda mais a distinguir o valor do espectro
        }

        spectrum[index] = 1.0 / spectrumValue;
        index++;
    }
}

void findPeakDirections(float spectrum[], int spectrumSize, float threshold)
{
    for (int i = 1; i < spectrumSize - 1; i++)
    {
        if (spectrum[i] > spectrum[i - 1] && spectrum[i] > spectrum[i + 1] && spectrum[i] > threshold)
        {
            float angle = ANGLE_MIN + i * ANGLE_RESOLUTION;
            printf("Pico encontrado em %.2f graus\n", angle);
        }
    }
}

int main()
{
    // Exemplo de matriz de autovalores e autovetores (substitua com os valores corretos)
    float eigenvalues[NUM_MICROPHONES] = {0.5, 0.3, 0.2, 0.1};
    float eigenvectors[NUM_MICROPHONES][NUM_MICROPHONES] = {{0.1, 0.2, 0.3, 0.4},
                                                            {0.4, 0.3, 0.2, 0.1},
                                                            {0.2, 0.3, 0.4, 0.5},
                                                            {0.5, 0.4, 0.3, 0.2}};

    float spectrum[(int)((ANGLE_MAX - ANGLE_MIN) / ANGLE_RESOLUTION) + 1];

    constructMUSIC(eigenvalues, eigenvectors, spectrum);

    // Encontra os picos do espectro
    findPeakDirections(spectrum, (int)((ANGLE_MAX - ANGLE_MIN) / ANGLE_RESOLUTION) + 1, 0.5);

    return 0;
}

