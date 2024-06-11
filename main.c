#include "structs.h"

int carregarPassageiros(Passageiros *pessoas, const char *filename){
    Passageiros unico;
    char linha[118];
    char nome[200];
    char nDoc[7];
    char *caractere_nao_coonvertido;

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo!");
        return 1;
    }

    int count = 0;
    while (fgets(linha, sizeof(linha), file))
    {
        sscanf(linha, "%s %s\n", nome, nDoc);
        

        unico.numDoc = strtol(nDoc, &caractere_nao_coonvertido, 10);
        snprintf(unico.nome, sizeof(unico.nome), "%s", nome);

        pessoas[count] = unico;
        //printf("%s %s\n", nome, nDoc); //para debug
        //printf("Reg: %s %d\n", pessoas[count].nome, pessoas[count].numDoc);//debug reg
        count++;
    }
    
    fclose(file);
    return count;
}

int carregarVoos(Voos *voo, const char *filename){
    Voos unico;
    int count = 0;
    char *caractere_nao_convertido;
    char linha[556], origem[15], destino[15], string_data[11], string_hora[6], assentos[4];
    char dia[3], mes[3], ano[5], hora[3], min[4];
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo de voo");
        return -2;
    }

    while (fgets(linha, sizeof(linha), file))
    {
        sscanf(linha, "%s %s %s %s %s", origem, destino, string_data, string_hora, assentos);
        //printf("Linha: %s %s %s %s %s\n", origem, destino, string_data, string_hora, assentos); 

        sscanf(string_data, "%2[0-9]/%2[0-9]/%4[0-9]", dia, mes, ano);
        sscanf(string_hora, "%2[0-9]:%2[0-9]", hora, min);
        //printf("Data: %2s/%2s/%4s\n", dia, mes, ano);
        unico.assentosDispo = strtol(assentos, &caractere_nao_convertido, 10);
        unico.dia = strtol(dia, &caractere_nao_convertido, 10);
        unico.mes = strtol(mes, &caractere_nao_convertido, 10);
        unico.ano = strtol(ano, &caractere_nao_convertido, 10);
        unico.hora = strtol(hora, &caractere_nao_convertido, 10);
        unico.min = strtol(min, &caractere_nao_convertido, 10);
        snprintf(unico.origem, sizeof(unico.origem), "%s", origem);
        snprintf(unico.destino, sizeof(unico.destino), "%s", destino);

        //printf("Reg %d/%d/%d %s %s %d:%d %d\n", unico.dia, unico.mes, unico.ano, unico.origem, unico.destino, unico.hora, unico.min, unico.assentosDispo);

        voo[count] = unico;
        count++;
    }
    fclose(file);
    return count;

    
}

void fazerReservas(Passageiros *pessoas,int numPassageiros, Voos *voo, int numVoos, Reserva *reservas, int *numReservas){
    int idPass = 0, idvoo = 0;
    //printf("Id Passageiro: %d\n", numPassageiros );//debug
    fflush(stdin);
    printf("Digite o ID do passageiro (0 a %d):", numPassageiros - 1);
    idPass = input_d("");
    //printf("Id Passageiro: %d\n", idPass);//debug
    if (idPass < 0 || idPass >= numPassageiros)
    {
        printf("ID do Passageiro Invalido!");
        return;
    }
    fflush(stdin);
    printf("Digite o ID do voo (0 a %d):", numVoos - 1);
    idvoo = input_d("");
    //printf("Id Voo: %d\n", idvoo);//debug
    if (idvoo < 0 || idvoo >= numVoos)
    {
        printf("ID do Voo Invalido!");
        return;
    }
    if (voo[idvoo].assentosDispo > 0) {
        voo[idvoo].assentosDispo--;
        reservas[*numReservas].idPassageiro = idPass;
        reservas[*numReservas].idVoo = idvoo;
        (*numReservas)++;

        printf("Reserva feita com sucesso!\n");
    
    } else {
        printf("N?o h? assentos dispon?veis para este voo!\n");
    }
}

void consultarVoos(Voos *voo, int *numVoos){
    for (int i = 0; i < numVoos; i++)
    {
        printf("\nOrigem: %s\n Destino: %s\n Data: %2d/%1d/%4d\n Hora: %2d:%1d\n Assentos Disponiveis: %d\n", voo[i].origem, voo[i].destino, voo[i].dia, voo[i].mes, voo[i].ano, voo[i].hora, voo[i].min, voo[i].assentosDispo);
    }
    
}

void excluirReserva(Passageiros *pessoas, Voos *voo, Reserva *reservas, int *numReservas){
    int idPass, idVoo, vooParaExcluir;

    printf("Digite o ID do passageiro para excluir a reserva (0 a %d)", MAX_PESSOAS - 1);
    idPass = input_d("");

    if (idPass < 0 || idPass >= MAX_PESSOAS)
    {
        printf("ID do Passageiro Invalido!\n");
        return;
    }

    printf("Voos reservados pelo passageiro %s (ID %d):\n", pessoas[idPass].nome, idPass);
    int voosReservados[MAX_PESSOAS];
    int numVoosReservados = 0;

    for (int i = 0; i < *numReservas; i++) {
        if (reservas[i].idPassageiro == idPass) {
            voosReservados[numVoosReservados] = i;
            printf("Voo %d: Origem: %s, Destino: %s, Data: %02d/%02d/%04d, Hora: %02d:%02d\n", 
                   numVoosReservados + 1,
                   voo[reservas[i].idVoo].origem,
                   voo[reservas[i].idVoo].destino,
                   voo[reservas[i].idVoo].dia,
                   voo[reservas[i].idVoo].mes,
                   voo[reservas[i].idVoo].ano,
                   voo[reservas[i].idVoo].hora,
                   voo[reservas[i].idVoo].min);
            numVoosReservados++;
        }
    }
    if (numVoosReservados == 0)
    {
        printf("Nenhuma reserva encontrada para o passgeiro informado!\n");
        return;
    }
    printf("Digite o número do voo que deseja excluir (1 a %d): ", numVoosReservados);
    vooParaExcluir = input_d("");

    if(vooParaExcluir < 1 || vooParaExcluir > numVoosReservados){
        printf("Numero do voo invalido!\n");
        return;
    }
    
    int reservaIndex = voosReservados[vooParaExcluir - 1];
    int idVooParaExcluir = reservas[reservaIndex]. idVoo;

    voo[idVooParaExcluir].assentosDispo++;

    for (int j = reservaIndex; j < *numReservas - 1; j++){
        reservas[j] = reservas[j + 1];
    }

    (*numReservas)--;
    printf("Reserva excluída com sucesso!\n");
}

void listarReservas(Reserva *reservas, int numReservas, Passageiros *pessoas, int numPassageiros, Voos *voo, int numVoos){
    int idPass;
    printf("Digite o ID do passageiro (0 a %d):", numPassageiros - 1);
    idPass = input_d("");

    if (idPass < 0 || idPass >= numPassageiros)
    {
        printf("ID do Passageiro Invalido!\n");
        return;
    }

    printf("Reservas para o passageiro %s (Documento: %d):\n", pessoas[idPass].nome, pessoas[idPass].numDoc);
    int reservasEncontradas = 0;
    for (int i = 0; i < numReservas; i++)
    {
        if (reservas[i].idPassageiro == idPass)
        {
            int idVoo = reservas[i].idVoo;
            printf("\nVoo %d:\n", i+1);
            printf("Origem: %s\n", voo[idVoo].origem);
            printf("Destino: %s\n", voo[idVoo].destino);
            printf("Data: %02d/%02d/%04d\n", voo[idVoo].dia, voo[idVoo].mes, voo[idVoo].ano);
            printf("Hora: %02d:%02d\n", voo[idVoo].hora, voo[idVoo].min);
            printf("Assentos Disponiveis: %d\n", voo[idVoo].assentosDispo);
            reservasEncontradas++;
        }
    }
    if (reservasEncontradas == 0)
    {
        printf("Nenhuma reserva encontrada para o passageiro informado!\n");
    }
    
    
    
}

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Portuguese");
    Passageiros pessoas[MAX_PESSOAS];
    Voos voo[MAX_PESSOAS];
    Reserva reservas[MAX_PESSOAS];
    int count = 0;
    int numPassageiros = 0;
    int numVoos = 0;
    int numReservas = 0;
    
    numVoos = carregarVoos(voo, "voos.txt");
    if (numVoos < 0) return 1;
    numPassageiros = carregarPassageiros(pessoas, "passageiros.txt");
    if (numPassageiros < 0) return 1;
    //printf("NumPassageiros: %d %d\n", numPassageiros - 1, numVoos);
    //fazerReservas(pessoas, &numPassageiros, voo, &numVoos, reservas, numReservas);
    //printf("%d", numReservas);


    int op = -1;
    // caso o usuario digite qualquer numero diferente de 5 o menu continuara rodando em loop ate que o 5 seja digitado que ? a unica condi??o de parada
    while (op != 6) {
        do {
            printf("***************************************************************************************\n");
            printf(" 1 - Fazer Reserva do Voo                                                              \n");
            printf(" 2 - Consultar Voos Disponiveis                                                        \n");
            printf(" 3 - Listar Reservas                                                                   \n");
            printf(" 4 - Excluir Reservas                                                                  \n");
            printf(" 5 - Sair.                                                                             \n");
            printf("***************************************************************************************\n");
            op = input_d("Digite um numero entre: [1-5]: ");
        } while (op < 1 || op > 5);

        switch (op) {
            case 1:
                fazerReservas(pessoas, numPassageiros, voo, numVoos, reservas, &numReservas);
                break;
            case 2:
                consultarVoos(voo, numVoos);
                break;
            case 3:
                listarReservas(reservas, numReservas, pessoas, numPassageiros, voo, numVoos);
                break;
            case 4:
                excluirReserva(pessoas, voo, reservas, &numReservas);
                break;
            case 5:
                printf("Saindo...\n");
                return;
        }
    }
    return 0;
}
