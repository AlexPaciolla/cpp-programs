/*
	Name: FINO A 100
	Copyright: none
	Author: Alex Paciolla
	Date: 15/11/21 14:24
	Description: 	Gioco in cui i due giocatori devono inserire un numero da 1 a 10, il quale viene sommato al totale.
					Chi inserisce per ultimo il numero, raggiungendo o superando dunque il 100, vince.
					La vittoria è resa possibile solo nel caso in cui venga seguito l'algoritmo corretto.
					Link alla spiegazione del gioco: https://www.youtube.com/watch?v=dUXW3Kh_kxo
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//FUNZIONE PER RICHIEDERE L'INSERIMENTO DEL NUMERO ALL'UTENTE

int UserInput()
{
	int usr;

	do
	{
		printf("\nInserisci un numero tra 1 e 10: ");
		scanf("%d",&usr);								//viene inserito il numero dall'utente

		if(usr<1||usr>10)
		{
			printf("\nNON BARARE");						//da un feedback in caso di errore nell'inserimento
		}

	}while(usr<1||usr>10);								//permette il reinserimento

	return usr;
}


//INIZIO DEL GIOCO

int main(){
	int usr;			//numero scelto dall'utente
	int cmp=1;			//numero scelto dal computer
	int tot=0;			//somma di tutti i numeri
	int random;			//variabile casuale per stabilire chi inizia
	int contatore=0;	//contatore, che permette di creare il numero che permette all'utente di perdere
	
	srand(time(NULL));
	random=rand()%2;
	
	switch(random)
	{
		case 0:
			//il computer vince
			printf("Inizia il computer:\n");
			
			do
			{
				printf("\nIl computer ha scelto %d\n",cmp);	//output della scelta presa dal computer
				
				tot=tot+cmp;								//calcolo del totale a seguito dell'inserimento
				printf("\nIl totale e' di %d\n",tot);			//output del totale
				
				if(tot<100)									//per evitare che una volta raggiunto il 100 venga nuovamente richiesto all'utente di inserire il suo numero
				{
					usr=UserInput();						//input del numero da parte dell'utente

					tot=tot+usr;							//calcolo del totale a seguito dell'inserimento
					printf("\nIl totale e' di %d\n",tot);	//output del totale
				}

				cmp=11-usr;									//calcolo del nuovo numero del computer

			}while(tot<100);								//da ripetere finchè non si raggiunge il totale di 100 come da regolamento

			printf("\nIl computer ha vinto!");				//Sempre vero in questo caso

			break;

		case 1:		//l'utente ha la possibilità di vincere, a patto che questo segua l'algoritmo giusto
			printf("Inizi tu:\n");

			usr=UserInput();									//input del numero da parte dell'utente
			
			tot=tot+usr;
			printf("\nIl totale e' di %d\n",tot);				//output del totale
			
			switch(usr)
			{
				case 1:		//se viene scelto 1, che permette di avere una possibilità di vincere
					do
					{
						cmp=(rand()%10)+1;							//il computer sceglie un numero casuale
						printf("\nIl computer ha scelto %d\n",cmp);	//output della scelta presa dal computer
						
						tot=tot+cmp;								//calcolo del totale a seguito dell'inserimento
						printf("\nIl totale e' di %d",tot);			//output del totale

						usr=UserInput();							//input del numero da parte dell'utente

						tot=tot+usr;								//calcolo del totale a seguito dell'inserimento
						printf("\nIl totale e' di %d\n",tot);		//output del totale

					}while(usr==11-cmp && tot<100);					//finchè l'utente segue l'algoritmo

					if(tot>=100)									//se si ha superato il 100, quindi si ha vinto
					{
						printf("\nHai vinto!");
					}
					else											//l'utente, non avendo seguito l'algoritmo, perde
					{
						if(tot<12)
						{
							cmp=12-tot;
						}
						else if(tot<23)
						{
							cmp=23-tot;
						}
						else if(tot<34)
						{
							cmp=34-tot;
						}
						else if(tot<45)
						{
							cmp=45-tot;
						}
						else if(tot<56)
						{
							cmp=56-tot;
						}
						else if(tot<67)
						{
							cmp=67-tot;
						}
						else if(tot<78)
						{
							cmp=78-tot;
						}
						else if(tot<89)
						{
							cmp=89-tot;
						}
						else if(tot<100)
						{
							cmp=100-tot;
						}

						printf("\nIl computer ha scelto %d\n",cmp);		//output della scelta presa dal computer

						tot=tot+cmp;									//calcolo del totale a seguito dell'inserimento
						printf("\nIl totale e' di %d\n",tot);			//output del totale

						do
						{
							usr=UserInput();								//input del numero da parte dell'utente

							tot=tot+usr;									//calcolo del totale a seguito dell'inserimento
							printf("\nIl totale e' di %d\n",tot);			//output del totale

							cmp=11-usr;
							printf("\nIl computer ha scelto %d\n",cmp);		//output della scelta presa dal computer

							tot=tot+cmp;
							printf("\nIl totale e' di %d\n",tot);			//output del totale

						}while(usr==11-cmp && tot<100);						//finchè l'utente segue l'algoritmo

						printf("\nIl computer ha vinto");
					}

					break;

				default:	//se non viene scelto 1, l'utende decide dunque di non seguire l'algoritmo

					cmp=12-usr;
					printf("\nIl computer ha scelto %d\n",cmp);		//output della scelta presa dal computer

					tot=tot+cmp;									//calcolo del totale a seguito dell'inserimento
					printf("\nIl totale e' di %d",tot);				//output del totale

					do
					{
						usr=UserInput();								//input del numero da parte dell'utente

						tot=tot+usr;									//calcolo del totale a seguito dell'inserimento
						printf("\nIl totale e' di %d\n",tot);			//output del totale

						cmp=11-usr;
						printf("\nIl computer ha scelto %d\n",cmp);		//output della scelta presa dal computer

						tot=tot+cmp;
						printf("\nIl totale e' di %d\n",tot);			//output del totale

					}while(usr==11-cmp && tot<100);						//finchè l'utente segue l'algoritmo

					printf("\nIl computer ha vinto");
					
					break;
			}

	}	
}
