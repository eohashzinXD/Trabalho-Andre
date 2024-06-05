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
            fazerReserva(&pessoas);
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

void fazerReserva(Passageiro *pessoas){
    fflush(stdin);
    printf("Digite seu nome completo: \n");
    if (fgets(pessoas->nome, sizeof(pessoas->nome), stdin) != NULL)
    {
        size_t len = strlen(pessoas->nome);
        if (len > 0 && pessoas->nome[len - 1] == '\n')
        {
            pessoas->nome[len - 1] = '\0';
        }
    }
    fflush(stdin);
    printf("Digite seu numero de documento(000.000.000.00):\n");
    if (fgets(pessoas->numero_doc, sizeof(pessoas->numero_doc), stdin) != NULL)
    {
        size_t len = strlen(pessoas->numero_doc);
        if (len > 0 && pessoas->numero_doc[len - 1] == '\n')
        {
            pessoas->numero_doc[len - 1] = '\0';
        }
    }
    menu();
    //printf("Nome: %s\nNumero Doc: %s\n", pessoas->nome, pessoas->numero_doc);
}

int main(int argc, char const *argv[])
{
    Passageiro pessoas;
    menu();
    
    return 0;
}
