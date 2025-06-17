#include <stdio.h>
#include <stdbool.h>

// Definições de constantes
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define CODIGO_NAVIO 3
#define CODIGO_HABILIDADE 5  

//FUNÇÕES AUXILIARES //


void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    printf("\n===== TABULEIRO =====\n   ");
    for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        printf("%2d ", i);
        for(int j = 0; j < TAMANHO_TABULEIRO; j++){
            if(tabuleiro[j][i] == 0){
                printf("~ ");  
            } else if(tabuleiro[j][i] == CODIGO_NAVIO){
                printf("N ");  
            } else if(tabuleiro[j][i] == CODIGO_HABILIDADE){
                printf("* ");  
            } else {
                printf("? ");
            }
        }
        printf("\n");
    }
}

// Verifica se uma posição existe no tabuleiro
bool posicaoExiste(int x, int y){
    return x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO;
}

// POSICIONAMENTO DE NAVIOS //

// Verifica se navio horizontal/vertical cabe na posição
bool verificarPosicaoValidaNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, int orientacao){
    for(int i = 0; i < TAMANHO_NAVIO; i++){
        if(orientacao == 0){ 
            if(!posicaoExiste(x + i, y) || tabuleiro[x + i][y] != 0) return false;
        } else { 
            if(!posicaoExiste(x, y + i) || tabuleiro[x][y + i] != 0) return false;
        }
    }
    return true;
}

// Coloca navio horizontal/vertical
void adicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, int orientacao){
    for(int i = 0; i < TAMANHO_NAVIO; i++){
        if(orientacao == 0){
            tabuleiro[x + i][y] = CODIGO_NAVIO;
        } else {
            tabuleiro[x][y + i] = CODIGO_NAVIO;
        }
    }
}

// Verifica navio na diagonal
bool verificarPosicaoValidaNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, int orientacao){
    for(int i = 0; i < TAMANHO_NAVIO; i++){
        if(orientacao == 0){ // Diagonal baixo-direita
            if(!posicaoExiste(x + i, y + i) || tabuleiro[x + i][y + i] != 0) return false;
        } else { // Diagonal cima-esquerda
            if(!posicaoExiste(x - i, y - i) || tabuleiro[x - i][y - i] != 0) return false;
        }
    }
    return true;
}

// Coloca navio na diagonal
void adicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, int orientacao){
    for(int i = 0; i < TAMANHO_NAVIO; i++){
        if(orientacao == 0){
            tabuleiro[x + i][y + i] = CODIGO_NAVIO;
        } else {
            tabuleiro[x - i][y - i] = CODIGO_NAVIO;
        }
    }
}


//APLICANDO HABILIDADES//


void ativarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[5][3], int x, int y){
    int inicioX = x - 2;
    int inicioY = y - 1;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 5; j++){
            if(habilidade[j][i] == 1){
                int posX = inicioX + j;
                int posY = inicioY + i;
                if(posicaoExiste(posX, posY)){
                    tabuleiro[posX][posY] = CODIGO_HABILIDADE;
                }
            }
        }
    }
}

//FUNÇÃO PRINCIPAL//


int main(){

    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Matrizes das habilidades
    int habCone[5][3] = {
        {0,0,1},
        {0,1,1},
        {1,1,1},
        {0,1,1},
        {0,0,1}
    };

    int habCruz[5][3] = {
        {0,1,0},
        {0,1,0},
        {1,1,1},
        {0,1,0},
        {0,1,0}
    };

    int habOctaedro[5][3] = {
        {0,0,0},
        {0,1,0},
        {1,1,1},
        {0,1,0},
        {0,0,0}
    };

    //POSICIONAMENTO DE NAVIOS //
    

    printf("\n--- POSICIONANDO NAVIOS ---\n");

    for(int i = 0; i < 4; i++){
        int x, y, orientacao, tipo;

        printf("\nNavio %d\n", i+1);
        printf("Escolha tipo:\n1 - Horizontal/Vertical\n2 - Diagonal\n> ");
        scanf("%d", &tipo);

        printf("Digite a posição X e Y (0 a 9): ");
        scanf("%d %d", &x, &y);

        if(tipo == 1){
            printf("Orientação (0 - Horizontal, 1 - Vertical): ");
            scanf("%d", &orientacao);

            if(verificarPosicaoValidaNavio(tabuleiro, x, y, orientacao)){
                adicionarNavio(tabuleiro, x, y, orientacao);
            } else {
                printf("Posição inválida!\n");
                i--; 
            }

        } else if(tipo == 2){
            printf("Orientação (0 - Diagonal baixo-direita, 1 - Diagonal cima-esquerda): ");
            scanf("%d", &orientacao);

            if(verificarPosicaoValidaNavioDiagonal(tabuleiro, x, y, orientacao)){
                adicionarNavioDiagonal(tabuleiro, x, y, orientacao);
            } else {
                printf("Posição inválida!\n");
                i--; 
            }

        } else {
            printf("Tipo inválido!\n");
            i--; // repete
        }
    }

    exibirTabuleiro(tabuleiro);

    //APLICANDO HABILIDADES//
    

    printf("\n--- ATIVANDO HABILIDADES ---\n");

    for(int i = 0; i < 3; i++){
        int x, y, tipo;

        printf("\nHabilidade %d\n", i+1);
        printf("Escolha o tipo:\n1 - Cone\n2 - Cruz\n3 - Octaedro\n> ");
        scanf("%d", &tipo);

        printf("Digite a posição central X e Y (0 a 9): ");
        scanf("%d %d", &x, &y);

        if(tipo == 1){
            ativarHabilidade(tabuleiro, habCone, x, y);
        } else if(tipo == 2){
            ativarHabilidade(tabuleiro, habCruz, x, y);
        } else if(tipo == 3){
            ativarHabilidade(tabuleiro, habOctaedro, x, y);
        } else {
            printf("Tipo inválido!\n");
            i--; // repete
        }
    }

    // EXIBIR TABULEIRO FINAL//
    
    exibirTabuleiro(tabuleiro);

    printf("\nLegenda: ~ = Água | N = Navio | * = Área da habilidade\n");
    printf("\nFim do programa.\n");

    return 0;
}