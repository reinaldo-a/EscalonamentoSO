#include <stdio.h>

int main() {
    int n;

    printf("Quantidade de processos: ");
    scanf("%d", &n);

    int pid[n];        
    int burst[n];      
    int prioridade[n]; 
    int espera[n];     
    int retorno[n];    

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcesso P%d\n", pid[i]);
        printf("Tempo de execucao (burst): ");
        scanf("%d", &burst[i]);
        printf("Prioridade (menor numero = maior prioridade): ");
        scanf("%d", &prioridade[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (prioridade[j] < prioridade[i]) {
                int temp = prioridade[i];
                prioridade[i] = prioridade[j];
                prioridade[j] = temp;

                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    espera[0] = 0;
    for (int i = 1; i < n; i++) {
        espera[i] = espera[i - 1] + burst[i - 1];
    }

    for (int i = 0; i < n; i++) {
        retorno[i] = espera[i] + burst[i];
    }

    printf("\n===== ORDEM DE EXECUCAO =====\n");
    for (int i = 0; i < n; i++) {
        printf("P%d (Prioridade: %d) -> ", pid[i], prioridade[i]);
    }

    printf("\n\n===== TABELA FINAL =====\n");
    printf("PID\tBurst\tPrioridade\tEspera\tRetorno\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\n",
               pid[i], burst[i], prioridade[i], espera[i], retorno[i]);
    }

    return 0;
}
