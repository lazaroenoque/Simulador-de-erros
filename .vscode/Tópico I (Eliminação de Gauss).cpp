#include <stdio.h> // Biblioteca para funções de I/O (printf, scanf)
#include <math.h>  // Biblioteca para funções matemáticas, especialmente fabs() para valor absoluto
#include <ctype.h> // Biblioteca para funções de manipulação de caracteres, como toupper()

#define N 3 // Define uma constante para o tamanho do sistema (3x3)

// Função para exibir a matriz do sistema
// Recebe a matriz aumentada A[N][N+1] e exibe seu conteúdo na tela.
void imprimir_matriz(float A[N][N + 1]) {
    int i, j;
    printf("\n");
    for (i = 0; i < N; i++) { // Itera pelas linhas (i)
        for (j = 0; j < N + 1; j++) { // Itera pelas colunas (j), incluindo o vetor 'b'
            printf("%.4f", A[i][j]);
            if (j == N - 1) {
                printf("\t|"); // Linha separadora entre coeficientes e termos independentes
            } else {
                printf("\t"); // Tabulação para formatação
            }
        }
        printf("\n"); //quebra de linha
    }
}

//função principal
int main() {
    char continuar;

    printf("--- Solucao de Sistemas Lineares 3x3 por Eliminacao de Gauss ---\n");
   // Loop principal: Permite resolver múltiplos sistemas sem reiniciar o programa. 
    do {
        float A[N][N + 1]; // Matriz aumentada [A|b]
        float x[N];        // Vetor solucao [x, y, z]
        int i, j, k;       // Contadores para loops (linhas, colunas, pivôs)
        float multiplicador; // Fator de eliminação (m_ik = A[i][k] / pivo)
        float pivo;        // Valor do elemento A[k][k] usado para zerar os elementos abaixo

        printf("\n======================================================\n");
        printf("ENTRADA DO NOVO SISTEMA (3 Equacoes)\n");
        printf("Formato: a1*x + b1*y + c1*z = d1\n");
        printf("======================================================\n");
        
        // --- 1. PREENCHIMENTO DA MATRIZ ---
        for (i = 0; i < N; i++) {
            printf("Equacao %d (Digite 4 valores: a, b, c, d):\n", i + 1);
            for (j = 0; j < N + 1; j++) {
                printf("  A[%d][%d]: ", i + 1, j + 1);
                if (scanf("%f", &A[i][j]) != 1) { // Leitura do coeficiente A[i][j]
                    printf("Erro de leitura. Encerrando.\n");
                    return 1;
                }
            }
        }

        printf("\n--- Matriz Original ---\n");
        imprimir_matriz(A);

        // --- 2. ELIMINACAO DE GAUSS (ESCALONAMENTO) ---
        for (k = 0; k < N; k++) { // k: linha pivo
            pivo = A[k][k];

            // Verificacao de pivo (pivoteamento parcial simples para estabilidade)
            if (fabs(pivo) < 1e-9) { 
                printf("\nERRO: Pivo A[%d][%d] muito proximo de zero. Tentando troca de linha...\n", k + 1, k + 1);
                
                // Tenta encontrar a melhor linha para troca abaixo
                int max_i = k;
                for (i = k + 1; i < N; i++) {
                    if (fabs(A[i][k]) > fabs(A[max_i][k])) {
                        max_i = i;
                    }
                }
                
                if (max_i != k) {
                    // Troca a linha k pela linha max_i
                    for (j = k; j < N + 1; j++) {
                        float temp = A[k][j];
                        A[k][j] = A[max_i][j];
                        A[max_i][j] = temp;
                    }
                    pivo = A[k][k]; // Recalcula o pivo
                } else {
                    printf("ERRO: O sistema e singular (determinante proximo de zero). Nao ha solucao unica.\n");
                    goto proximo_sistema; // Pula para a pergunta de continuar
                }
            }

            // Zera os elementos abaixo do pivo na coluna k
            for (i = k + 1; i < N; i++) { // i: linhas a serem modificadas
                multiplicador = A[i][k] / pivo;

                // Operacao: L_i = L_i - multiplicador * L_k
                for (j = k; j < N + 1; j++) {
                    A[i][j] = A[i][j] - multiplicador * A[k][j];
                }
            }
        }

        printf("\n--- Matriz Escalonada ---\n");
        imprimir_matriz(A);

        // --- 3. RETROSUBSTITUICAO ---
        
        // Verifica o último pivo para consistencia
        if (fabs(A[N - 1][N - 1]) < 1e-9) {
            printf("\nERRO: Matriz singular. Infinitas solucoes ou nenhuma solucao.\n");
            goto proximo_sistema;
        }
        
        // O ultimo elemento da solucao (z)
        x[N - 1] = A[N - 1][N] / A[N - 1][N - 1]; 

        // Loop para encontrar os valores restantes (y e x)
        for (i = N - 2; i >= 0; i--) {
            float soma = 0;
            for (j = i + 1; j < N; j++) {
                soma += A[i][j] * x[j];
            }
            x[i] = (A[i][N] - soma) / A[i][i];
        }

        // --- 4. EXIBICAO DA SOLUCAO ---
        printf("\n--- Solucao do Sistema ---\n");
        printf("x = %.4f\n", x[0]);
        printf("y = %.4f\n", x[1]);
        printf("z = %.4f\n", x[2]);

        proximo_sistema: ; // Label para o goto em caso de erro

        // --- 5. PERGUNTA DE CONTINUACAO ---
        // ' %c' consome qualquer caractere de nova linha pendente
        printf("\n\nDeseja resolver outro sistema? (s/n): ");
        scanf(" %c", &continuar); 
        
    } while (toupper(continuar) == 'S'); // O loop continua se for 's' ou 'S'

    printf("\nPrograma encerrado.\n");
    return 0; // Saída bem-sucedida
}



