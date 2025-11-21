#include <stdio.h>
#define MAX_PROCESSOS 5

typedef struct {
    int id;
    int tempo_restante;
} Processo;

void escalona_round_robin(Processo processos[], int n, int quantum) {
    Processo fila[MAX_PROCESSOS];
    int frente = 0, cauda = n, tempo_atual = 0; 
    
    for (int i = 0; i < n; i++) { 
        fila[i] = processos[i];
    }
    
    while (frente != cauda) {
        Processo atual = fila[frente];
        frente = (frente + 1) % MAX_PROCESSOS;
        
        int execucao = (atual.tempo_restante > quantum) ? quantum : atual.tempo_restante;
        
        tempo_atual += execucao;
        atual.tempo_restante -= execucao;
        
        printf("P%d executa %dms (Total: %dms)\n", atual.id, execucao, tempo_atual);
        
        if (atual.tempo_restante > 0) {
            fila[cauda] = atual;
            cauda = (cauda + 1) % MAX_PROCESSOS; 
        } else {
            printf("--- P%d CONCLUÍDO ---\n", atual.id);
        }
    }
}

int main() {
    Processo p[] = {{1, 10}, {2, 5}, {3, 15}};
    escalona_round_robin(p, 3, 4); 
}
