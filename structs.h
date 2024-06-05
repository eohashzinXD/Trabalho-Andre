#include <stdlib.h>
#define MAX_LENGTH_ORIGIN 200
#define MAX_LENGTH_NAME 300
#define MAX_VETOR 100

typedef struct{
    char origem[MAX_LENGTH_ORIGIN];
    char destino[MAX_LENGTH_ORIGIN];
    float data;
    float horario;
    int assentos;
}Voo;


typedef struct{
    char nome[MAX_LENGTH_NAME];
    char segundo[MAX_LENGTH_NAME];
    char sobrenome[MAX_LENGTH_NAME];
    char ultimo[MAX_LENGTH_NAME];
    long int numero_doc;
}Passageiro;