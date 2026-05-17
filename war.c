// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        NIVEL NOVATO
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

#include <stdio.h>
#include <string.h>


//definição da struct

typedef struct {
    char nome [5];
    char cor [5];
    int tropas;
} Territorio;

int main() {
    //declaração de vetor de structs com capacidade para 5 territórios
    Territorio mapa [5];
    int i;

    //cadastro dos territórios: laço para preencher os dados
    for (i=0; i<5; i++){
        printf("\n--- Cadastro do território %d ---\n", i+1);

        printf("digite o nome do território:  ");
        scanf ("%s", mapa[i].nome); //uso de scanf conforme orientação

        printf("Digite a cor do exército:  ");
        scanf ("%s", mapa[i].cor);

        printf ("Digite a quantidade de tropas:  ");
        scanf ("%d", &mapa[i].tropas);
    }

    //exibição dos dados
    printf("\n\n=== DADOS DOS TERRITÓRIOS CADASTRADOS ===\n");
    for (i=0; i<5; i++){
        printf("Território %s | Cor: %s | Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    return 0;
}
