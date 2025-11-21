#include <stdio.h>

// Estrutura que guarda os dados de cada processo
typedef struct {
    char id[5];        // Nome/identificação do processo (ex: P1)
    int chegada;       // Tempo de chegada
    int burst;         // Tempo de execução (quanto tempo precisa)
    int inicio;        // Hora que começa a rodar
    int fim;           // Hora que termina
    int espera;        // Tempo de espera na fila
    int turnaround;    // Tempo total (fim - chegada)
    int concluido;     // Flag indicando se já foi executado (0 = não / 1 = sim)
} Processo;

int main() {
    int n;

    // Pergunta quantos processos o usuário vai cadastrar
    printf("Qtd de processos: ");
    scanf("%d", &n);

    Processo p[n];

    // Leitura de todos os processos
    for (int i = 0; i < n; i++) {
        printf("\nID: ");
        scanf("%s", p[i].id);

        printf("Chegada: ");
        scanf("%d", &p[i].chegada);

        printf("Burst: ");
        scanf("%d", &p[i].burst);

        // No começo, nenhum processo foi concluído
        p[i].concluido = 0;
    }

    int tempo = 0;        // Tempo atual da CPU
    int concluidos = 0;   // Quantos processos já finalizaram
    int menorBurst;       // Armazena o menor burst encontrado
    int idx;              // Índice do processo escolhido pra rodar

    // Loop principal: continua até todos os processos terminarem
    while (concluidos < n) {

        menorBurst = 999999;  // valor gigante só pra comparação
        idx = -1;             // indica que nenhum processo foi escolhido ainda

        // Procura o processo com menor burst entre os que já chegaram
        for (int i = 0; i < n; i++) {

            // Só considera quem:
            // 1. Não foi concluído
            // 2. Já chegou no sistema
            if (!p[i].concluido && p[i].chegada <= tempo) {

                // Compara o burst pra achar o menor
                if (p[i].burst < menorBurst) {
                    menorBurst = p[i].burst;
                    idx = i;  // salva o índice do menor
                }
            }
        }

        // Se nenhum processo chegou ainda, avança o tempo
        if (idx == -1) {
            tempo++;
            continue;
        }

        // Marca o momento que o processo começou a rodar
        p[idx].inicio = tempo;

        // Executa o processo até o fim (SJF não preemptivo = não interrompe)
        tempo += p[idx].burst;

        // Marca o horário que terminou
        p[idx].fim = tempo;

        // Turnaround = fim - chegada
        p[idx].turnaround = p[idx].fim - p[idx].chegada;

        // Tempo de espera = inicio - chegada
        p[idx].espera = p[idx].inicio - p[idx].chegada;

        // Marca como concluído
        p[idx].concluido = 1;
        concluidos++;
    }

    // Exibe o resultado final de todos os processos
    printf("\n=== Resultado SJF ===\n");
    for (int i = 0; i < n; i++) {
        printf("%s -> Inicio: %d | Fim: %d | Espera: %d | Turnaround: %d\n",
            p[i].id, p[i].inicio, p[i].fim, p[i].espera, p[i].turnaround);
    }

    return 0;
}
