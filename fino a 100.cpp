/*
	Name: FINO A 100
	Copyright: none
	Author: Alex Paciolla
	Date: 15/11/21 14:24
	Description: 
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(){
	int usr;//numero scelto dall'utente
	int cmp=1;//numero scelto dal computer
	int tot=0;//somma di tutti i numeri
	int random;//variabile casuale per stabilire chi inizia
	int contatore=0;//contatore, che permette di creare il numero che permette all'utente di perdere
	
	srand(time(NULL));
	random=rand()%2;
	
	switch(random)
	{
		case 0:
			//il computer vince
			printf("\nInizia il computer:");
			
			do
			{
				printf("\nIl computer ha scelto %d",cmp);//output della scelta presa dal computer
				
				tot=tot+cmp;//calcolo del totale a seguito dell'inserimento
				printf("\nIl totale e' di %d",tot);//output del totale
				
				if(tot<100)//per evitare che una volta raggiunto il 100 venga nuovamente richiesto all'utente di inserire il suo numero
				{
     				do
					{
						printf("\nInserisci un numero tra 1 e 10: ");
						scanf("%d",&usr);//viene inserito il numero dall'utente

						if(usr<1||usr>10)
						{
							printf("\nNON BARARE");//da un feedback in caso di errore nell'inserimento
						}
					}while(usr<1||usr>10);//permette il reinserimento

					tot=tot+usr;//calcolo del totale a seguito dell'inserimento
					printf("\nIl totale e' di %d\n",tot);//output del totale
				}

				cmp=11-usr;//calcolo del nuovo numero del computer
				
			}while(tot<100);//da ripetere finchè non si raggiunge il totale di 100 come da regolamento
			
			printf("\nIl computer ha vinto!");//Sempre vero in questo caso
			
			break;
			
/*		case 1:
			//l'utente ha la possibilità di vincere, a patto che questo segua l'algoritmo giusto
			printf("\nInizi tu:");
			
			do
			{
				printf("\nInserisci un numero tra 1 e 10: ");
				scanf("%d",&usr);//viene inserito il numero dall'utente
				
				if(usr<1||usr>10)
				{
					printf("\nNON BARARE");//da un feedback in caso di errore nell'inserimento
				}
				
			}while(usr<1||usr>10);//permette il reinserimento
			
			tot=tot+usr;
			printf("\nIl totale e' di %d",tot);//output del totale
			
			switch(usr)
			{
				case 1://se viene scelto 1, che permette di avere una possibilità di vincere
					do
					{
						cmp=(rand()%10)+1;//il computer sceglie un numero casuale
						printf("\nIl computer ha scelto %d",cmp);//output della scelta presa dal computer
						
						tot=tot+cmp;//calcolo del totale a seguito dell'inserimento
						printf("\nIl totale e' di %d",tot);//output del totale
						
						do
						{
							printf("\nInserisci un numero tra 1 e 10: ");
							scanf("%d",&usr);//viene inserito il numero dall'utente
							
							if(usr<1||usr>10)
							{
								printf("\nNON BARARE");//da un feedback in caso di errore nell'inserimento
							}
							
						}while(usr<1||usr>10);//permette il reinserimento
						
						tot=tot+usr;//calcolo del totale a seguito dell'inserimento
						printf("\nIl totale e' di %d",tot);//output del totale
						
					}while(usr==11-cmp && tot<100);//finchè l'utente segue l'algoritmo
					
					if(tot>=100)
					{
						printf("\nHai vinto!");
					}
					else//l'utente, non avendo seguito l'algoritmo, perde
					{
						cmp=12-usr;
						printf("\nIl computer ha scelto %d",cmp);//output della scelta presa dal computer
						
						tot=tot+cmp;//calcolo del totale a seguito dell'inserimento
						printf("\nIl totale e' di %d",tot);//output del totale						
						
						do
						{
							do
							{
								printf("\nInserisci un numero tra 1 e 10: ");
								scanf("%d",&usr);//viene inserito il numero dall'utente
								
								if(usr<1||usr>10)
								{
									printf("\nNON BARARE");//da un feedback in caso di errore nell'inserimento
								}
								
							}while(usr<1||usr>10);//permette il reinserimento
							
							tot=tot+usr;//calcolo del totale a seguito dell'inserimento
							printf("\nIl totale e' di %d",tot);//output del totale
							
							cmp=11-usr;
							printf("\nIl computer ha scelto %d",cmp);//output della scelta presa dal computer
							
							tot=tot+cmp;
							printf("\nIl totale e' di %d",tot);//output del totale
							
						}while(usr==11-cmp && tot<100);//finchè l'utente segue l'algoritmo
						
						printf("\nIl computer ha vinto");
					}
					
					break;
					
				default:
					
					cmp=12-usr;
					printf("\nIl computer ha scelto %d",cmp);//output della scelta presa dal computer
					
					tot=tot+cmp;//calcolo del totale a seguito dell'inserimento
					printf("\nIl totale e' di %d",tot);//output del totale						
					
					do
					{
						cmp=11-usr;
						printf("\nIl computer ha scelto %d",cmp);//output della scelta presa dal computer
						
						tot=tot+cmp;
						printf("\nIl totale e' di %d",tot);//output del totale
						
						do
						{
							printf("\nInserisci un numero tra 1 e 10: ");
							scanf("%d",&usr);//viene inserito il numero dall'utente
							
							if(usr<1||usr>10)
							{
								printf("\nNON BARARE");//da un feedback in caso di errore nell'inserimento
							}
							
						}while(usr<1||usr>10);//permette il reinserimento
						
						tot=tot+usr;//calcolo del totale a seguito dell'inserimento
						printf("\nIl totale e' di %d",tot);//output del totale
						
					}while(usr==11-cmp && tot<100);//finchè l'utente segue l'algoritmo
					
					printf("\nIl computer ha vinto");
					
					break;
			}*/
			
	}	
}
