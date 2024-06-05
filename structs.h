#include <stdlib.h>
#define MAX_LENGTH_ORIGIN 200
#define MAX_LENGTH_NAME 300

typedef struct{
    char origem[MAX_LENGTH_ORIGIN];
    char destino[MAX_LENGTH_ORIGIN];
    float data;
    float horario;
    int assentos;
}Voo;


typedef struct{
    char nome[MAX_LENGTH_NAME];
    char numero_doc[15];
}Passageiro;