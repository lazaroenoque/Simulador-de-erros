#include <stdio.h> // Biblioteca para funções de I/O (printf, scanf)
#include <math.h>  // Biblioteca para funções matemáticas (fmax, fabs)
#include <locale.h> // Biblioteca para configurações regionais (suporte ao Português)


int main() {


setlocale(LC_ALL, "Portuguese"); // Configura a localização para Português
                                 // (permite acentuação, formatação, etc.)

//variáveis globais

    double a[3][3], b[3]; //matriz dos coefientes das variáveis

    double x[3], x_old[3]; //x[3] é vetor solução atual (k); x_old[3] é o vetor anterior anterior (k-1)

    double D,N,dR,prec; //dR é a distãncia relativa; prec é a precisão do resultado;
	                    //D e N são variáveis auxiliares usadas no cálculo da dR 

    int maxIter; //número máximo de iterações fornecidas pelo usuário

    char cont = 's'; //variável que controla o loop principal

    





//loop principal que Permite a entrada de novos dados

while(cont == 's' || cont == 'S'){



    // Entrada dos coeficientes das variáveis do sistema

    printf("Digite os coeficientes da matriz A (3x3):\n");

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {

            printf("A[%d][%d]: ", i+1, j+1); //solicita os coeficientes
            scanf("%lf", &a[i][j]); //coleta dos coefientes

        }
    }

    // Entrada dos termos idependentes do sistema

    printf("\nDigite os termos independentes (b):\n");

    for (int i = 0; i < 3; i++) {

        printf("b[%d]: ", i+1); //solicita os termos independentes
        scanf("%lf", &b[i]); //coleta dos termos idependentes

         //chute inicial padronizado pelo programdor
         //idealmente, deveria se veriaficar se a[i][i] é diferente de 0.
        x[i] = b[i]/a[i][i]; 

        

        

    }

    //solicita o número de iterações desejdas pelo usuário
    printf("\nDigite o número máximo de iterações: ");

    scanf("%d",&maxIter); //coleta o número de iterações

    //solicita o a precisão em formato percentual
    printf("\nDigite precisão em formato percentual (Ex.: 10%%): ");

    scanf("%lf",&prec); //coleta a precisão

    

    

    //Método de Gauss-Seidel
    
//caso o sistema venha a convergir, esse loop 2 garante o número de iterações
//necessárias para a converrgência.
for(int iter = 0; iter<maxIter; iter++){

    //loop que garante o vetor solução anterior (k-1) e o armazena
    //para o cálculo da dR
        for( int k = 0; k < 3;k++){
            x_old[k] = x[k]; //a solução atual é copiada para x_old[k] antes
                             //que a mesma seja atualizada
		} 

//atualização do vetor solução

x[0] = (1/a[0][0])*(b[0]-a[0][1]*x[1]-a[0][2]*x[2]); //A cooredenada x[0] de x[k] é atualizada
                                                    //por meio da fórmula de Gauss-Seidel.

x[1] = (1/a[1][1])*(b[1]-a[1][0]*x[0]-a[1][2]*x[2]);//A cooredenada x[1] de x[k] é atualizada
                                                    //por meio da fórmula de Gauss-Seidel.

x[2] = (1/a[2][2])*(b[2]-a[2][0]*x[0]-a[2][1]*x[1]); //A cooredenada x[2] de x[k] é atualizada
                                                    //por meio da fórmula de Gauss-Seidel.

           //coleta do valor máximo em módulo de (x[k] - x_old[k]) 
           
           N = fmax(fmax(fabs(x[0]-x_old[0]),  //a função 'fabs' garante que todas as coordenadas
                                               //do vetor sejam positivas, enquanto a função
                                               //'fmax' coleta o maior valor desse vetor modificado
                                               //pela função 'fabs'.

                        fabs(x[1]-x_old[1])),

                        fabs(x[2]-x_old[2]));    

               //coleta do valor máximo em módulo de x[k]
			                           
               D = fmax(fmax(fabs(x[0]),  //a função 'fabs' garante que todas as coordenadas
                                          //do vetor sejam positivas, enquanto a função
                                          //'fmax' coleta o maior valor desse vetor modificado
                                          //pela função 'fabs'.

                            fabs(x[1])),

                            fabs(x[2]));


                //Cálculo da distãncia relativa
                dR = N/D;

 

                //condição de parada em caso de convergência        
                if(dR < (prec/100)){

                printf("\nO sistema convergiu após %d iterações.\n",iter+1);

                //exibição do resultado

                printf("\nSolução aproximada:\n");

                //O programa multiplica a resposta por 1000 e a exibe. Assim,
                //a corrente é exibida em miliampéres (mA).
                
                printf("I6 = %.3lf mA\n", x[0]*1000.0);
                printf("I2 = %.3lf mA\n", x[1]*1000.0);
                printf("I3 = %.3lf mA\n", x[2]*1000.0);

iter = 1001; //quando o sistema converge, a variável iter é atualizada de modo 
            //que a condição do loop 2 não seja mais satisfeita. Logo, o
            //loop 2 é encerrado.

}       

}

//Exibe uma mensagem caso o sistema não convergir

if(dR >= (prec/100)){
printf("\nO sistema não convergiu após %d iterações.\n", maxIter);

}

//pergunta ao usuário se o mesmo não deseja resolver um novo sistema

printf("\nDeseja resolver um novo sistema? (s/S ou n/N): ");
scanf("%s", &cont); //a variável de controle do loop principal é atualizada,
                    //permitindo a resolução ou não de um novo sistema.

printf("\n");

}

return 0;

}
