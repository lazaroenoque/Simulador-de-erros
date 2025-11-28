#include <stdio.h>

// O cabeçalho <stdio.h> é incluído para operações básicas de I/O (Input/Output), 
// como 'printf' (imprimir no console) e 'scanf' (ler do console).

// --- Função de Interpolação de Lagrange ---
// Recebe:
// x[]: Array dos pontos independentes (xi)
// y_orig[]: Array dos valores da função (yi) correspondentes a x
// n: Número total de pontos
// xp: O ponto onde queremos estimar o valor da função P(xp)
double lagrange(double x[], double y_orig[], int n, double xp) {
    double resultado = 0.0; // P(xp), o valor interpolado.

    // Loop externo (variável i): Itera sobre cada ponto tabelado (xi, yi)
    // para construir e somar os termos do polinômio.
    for (int i = 0; i < n; i++) {
        double L = 1.0; // Inicializa o Polinômio de Lagrange Li(xp)

        // Loop interno (variável j): Calcula o polinômio Li(xp) para o ponto xi.
        // A fórmula de Lagrange requer o produto de termos: ? (xp - xj) / (xi - xj).
        for (int j = 0; j < n; j++) {
            // Condição: i != j garante que o termo (xi - xj) do denominador não seja (xi - xi) = 0.
            if (i != j) {
                // Li(xp) = Li(xp) * [(xp - xj) / (xi - xj)]
                L *= (xp - x[j]) / (x[i] - x[j]);
            }
        }
        
        // O termo do polinômio é yi * Li(xp).
        // P(xp) = ? [yi * Li(xp)]
        resultado += y_orig[i] * L;
    }

    return resultado; // Retorna o valor interpolado P(xp)
}

// ---------------------------------------------------------------------------------

// --- Função para Construir a Tabela de Diferenças Divididas (Preparação para Newton) ---
// Recebe:
// x[]: Array dos pontos independentes (xi)
// y[][10]: Matriz onde a primeira coluna (y[i][0]) contém os valores yi,
//          e as colunas subsequentes armazenarão as diferenças divididas.
// n: Número total de pontos
void diferencas_divididas(double x[], double y[][10], int n) {
    // Loop externo (variável j): Itera sobre as colunas da tabela, começando da segunda (j=1),
    // que representa as diferenças de primeira ordem, depois segunda ordem, e assim por diante.
    for (int j = 1; j < n; j++) {
        // Loop interno (variável i): Itera sobre as linhas, calculando a diferença
        // y[i][j] usando a diferença anterior (j-1) nas linhas i e i+1.
        for (int i = 0; i < n - j; i++) {
            // Fórmula da Diferença Dividida de ordem j:
            // f[xi, ..., xi+j] = ( f[xi+1, ..., xi+j] - f[xi, ..., xi+j-1] ) / ( xi+j - xi )
            y[i][j] = (y[i+1][j-1] - y[i][j-1]) / (x[i + j] - x[i]);
        }
    }
}

// ---------------------------------------------------------------------------------

// --- Função de Interpolação de Newton ---
// Usa os coeficientes (diferenças divididas) calculados na função anterior.
double newton(double x[], double y[][10], int n, double xp) {
    // O primeiro termo do polinômio de Newton é o primeiro coeficiente: f[x0] = y[0][0]
    double resultado = y[0][0];
    double termo = 1.0; // Variável para acumular o produto (xp - x0)(xp - x1)...

    // Loop (variável i): Começa do segundo termo (i=1) até o último.
    for (int i = 1; i < n; i++) {
        // 1. Calcula o próximo fator do produto: termo = (xp - x0)(xp - x1)...(xp - x(i-1))
        termo *= (xp - x[i-1]);
        
        // 2. Soma o termo do polinômio: coeficiente * (produto de fatores)
        // O coeficiente é a diferença dividida principal: f[x0, x1, ..., xi], que está em y[0][i].
        resultado += y[0][i] * termo;
    }

    return resultado; // Retorna o valor interpolado P(xp)
}

// ---------------------------------------------------------------------------------

// --- Função Principal ---
int main() {
    int n;
    double xp;
    int continuar; 

    printf("### Interpolação Polinomial (Lagrange & Newton) ###\n\n");

    // Coleta o número de pontos.
    printf("Digite o numero de pontos (max 10): ");
    if (scanf("%d", &n) != 1 || n < 2 || n > 10) {
        printf("Erro: O número de pontos deve ser entre 2 e 10.\n");
        return 1; // Encerra o programa em caso de erro.
    }

    // Declaração dos arrays (tamanho estático 10, conforme o limite)
    double x[10];
    double y_orig[10];      // Valores y originais (usado por Lagrange)
    double y_diff[10][10];  // Tabela para diferenças divididas (usado por Newton)

    // Coleta dos valores de x e y.
    printf("\n--- Entrada dos Pontos Tabelados ---\n");
    printf("Digite os valores de x:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d]: ", i);
        scanf("%lf", &x[i]);
    }

    printf("Digite os valores de y:\n");
    for (int i = 0; i < n; i++) {
        printf("y[%d]: ", i);
        scanf("%lf", &y_orig[i]);
        // Copia os valores y originais para a primeira coluna da tabela de diferenças.
        y_diff[i][0] = y_orig[i];
    }

    // Pré-cálculo de Newton: A tabela é construída APENAS UMA VEZ.
    diferencas_divididas(x, y_diff, n);

    // Loop principal (do-while): Permite ao usuário interpolar vários valores de xp 
    // usando o MESMO conjunto de dados tabelados.
    do {
        printf("\n--- Interpolação ---\n");
        printf("Digite o ponto de interpolacao xp: ");
        
        if (scanf("%lf", &xp) != 1) {
            printf("Entrada inválida. Encerrando o programa.\n");
            break;
        }

        // Chamada das funções e obtenção dos resultados
        double resultado_lagrange = lagrange(x, y_orig, n, xp);
        double resultado_newton = newton(x, y_diff, n, xp);

        // Exibição dos resultados (que devem ser idênticos, confirmando o Teorema da Unicidade)
        printf("\n===== RESULTADOS para xp = %.4lf =====\n", xp);
        printf("Interpolacao por Lagrange: %.10lf\n", resultado_lagrange);
        printf("Interpolacao por Newton:   %.10lf\n", resultado_newton);

        // Pergunta se deseja continuar o loop
        printf("\nDeseja interpolar um novo ponto? (1 para Sim / 0 para Não): ");
        if (scanf("%d", &continuar) != 1) {
             continuar = 0;
        }

    } while (continuar == 1); // A repetição ocorre enquanto o usuário digitar '1'.

    printf("\nPrograma encerrado. Obrigado!\n");

    return 0; // Saída bem-sucedida do programa.
}
