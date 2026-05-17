#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura (struct) para representar cada território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void cadastrarTerritorios(Territorio* mapa, int total);
void exibirTerritorios(Territorio* mapa, int total);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

// --- FUNÇÃO PRINCIPAL ---
int main() {
    int totalTerritorios;
    
    // Configura o gerador de números aleatórios com base no relógio do computador
    srand(time(NULL));

    printf("=== BEM-VINDO AO WAR ESTRUTURADO ===\n");
    printf("Quantos territorios deseja cadastrar no jogo? ");
    scanf("%d", &totalTerritorios);
    
    // Limpar o buffer do teclado após ler o número
    fflush(stdin); 

    // ALOCAÇÃO DINÂMICA: Aloca espaço para o vetor de territórios
    // calloc limpa a memória, definindo números como 0 e strings como vazias
    Territorio* mapa = (Territorio*) calloc(totalTerritorios, sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro Crítico: Memoria insuficiente!\n");
        return 1; // Fecha o programa com erro
    }

    // Executa o registo inicial dos territórios
    cadastrarTerritorios(mapa, totalTerritorios);

    int opcao = 1;
    while (opcao != 0) {
        printf("\n--- MENU DE GUERRA ---\n");
        printf("1. Ver mapa de territorios\n");
        printf("2. Realizar um Ataque\n");
        printf("0. Sair do Jogo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirTerritorios(mapa, totalTerritorios);
        } 
        else if (opcao == 2) {
            int idAtacante, idDefensor;
            
            exibirTerritorios(mapa, totalTerritorios);
            
            printf("\nEscolha o ID do territorio ATACANTE: ");
            scanf("%d", &idAtacante);
            printf("Escolha o ID do territorio DEFENSOR: ");
            scanf("%d", &idDefensor);

            // VALIDAÇÃO 1: Verificar se os IDs existem no vetor
            if (idAtacante < 0 || idAtacante >= totalTerritorios || idDefensor < 0 || idDefensor >= totalTerritorios) {
                printf("\n[ERRO] ID invalido! Escolha IDs que aparecem na lista.\n");
                continue;
            }

            // Usamos ponteiros para apontar diretamente para os territórios escolhidos
            Territorio* atq = &mapa[idAtacante];
            Territorio* dfs = &mapa[idDefensor];

            // VALIDAÇÃO 2: Não permitir auto-ataque ou atacar a mesma cor
            if (strcmp(atq->cor, dfs->cor) == 0) {
                printf("\n[AVISO] Ataque proibido! Ambos os territorios pertencem ao exercito %s.\n", atq->cor);
            } else {
                // Se tudo estiver correto, a batalha acontece!
                atacar(atq, dfs);
            }
        }
    }

    // FIM DO JOGO: Libertar a memória da pilha (Heap)
    liberarMemoria(mapa);
    printf("\nObrigado por jogar! Memoria libertada com sucesso.\n");

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES (MÉTODO EDUCATIVO) ---

/**
 * Função para cadastrar todos os territórios através de ponteiros.
 */
void cadastrarTerritorios(Territorio* mapa, int total) {
    printf("\n--- FASE DE CADASTRO ---\n");
    for (int i = 0; i < total; i++) {
        printf("\nTerritorio ID %d:\n", i);
        printf("Nome do territorio: ");
        scanf("%s", mapa[i].nome); // Sem '&' porque 'nome' já é um array (ponteiro)
        
        printf("Cor do exercito dono: ");
        scanf("%s", mapa[i].cor);
        
        printf("Quantidade de tropas iniciais: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/**
 * Função que exibe os dados atuais de todos os territórios.
 */
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n================ MAPA ATUAL ================\n");
    printf("ID\t| Territorio\t\t| Cor\t\t| Tropas\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        // Usando notação de seta (->) através de ponteiro calculado por índice
        Territorio* t = &mapa[i];
        printf("%d\t| %-16s\t| %-10s\t| %d\n", i, t->nome, t->cor, t->tropas);
    }
    printf("============================================\n");
}

/**
 * Função principal do combate. Utiliza ponteiros diretos para alterar os dados originais.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // rand() % 6 gera um número de 0 a 5. Somamos 1 para ficar de 1 a 6 (como um dado real).
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- DADOS LANÇADOS ---");
    printf("\n[%s] Dado Atacante: %d", atacante->nome, dadoAtacante);
    printf("\n[%s] Dado Defensor: %d\n", defensor->nome, dadoDefensor);

    // O Atacante só ganha se o dado for estritamente MAIOR. Empate vence a defesa.
    if (dadoAtacante > dadoDefensor) {
        printf("\nVITORIA DO ATACANTE! O territorio %s foi conquistado.\n", defensor->nome);
        
        // Modificação de dados via ponteiro (operador ->)
        strcpy(defensor->cor, atacante->cor); // Defesa muda para a cor do atacante
        
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas; // Defensor recebe metade das tropas
        atacante->tropas = atacante->tropas - tropasTransferidas; // Atacante perde as que enviou
    } 
    else {
        printf("\nA DEFESA VENCEU! O ataque de %s falhou.\n", atacante->nome);
        if (atacante->tropas > 1) {
            atacante->tropas--; // Atacante perde 1 tropa pela derrota
            printf("%s perdeu 1 tropa (Restam %d).\n", atacante->nome, atacante->tropas);
        } else {
            printf("%s tem apenas 1 tropa militar, nao pode perder mais nenhuma.\n", atacante->nome);
        }
    }
}

/**
 * Função responsável por limpar a memória alocada dinamicamente.
 */
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}
