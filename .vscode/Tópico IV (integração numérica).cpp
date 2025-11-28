#include <stdio.h> // Biblioteca para funções de I/O (printf, scanf)
#include <locale.h> // Biblioteca para configurações regionais (suporte ao Português)

int main(void) {
	
	setlocale(LC_ALL, "Portuguese");        // Configura a localização para Português
                                            // (permite acentuação, formatação, etc.)
	
	char cont = 's';                              //variável que controla o loop principal
	
	while(cont == 's' || cont == 'S'){      //loop principal que Permite a entrada de novos dados
		
	float Ai = 0.0,Atrap,h,Asim, As = 0.0, Asi, Asf;   //declaração de variáveis, sendo: Ai a variável
	                                                   //que auxiliará no cálculo pelo método dos trapézios.
	                                                   // As é a variável que auxiliará no cálculo pelo
	                                                   //método de Simpson. 'h' é a largura dos
	                                                   //subintervalos.
	
	int k;                                  //variável que controla o número de subintervalos fornecidos pelo usuário.
	
	printf("Digite o número de subintervalos: ");   //solicita o número de subintervalos ao usuário.
	
	scanf("%d",&k);                         //armazena o número de subintervalos.
	
	float P[k+1];                           //declaração do vetor que armazena a altura de cada ponto.
	
	printf("\ndigite o tamanho de cada subintervalo: ");   //solicita o tamanho de cada subintervalo ao usuário.
	
	scanf("%f",&h);                                        //armazena o tamanho de cada subintervalo na variável h.
	
	printf("\n");                            //quebra de linha.
	
	for(int i = 0;i <=k;i++){                //prenchimento vetor P[k+1] pelo usuário.
	
		printf("Digite a altura %d (Y%d): ",i,i);
		scanf("%f",&P[i]);                   //armazena uma altura para cada ponto do vetor P[k+1].
	
    }
    
    Asi = P[0];                              //armazena a altura do primeiro ponto fornecido pelo usuário.
    
    Asf = P[k];                              //armazena a altura do último ponto fornecido pelo usuário.
    
    for(int i = 1;i<k;i++){                  //início do cálculo da área pelo método dos trapézios.
    
		Ai = Ai + P[i];	                     //soma as alturas do vetor P[k+1], exceto P[0] e P[k].
    }
    
    Atrap = (2*Ai + Asf + Asi)*(h/2);           //multiplica por 2 a soma das alturas, exceto p[0] e p[k],
                                                //soma P[0] e P[k] e multiplica pela largura
                                                //dos subintervalos (h) dividido por 2.
                                                
    if(k%2 != 0){                               //verifica se o número de subintervalos (k) é ímpar.
    
    printf("\nO número de subintervalos e ímpar\n");    //sendo k um número impar, imprime mensagens de feedback ao usuário.
    printf("Não é possivel calcular pelo método de Simpson 1/3\n");
    printf("\nCálculo usando o método dos trapézios:\n");
    
	printf("A = %.4f\n",Atrap);                       //finalizando, exibe a área calculada pelo método dos trapézios.
	
    }else{                                   //sendo k um número par, o código segue outro fluxo.
    	
    	printf("\nO número de subintervalos é par.\n");    //exibe um feedback ao usuário. 
    
    	for(int i = 1;i<k;i++){              //início do cálculo da área pelo método de Simpson 1/3.
		if(i%2 == 0){                        //condição para somar termos pares, exceto P[k] e p[0].
			As = As + 2*P[i];                //soma dos termos pares ponderados.
		}
		if(i%2 != 0){                        //condição para somar termos ímpares.    
			As = As + 4*P[i];                //soma dos termos ímpares ponderados. 
		}	
    }
    
    As = As + Asi + Asf;                     //soma a P[0] e P[k] aos termos ímpares e pares somados anteriormente.
    Asim = (h/3)*As;                           //cálculo final da área pelo método de Simpson 1/3.
                              
    
	printf("\nMétodo dos trapézios: A = %.5f",Atrap);      //finalizando, exibe a área calculada pelo método dos trapézios.
	printf("\nMétodo de Simpson 1/3: A = %.5f\n",Asim);     //finalizando, exibe a área calculada pelo método de Simpson 1/3.
	
    }
    printf("\nDeseja realizar uma nova soma?(s/S ou n/N):\n"); //pergunta se o usuário deseja realizar uma nova soma.
    
	scanf("%s",&cont);                              //atualiza a variável cont para que o código seja
	                                                //executado mais uma vez ou não.
	
	printf("\n");                                   //quebra de linha
    }
	
	return 0;                                //retorna o 0 para informar que o código foi bem executado.
}
