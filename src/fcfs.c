#include <stdio.h>

typedef struct{
    int ID;
    char Nome[30];
    int chegada;
    int espera;
    int tempoleva;
    int tempototal;
}processo;

int main(){
    int quantidade;

    printf("Quantos pessoas estao na fila?");
    scanf("%d", &quantidade);
    do {
            printf("Quantos pessoas estao na fila?");
            scanf("%d", &quantidade);
            if (quantidade < 0){
                printf("ERRO: chegada nao pode ser negativa.\n");
            }
        } while(quantidade < 0);

    processo fila[quantidade];
    for(int i = 0; i<quantidade ; i++){
        fila[i].ID = i + 1;
        printf("Qual o nome da pessoa?\n");
        scanf("%29s", fila[i].Nome);

        do {
            printf("Qual posicaoo chegou?\n");
            scanf("%d", &fila[i].chegada);
            if (fila[i].chegada < 0){
                printf("ERRO: chegada nao pode ser negativa.\n");
            }
        } while(fila[i].chegada < 0);


        do {
            printf("Quanto tempo leva o atendimento?\n");
            scanf("%d", &fila[i].tempoleva);
            if (fila[i].tempoleva < 0){
                printf("ERRO: tempo nao pode ser negativo.\n");
            }
        } while(fila[i].tempoleva < 0);
    }

    for(int i = 0; i<quantidade - 1; i++){
        for(int j = 0; j<quantidade - 1 - i; j++){
            if(fila[j].chegada >  fila[j+1].chegada){
                processo auxilio = fila[j];
                fila[j] = fila[j+1];
                fila[j+1] = auxilio;
            }  
        }
    }
    // auxilia na atribuicao de tempo total e de espera
    int tempoAtual = 0;

    for(int i = 0; i < quantidade; i++) {
        if(fila[i].chegada > tempoAtual) {
            tempoAtual = fila[i].chegada;
        }

        fila[i].espera = tempoAtual - fila[i].chegada;
        fila[i].tempototal = fila[i].espera + fila[i].tempoleva;

        tempoAtual= tempoAtual + fila[i].tempoleva;
    }

// Tabela final com nome incluído
    printf("\nID |   Nome          | Chegada | Burst | Espera | Turnaround\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < quantidade; i++) {
        printf("%2d | %-14s | %7d | %5d | %6d | %10d\n",
            fila[i].ID,
            fila[i].Nome,
            fila[i].chegada,
            fila[i].tempoleva,
            fila[i].espera,
            fila[i].tempototal
        );
    }

    return 0;
}
