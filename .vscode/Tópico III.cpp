#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
	
	setlocale(LC_ALL, "Portuguese"); 
	//variáveis globais
	
    double a[3][3], b[3]; //matriz dos coefientes das variáveis
    double x[3], x_old[3]; //x[3] é vetor solução atual (k); x_old[3] é o vetor anterior anterior (k-1)
    double D,N,dR,prec; //dR é a distãncia relativa; prec é a precisão do resultado 
    int maxIter; //número máximo de iterações
    char cont = 's';
    


//Permite a entrada de novos dados
while(cont == 's' || cont == 'S'){

    // Entrada dos coeficientes das variáveis do sistema
    printf("Digite os coeficientes da matriz A (3x3):\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("A[%d][%d]: ", i+1, j+1);
            scanf("%lf", &a[i][j]); //coleta dos coefientes
        }
    }

    // Entrada dos termos idependentes do sistema
    printf("\nDigite os termos independentes (b):\n");
    for (int i = 0; i < 3; i++) {
        printf("b[%d]: ", i+1);
        scanf("%lf", &b[i]); //coleta dos termos idependentes
        
        x[i] = b[i]/a[i][i]; //chute inicial padronizado pelo programdor
        
        
    }
    
    //solicita o número de iterações desejdas pelo usuário
    printf("\nDigite o numero maximo de iteracoes: ");
    scanf("%d",&maxIter); //coleta o número de iterações
    
    //solicita o a precisão em formato percentual
    printf("\nDidite precisão em formato percentual (Ex.: 10%%): ");
    scanf("%lf",&prec); //coleta a precisão
    
    
    //Método de Gauss-Seidel
	for(int iter = 0; iter<maxIter; iter++){
		
		
	    //garante a existência do vetor solução anterior (k-1) para a comparação no cálculo da dR
		for( int k = 0; k < 3;k++){
			x_old[k] = x[k];
		}
		
		//atualização do vetor solução
		
		x[0] = (1/a[0][0])*(b[0]-a[0][1]*x[1]-a[0][2]*x[2]);
		
		x[1] = (1/a[1][1])*(b[1]-a[1][0]*x[0]-a[1][2]*x[2]);
		
		x[2] = (1/a[2][2])*(b[2]-a[0][2]*x[0]-a[2][1]*x[1]);
		
		 //coleta do valor máximo em módulo de (x[3] - x_old[3]) 
	           N = fmax(fmax(fabs(x[0]-x_old[0]),  
                                fabs(x[1]-x_old[1])),
                                fabs(x[2]-x_old[2]));
                                
         //coleta do valor máximo em módulo de x[3]                        
               D = fmax(fmax(fabs(x[0]),
                            fabs(x[1])),
                            fabs(x[2]));
		
		 //Cálculo da distãncia relativa						
			 dR = N/D;
			 
		 //condição de parada em caso de convergência	       
		if(dR < (prec/100)){
			printf("\nO sistema convergiu apos %d iteracoes.\n",iter);
			//exibição do resultado
			printf("\nSolução aproximada:\n");
            printf("I6 = %.3lf mA\n", x[0]*1000.0);
            printf("I2 = %.3lf mA\n", x[1]*1000.0);
            printf("I3 = %.3lf mA\n", x[2]*1000.0);
			iter = 101;
		}				      
		

		
	}
	//Exibe uma mensagem caso o sistema não convergir
	if(dR >= (prec/100)){
		printf("\nO sistema nao convergiu após %d iteracoes.\n", maxIter);
	}

//pergunta ao usuário se o mesmo não deseja resolver um novo sistema
printf("\nDeseja resolver um novo sistema? (s/S ou n/N): ");
scanf("%s", &cont);
printf("\n");
}
return 0;
}


    

  


