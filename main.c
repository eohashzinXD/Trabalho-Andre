#include <stdio.h>
#include "structs.h"
#include <string.h>

void menu(){
    Passageiro pessoas;
    int op = -1;

    printf("Digite uma opcao: \n");
    printf("1 - Consultar Passagens Disponiveis\n");
    printf("2 - Fazer Reserva\n");
    printf("3 - Listar Reservas\n");
    printf("4 - Cancelar Reserva\n");
    printf("5 - Sair\n");
    scanf("%d", &op);

    do
    {
        switch (op)
        {
        case 1:
            //vooDispo();
            break;
        case 2:
            fazerReserva(&pessoas, "passageiros.txt");
            break;
        case 3:
            //listarReservas();
            break;
        case 4:
            //cancelarReserva();
            break;
        case 5:
            break;
        
        default:
            printf("Opcao invalida");
            break;
        }
    } while (op != 5);
}

int fazerReserva(Passageiro *pessoas, const char* filename){
    Passageiro unico;
    char *caractere_nao_convertido;

    char linha[256];
    char nome[200];
    char sobrenome[200];
    char sobrenome_sobre[200];
    char ultimo_nome[200];
    char doc[20];

    FILE *txtFile = fopen(filename, "r");
    if (!txtFile)
    {
        return 1;
    }

    int count = 0;
    while (fgets(linha, sizeof(linha), txtFile))
    {
        sscanf(linha, "%s %s %s %s %s\n", nome, sobrenome, sobrenome_sobre, ultimo_nome, doc);

        unico.numero_doc = strtol(doc, &caractere_nao_convertido, 10);
        snprintf(unico.nome, sizeof(unico.nome), "%s", nome);
        snprintf(unico.segundo, sizeof(unico.segundo), "%s", sobrenome);
        snprintf(unico.sobrenome, sizeof(unico.sobrenome), "%s", sobrenome_sobre);
        snprintf(unico.ultimo, sizeof(unico.ultimo), "%s", ultimo_nome);
        printf("%s\n", doc);

        pessoas[count] = unico;
        //printf("Reg Nome: %s %s %s %s\nNumero Doc: %ld\n", pessoas[count].nome,pessoas[count].segundo,pessoas[count].sobrenome,pessoas[count].ultimo, pessoas[count].numero_doc);
        count++;
    }
    fclose(txtFile);
    
    return count;
}

int main(int argc, char const *argv[])
{
    Passageiro pessoas[MAX_VETOR];
    
    fazerReserva(pessoas, "passageiros.txt");
    
    
    //menu();
    
    return 0;
}
