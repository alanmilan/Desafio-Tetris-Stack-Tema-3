#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definições constantes
#define MAX_FILA 10 // Tamanho máximo da fila (buffer circular)

// 1. Definição da Struct Peca
typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L', etc.
    int id;     // Identificador único da peça
} Peca;

// Variáveis Globais para controle da Fila Circular
Peca fila[MAX_FILA];
int inicio = 0;    // Índice do início da fila (head)
int fim = 0;       // Índice do final da fila (tail)
int tamanho = 0;   // Quantidade atual de peças na fila

// Protótipos das funções
void inicializarFila();
Peca gerarPeca();
void enfileirar(int automatico); // enqueue
void desenfileirar();            // dequeue
void exibirFila();
void limparBuffer();

int main() {
    int opcao;
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Inicializa a fila com 5 peças (Requisito Funcional)
    inicializarFila();

    do {
        printf("\n=== TETRIS STACK: PROXIMAS PECAS ===\n");
        exibirFila();
        
        printf("\nOpcoes de acao:\n");
        printf("1. Jogar peca (Dequeue - Usar a primeira)\n");
        printf("2. Inserir nova peca (Enqueue - Gerar nova)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                desenfileirar();
                break;
            case 2:
                // O parâmetro 0 indica que é uma inserção manual do usuário
                // (embora a peça seja gerada automaticamente)
                enfileirar(0); 
                break;
            case 0:
                printf("Encerrando simulacao...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// Função auxiliar para limpar buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Gera uma peça com ID sequencial e Tipo aleatório
Peca gerarPeca() {
    static int contadorId = 0; // static mantém o valor entre as chamadas da função
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'Z', 'S'};
    Peca p;
    
    p.id = contadorId++;
    // Escolhe aleatoriamente um dos tipos de peça
    p.nome = tipos[rand() % 7]; 
    
    return p;
}

// Inicializa a fila preenchendo 5 espaços iniciais
void inicializarFila() {
    printf("Sistema: Gerando pecas iniciais...\n");
    for (int i = 0; i < 5; i++) {
        enfileirar(1); // 1 indica modo silencioso (inicialização)
    }
}

// Adiciona uma peça ao final da fila (Enqueue)
void enfileirar(int modoSilencioso) {
    if (tamanho >= MAX_FILA) {
        printf("\n[!] A fila esta cheia! Jogue uma peca antes de pedir mais.\n");
        return;
    }

    Peca nova = gerarPeca();

    // Lógica da Fila Circular: insere na posição 'fim'
    fila[fim] = nova;
    
    // Atualiza o índice 'fim' (volta para 0 se chegar no MAX)
    fim = (fim + 1) % MAX_FILA;
    tamanho++;

    if (!modoSilencioso) {
        printf("\n[+] Nova peca [%c %d] entrou na fila.\n", nova.nome, nova.id);
    }
}

// Remove a peça do início da fila (Dequeue)
void desenfileirar() {
    if (tamanho == 0) {
        printf("\n[!] A fila esta vazia! Nao ha pecas para jogar.\n");
        return;
    }

    Peca jogada = fila[inicio];

    // Lógica da Fila Circular: avança o 'início'
    inicio = (inicio + 1) % MAX_FILA;
    tamanho--;

    printf("\n[>>>] Voce jogou a peca: [%c %d]\n", jogada.nome, jogada.id);
}

// Exibe a fila na ordem correta (do início ao fim lógico)
void exibirFila() {
    if (tamanho == 0) {
        printf("Fila de pecas: [ VAZIA ]\n");
        return;
    }

    printf("Fila de pecas: ");
    
    // Percorre do 'inicio' até a quantidade de elementos
    // Usamos uma variável auxiliar 'idx' para calcular a posição circular real
    int count = 0;
    int i = inicio;
    
    while (count < tamanho) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        
        i = (i + 1) % MAX_FILA; // Avanço circular
        count++;
    }
    printf("\n");
}