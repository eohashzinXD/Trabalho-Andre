#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <limits.h>
#include <inttypes.h>
#include <errno.h>
#include <float.h>
#include "pss.h"

#define MAX_PESSOAS 30
#define MAX_NAME 100
#define MAX_ORIGIN_DESTINY 200

typedef struct{
    char nome[MAX_NAME];
    long int numDoc;
} Passageiros;

typedef struct {
    char origem[MAX_ORIGIN_DESTINY];
    char destino[MAX_ORIGIN_DESTINY];
    int dia, mes, ano;
    int hora;
    int min;
    int assentosDispo;
}Voos;

typedef struct {
    int idPassageiro;
    int idVoo;
}Reserva;

void limpa_buffer() {
    int lixo;
    while ((lixo = getchar()) != '\n' && lixo != '\r' && lixo != EOF);
}

char input_c(const char *mensagem) {
    char x;
    do {
        printf("%s", mensagem);
        x = fgetc(stdin); 
        if (x == '\n') continue;
        if (x != EOF) limpa_buffer();
    } while (x == '\n' || x == EOF); 
    return x;
}

void input_s(const char *mensagem, char *x, int tamanho) {	
    do {
        printf("%s", mensagem);
        if (fgets(x, tamanho,stdin) != NULL) 
            x[strcspn(x, "\n")] = '\0';
    } while (strlen(x) == 0);
    if ( strlen(x) == tamanho - 1 ) limpa_buffer();    
}

int input_d(const char *mensagem) {
    char aux[1024];
    char *endptr;
    int x;
    intmax_t temp;
    do{
        input_s(mensagem,aux, sizeof(aux));
        temp = strtoimax(aux, &endptr, 10);
        if ((temp == INTMAX_MIN || temp == INTMAX_MAX) && errno == ERANGE) temp = INT_MAX;
        x = (int)temp;
    }while(*endptr != '\0');
    return x;
}

float input_f(const char *mensagem) {
    char aux[1024];
    char *endptr;
    float x;
    do{
        input_s(mensagem, aux, sizeof(aux));
        x = strtof(aux, &endptr);
        if ((x < FLT_MIN || x > FLT_MAX)) x = FLT_MAX;
    }while(*endptr != '\0');
    return x;
}

long int  input_ld(const char *mensagem) {
    char aux[1024];
    char *endptr;
    long int x;
    do{
        input_s(mensagem, aux, sizeof(aux));
        x = strtol(aux, &endptr, 10);
        if ((x < LONG_MIN || x > LONG_MAX)) x = LONG_MAX;
    }while(*endptr != '\0');
    return x;
}

double input_lf(const char *mensagem) {
    char aux[1024];
    char *endptr;
    double x;
    do{
        input_s(mensagem, aux, sizeof(aux));
        x = strtod(aux, &endptr); 
        if ((x < DBL_MIN || x > DBL_MAX)) x = DBL_MAX;
    }while(*endptr != '\0');
	return x; 
}

long double input_Lf(const char *mensagem) {
    char aux[5120];
    char *endptr;
    long double x;
    do{
        input_s(mensagem, aux, sizeof(aux));
        x = strtold(aux, &endptr); 
        if ((x < LDBL_MIN || x > LDBL_MAX)) x = LDBL_MAX;
    }while(*endptr != '\0'); 
    return x; 
}
