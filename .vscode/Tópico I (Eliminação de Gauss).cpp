#include <stdio.h> // Biblioteca para funções de I/O (printf, scanf)
#include <math.h>  // Biblioteca para funções matemáticas, especialmente fabs() para valor absoluto
#include <ctype.h> // Biblioteca para funções de manipulação de caracteres, como toupper()

#define N 3 // Define uma constante para o tamanho do sistema. N=3 indica um sistema 3x3.

// --- Função Auxiliar: Imprimir Matriz ---
// Recebe a matriz aumentada A[N][N+1] e exibe seu conteúdo na tela.
void imprimir_matriz(float A[N][N + 1]) {
    int i, j;
    printf("\n");
    for (i = 0; i < N; i++) { // Itera pelas linhas (i)
        for (j = 0; j < N + 1; j++) { // Itera pelas colunas (j), incluindo o vetor 'b'
            printf("%.4f", A[i][j]); // Exibe o valor com 4 casas decimais
            if (j == N - 1) {
                printf("\t|"); // Insere uma linha vertical após os coeficientes (coluna N-1)
            } else {
                printf("\t"); // Tabulação para formatação
            }
        }
        printf("\n"); // Nova linha após cada linha da matriz
    }
}

// --- Função Principal ---
int main() {
    char continuar;

    printf("--- Solucao de Sistemas Lineares 3x3 por Eliminacao de Gauss ---\n");
    
    // Loop principal: Permite resolver múltiplos sistemas sem reiniciar o programa.
    do {
        // Variáveis locais re-declaradas para cada novo sistema
        float A[N][N + 1]; // Matriz aumentada [A|b]. N colunas para 'A' + 1 coluna para 'b'.
        float x[N];        // Vetor solucao [x0, x1, x2] (representando x, y, z)
        int i, j, k; // Contadores para loops (linhas, colunas, pivôs)
        float multiplicador; // Fator de eliminação (m_ik = A[i][k] / pivo)
        float pivo; // Valor do elemento A[k][k] usado para zerar os elementos abaixo

        printf("\n======================================================\n");
        printf("ENTRADA DO NOVO SISTEMA (3 Equacoes)\n");
        printf("Formato: a1*x + b1*y + c1*z = d1\n");
        printf("======================================================\n");
        
        // --- 1. PREENCHIMENTO DA MATRIZ AUMENTADA [A|b] ---
        for (i = 0; i < N; i++) { // Itera pelas linhas (equações)
            printf("Equacao %d (Digite 4 valores: a, b, c, d):\n", i + 1);
            for (j = 0; j < N + 1; j++) { // Itera pelas colunas (coeficientes a_ij e termo b_i)
                printf("  A[%d][%d]: ", i + 1, j + 1);
                if (scanf("%f", &A[i][j]) != 1) { // Leitura do coeficiente A[i][j]
                    printf("Erro de leitura. Encerrando.\n");
                    return 1; // Saída de erro
                }
            }
        }

        printf("\n--- Matriz Original ---\n");
        imprimir_matriz(A);

        // --- 2. ELIMINACAO DE GAUSS (TRANSFORMAÇÃO PARA FORMA ESCALONADA) ---
        // O objetivo é criar zeros abaixo da diagonal principal.
        for (k = 0; k < N; k++) { // k: Índice da coluna atual (pivô A[k][k])
            pivo = A[k][k];

            // 2.1. Verificação e Pivoteamento Parcial
            // Verifica se o pivô é muito próximo de zero (problemas de divisão ou estabilidade)
            if (fabs(pivo) < 1e-9) {  // 1e-9 é uma tolerância numérica (e)
                printf("\nERRO: Pivo A[%d][%d] muito proximo de zero. Tentando troca de linha...\n", k + 1, k + 1);
                
                // Encontra a linha (max_i) abaixo da linha k que tem o maior valor absoluto
                int max_i = k;
                for (i = k + 1; i < N; i++) { // Procura apenas nas linhas abaixo de k
                    // Compara o valor absoluto do elemento A[i][k] com o maior módulo encontrado (A[max_i][k])
                    if (fabs(A[i][k]) > fabs(A[max_i][k])) {
                        max_i = i;
                    }
                }
                
                if (max_i != k) {
                    // Se encontrou um pivô melhor (max_i != k), realiza a troca de linhas (k e max_i)
                    for (j = k; j < N + 1; j++) { // Troca todos os elementos da linha, da coluna k em diante
                        float temp = A[k][j];
                        A[k][j] = A[max_i][j];
                        A[max_i][j] = temp;
                    }
                    pivo = A[k][k]; // O pivô é atualizado para o novo valor
                } else {
                    // Se não encontrou um pivô melhor, o sistema é singular ou mal-condicionado
                    printf("ERRO: O sistema e singular (determinante proximo de zero). Nao ha solucao unica.\n");
                    goto proximo_sistema; // Pula a resolução e vai para a pergunta de continuação
                }
            }

            // 2.2. Eliminação (Zerar elementos abaixo do pivô)
            for (i = k + 1; i < N; i++) { // i: Linhas alvo (abaixo do pivô)
                // Cálculo do fator de eliminação: multiplicador = A[i][k] / A[k][k] (pivô)
                multiplicador = A[i][k] / pivo;

                // Operação L_i = L_i - multiplicador * L_k
                for (j = k; j < N + 1; j++) { // j: Colunas da matriz
                    // Aplica a operação em toda a linha i, da coluna k até o termo independente
                    A[i][j] = A[i][j] - multiplicador * A[k][j];
                }
            }
        }

        printf("\n--- Matriz Escalonada ---\n");
        imprimir_matriz(A); // Exibe o resultado do escalonamento (matriz triangular superior)

        // --- 3. RETROSUBSTITUIÇÃO (Cálculo das variáveis) ---
        
        // 3.1. Verificação final de consistência
        // Se o último pivô (A[N-1][N-1]) é zero, o sistema pode não ter solução única
        if (fabs(A[N - 1][N - 1]) < 1e-9) {
            printf("\nERRO: Matriz singular. Infinitas solucoes ou nenhuma solucao.\n");
            goto proximo_sistema;
        }
        
        // 3.2. Cálculo da última variável (x[N-1], ou 'z')
        // Da última linha: A[N-1][N-1]*x[N-1] = A[N-1][N] => x[N-1] = A[N-1][N] / A[N-1][N-1]
        x[N - 1] = A[N - 1][N] / A[N - 1][N - 1]; 

        // 3.3. Loop de Retrossubstituição
        // Começa da penúltima linha (i = N-2) e vai até a primeira (i = 0)
        for (i = N - 2; i >= 0; i--) {
            float soma = 0; // Acumulador para os termos A[i][j] * x[j] já conhecidos
            
            // Soma os termos conhecidos (à direita da variável x[i])
            for (j = i + 1; j < N; j++) {
                soma += A[i][j] * x[j];
            }
            
            // Calcula x[i] a partir da fórmula: 
            // x[i] = (A[i][N] - Soma_dos_termos_conhecidos) / A[i][i]
            x[i] = (A[i][N] - soma) / A[i][i];
        }

        // --- 4. EXIBIÇÃO DA SOLUÇÃO ---
        printf("\n--- Solucao do Sistema ---\n");
        printf("x = %.4f\n", x[0]); // Primeira variável
        printf("y = %.4f\n", x[1]); // Segunda variável
        printf("z = %.4f\n", x[2]); // Terceira variável

        proximo_sistema: ; // O rótulo 'goto' que o programa salta em caso de erro
                           // (evita que o código tente a Retrossubstituição em sistemas singulares).

        // --- 5. PERGUNTA DE CONTINUACAO ---
        printf("\n\nDeseja resolver outro sistema? (s/n): ");
        // O espaço antes de '%c' no scanf é crucial para limpar o buffer de entrada.
        scanf(" %c", &continuar); 
        
    } while (toupper(continuar) == 'S'); // Continua o loop se 's' ou 'S' for digitado

    printf("\nPrograma encerrado.\n");
    return 0; // Saída bem-sucedida
}
    

  



