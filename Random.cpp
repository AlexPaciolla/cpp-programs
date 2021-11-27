/*
	Name: random
	Copyright: none
	Author: Alex Paciolla
	Date: 18/10/21 21:27
	Description: estrae numeri random
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void){
	
	int max;//numero massimo
	int min;//numero minimo
	int numero;//numero casuale estratto
	int repeatA;//cicli do-while
	int repeatB;//cicli do-while
	char domand;
	
	
	
	printf("Qual e' il numero minimo da estrarre? ");
	scanf("%d",&min);
	
	printf("Qual e' il numero massimo da estrarre? ");
	scanf("%d",&max);
	
	
	max=max-min+1;

	srand(time(NULL));
	
	do
	{
		numero=(rand()%(max))+min;
	
		printf("Il numero e' %d",numero);
	
		repeatA=1;
		repeatB=1;
		
		printf("\nProdurre un altro numero?[y/n]");
		
		do
		{
			scanf(" %c",&domand);
			
			switch(domand)
			{
				case 'y':
				case 'Y':
					repeatA=1;
					repeatB=0;
					break;
				case 'n':
				case 'N':
					repeatA=0;
					repeatB=0;
					break;
				default:
					printf("Comando non riconosciuto,reinserire:");
					repeatB=1;
						
			}
		}
		while(repeatB==1);
	}
	while(repeatA==1);

	printf("Sessione terminata");
	
	return 0;
}