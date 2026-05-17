#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_MISSOES 5
#define TAMANHO_MISSAO 100

// Estrutura para representar cada território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void cadastrarTerritorios(Territorio* mapa, int total);
void exibirTerritorios(Territorio* mapa, int total);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
void exibirMissao(char* missao);
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador);
void liberarMemoria(Territorio* mapa, char* missao);

// --- FUNÇÃO PRINCIPAL ---
int main() {
    int totalTerritorios;
    char corJogador[10];
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Lista pré-definida de missões estratégicas (Vetor de Strings)
    char* listaMissoes[TOTAL_MISSOES] = {
        "Conquistar 2 territorios para o seu imperio.",
        "Conquistar 3 territorios para o seu imperio.",
        "Dominar o mapa expandindo a sua cor.",
        "Garantir a supremacia militar com 2 territorios.",
        "Expandir as suas fronteiras por todo o mapa."
    };

    printf("=== BEM-VINDO AO DESAFIO FINAL: WAR MISSOES ===\n");
    
    // Definir qual é a cor do jogador humano para podermos testar a vitória
    printf("Escolha a COR do seu exercito (ex: Vermelho, Azul, Verde): ");
    scanf("%s", corJogador);

    printf("Quantos territorios deseja cadastrar no mapa? ");
    scanf("%d", &totalTerritorios);
    fflush(stdin); // Limpa o buffer do teclado

    // ALOCAÇÃO DINÂMICA: Vetor de territórios
    Territorio* mapa = (Territorio*) calloc(totalTerritorios, sizeof(Territorio));
    
    // ALOCAÇÃO DINÂMICA: Espaço para guardar a string da missão sorteada
    char* missaoJogador = (char*) malloc(TAMANHO_MISSAO * sizeof(char));

    // Verificação de segurança da memória
    if (mapa == NULL || missaoJogador == NULL) {
        printf("[ERRO] Falha crítica ao alocar memoria!\n");
        return 1;
    }

    // Registo dos territórios
    cadastrarTerritorios(mapa, totalTerritorios);

    // Sorteia e atribui a missão por REFERÊNCIA (passando o ponteiro)
    atribuirMissao(missaoJogador, listaMissoes, TOTAL_MISSOES);
    
    // Exibe a missão APENAS uma vez no início (Passagem por VALOR)
    exibirMissao(missaoJogador);

    int jogoAtivo = 1;
    int opcao;

    while (jogoAtivo) {
        printf("\n--- MENU DE TURNO ---\n");
        printf("1. Ver mapa de territorios\n");
        printf("2. Realizar um Ataque Estrategico\n");
        printf("0. Desistir do Jogo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirTerritorios(mapa, totalTerritorios);
        } 
        else if (opcao == 2) {
            int idAtacante, idDefensor;
            exibirTerritorios(mapa, totalTerritorios);
            
            printf("\nID do territorio ATACANTE: ");
            scanf("%d", &idAtacante);
            printf("ID do territorio DEFENSOR: ");
            scanf("%d", &idDefensor);

            // Validação de IDs válidos
            if (idAtacante < 0 || idAtacante >= totalTerritorios || idDefensor < 0 || idDefensor >= totalTerritorios) {
                printf("\n[ERRO] IDs invalidos!\n");
                continue;
            }

            Territorio* atq = &mapa[idAtacante];
            Territorio* dfs = &mapa[idDefensor];

            // Validação técnica: Não pode atacar a própria cor
            if (strcmp(atq->cor, dfs->cor) == 0) {
                printf("\n[AVISO] Ataque invalido! Nao pode atacar o seu proprio exercito (%s).\n", atq->cor);
                continue;
            }

            // Realiza a batalha
            atacar(atq, dfs);

            // VERIFICAÇÃO SILENCIOSA: O sistema checa se o objetivo foi cumprido
            if (verificarMissao(missaoJogador, mapa, totalTerritorios, corJogador)) {
                printf("\n============================================\n");
                printf("!!! PARABENS !!! VOCE CUMPRIU SUA MISSAO:\n");
                printf("\"%s\"\n", missaoJogador);
                printf("VOCE E O VENCEDOR DO WAR ESTRUTURADO!\n");
                printf("============================================\n");
                jogoAtivo = 0; // Termina o loop do jogo
            }
        } 
        else if (opcao == 0) {
            printf("\nSaindo do jogo...\n");
            jogoAtivo = 0;
        }
    }

    // Liberação total da memória para evitar vazamentos (Memory Leak)
    liberarMemoria(mapa, missaoJogador);
    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES (MÉTODO EDUCATIVO) ---

/**
 * Sorteia uma missão e copia para o ponteiro de destino (Passagem por Referência).
 */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    // strcpy copia o texto da lista para o espaço de memória alocado no main
    strcpy(destino, missoes[indiceSorteado]);
}

/**
 * Exibe a missão recebida (Passagem por Valor).
 */
void exibirMissao(char* missao) {
    printf("\n--------------------------------------------------\n");
    printf(" SUA MISSAO SECRETA: %s\n", missao);
    printf("--------------------------------------------------\n");
}

/**
 * Alimenta o mapa com os dados digitados pelo utilizador.
 */
void cadastrarTerritorios(Territorio* mapa, int total) {
    printf("\n--- CADASTRO DE TERRITORIOS ---\n");
    for (int i = 0; i < total; i++) {
        printf("Nome do territorio %d: ", i);
        scanf("%s", mapa[i].nome);
        printf("Cor do dono: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("---------------------\n");
    }
}

/**
 * Exibe o estado atual dos territórios em forma de tabela.
 */
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n================ MAPA ATUAL ================\n");
    printf("ID\t| Territorio\t\t| Cor\t\t| Tropas\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%d\t| %-16s\t| %-10s\t| %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("============================================\n");
}

/**
 * Executa a batalha simulada por dados (1 a 6).
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n[BATALHA] %s (%d) VS %s (%d)\n", atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("-> VITORIA! %s conquistou %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor); // Transfere a cor
        
        int transferir = atacante->tropas / 2;
        defensor->tropas = transferir;
        atacante->tropas -= transferir;
    } else {
        printf("-> DERROTA! A defesa de %s resistiu.\n", defensor->nome);
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    }
}

/**
 * Lógica de Verificação: Conta quantos territórios o jogador possui.
 * Se a missão pedir 2 ou 3 territórios e o jogador tiver essa quantidade, retorna 1 (Vitória).
 */
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    int territoriosConquistados = 0;

    // Percorre o mapa inteiro contando os territórios da cor do jogador
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            territoriosConquistados++;
        }
    }

    // Se a missão sorteada mencionar "2" e ele tiver 2 ou mais territórios -> Ganhou!
    if (strstr(missao, "2") != NULL && territoriosConquistados >= 2) {
        return 1;
    }
    // Se a missão sorteada mencionar "3" e ele tiver 3 ou mais territórios -> Ganhou!
    if (strstr(missao, "3") != NULL && territoriosConquistados >= 3) {
        return 1;
    }
    // Condição genérica para as outras missões: se conquistar todos ou pelo menos 3
    if (territoriosConquistados >= 3 || territoriosConquistados == tamanho) {
        return 1;
    }

    return 0; // Ainda não cumpriu a missão
}

/**
 * Liberta toda a memória dinâmica que foi requisitada ao sistema operacional.
 */
void liberarMemoria(Territorio* mapa, char* missao) {
    if (mapa != NULL) {
        free(mapa);
    }
    if (missao != NULL) {
        free(missao);
    }
    printf("\n[Sistema] Memoria limpa. Nenhum vazamento detectado!\n");
}
