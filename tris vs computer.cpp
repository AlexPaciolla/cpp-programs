//PROGRAMMA ANCORA IN FASE DI SVILUPPO, VERRA' FATTO L'UPLOAD DEL PROGRAMMA AGGIORNATO COSTANTEMENTE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(){
	char a=' ';//le seguenti sono caselle, inizializzate come vuote
	char b=' ';
	char c=' ';
	char d=' ';
	char e=' ';
	char f=' ';
	char g=' ';
	char h=' ';
	char i=' ';

	char symbol;
	char cmp;
	bool repeat;
	char player;
	int match=1;
	char casella;
	bool winner=false;

	srand(time(NULL));


	do
	{
		printf("Vuoi giocare come giocatore X o come giocatore O? ");	//si decide che simbolo si vuole usare, il giocatore X inizia sempre per primo
		scanf(" %c",&symbol);

		if(symbol!='X'&&symbol!='O'){
			printf("Il simbolo puo' essere solo X oppure O\n");			//se il simbolo è diverso da X o da O si da un feedback all'utente
		}
	}
	while(symbol!='X'&&symbol!='O');									//si consente il reinserimento



	switch(symbol)
	{
		case 'O':	//il computer inizia per primo

			while(match<=9&&winner==false)
			{
				do
				{
					cmp=(rand()%9)+'a';

					switch(cmp)//controllo che la casella sia libera e compilazione della casella
					{
						case 'a':				//ogni caso ha la stessa struttura:
							if(a==' '){			//se la casella è vuota
								a='X';			//metti il simbolo in questione in quella casella
								repeat=false;	//non far ripetere il ciclo
							}else{
								repeat=true;
							}

							break;
						case 'b':
							if(b==' '){
								b='X';
								repeat=false;
							}else{
								repeat=true;
							}

							break;
						case 'c':
							if(c==' '){
								c='X';
								repeat=false;
							}else{
								repeat=true;
							}

							break;
						case 'd':
							if(d==' '){
								d='X';
								repeat=false;
							}else{
								repeat=true;
							}

							break;
						case 'e':
							if(e==' '){
								e='X';
								repeat=false;
							}else{
								repeat=true;
							}

							break;
						case 'f':
							if(f==' '){
								f='X';
								repeat=false;
							}else{
								repeat=true;
							}

							break;
						case 'g':
							if(g==' '){
								g='X';
								repeat=false;
							}else{
								repeat=true;
							}

							break;
						case 'h':
							if(h==' '){
								h='X';
								repeat=false;
							}else{
								repeat=true;
							}

							break;
						case 'i':
							if(i==' '){
								i='X';
								repeat=false;
							}else{
								repeat=true;
							}

							break;
					}
				}
				while(repeat==true);//controllo dell'input della casella che permette il reinserimeto in caso questa sia occupata o inesistente

				match++;

				printf("\n\n	 A | B | C\n");//stampaa di una mappa campione
				printf("	-----------\n");
				printf(" 	 D | E | F\n");
				printf("	-----------\n");
				printf(" 	 G | H | I\n\n");


				printf("\n\n	 %c | %c | %c\n",a,b,c);//stampa della mappa attuale
				printf("	-----------\n");
				printf(" 	 %c | %c | %c\n",d,e,f);
				printf("	-----------\n");
				printf(" 	 %c | %c | %c\n\n",g,h,i);


				if((a=='X'&&b=='X'&&c=='X')||(d=='X'&&e=='X'&&f=='X')||(g=='X'&&h=='X'&&i=='X')||(a=='X'&&d=='X'&&g=='X')||(b=='X'&&e=='X'&&h=='X')||(c=='X'&&f=='X'&&i=='X')||(a=='X'&&e=='X'&&i=='X')||(c=='X'&&e=='X'&&g=='X'))
				{
					printf("Il giocatore X ha vinto!");
					match+=9;//per uscire dal loop di gioco
					winner=true;
				}


				if(winner==false&&match<=9)
				{
					printf("E' il turno del giocatore O.\nQuale casella scegli? ");
					player='O';


					do
					{
						scanf(" %c",&casella);													//ricezione della casella in cui si vuole mettere il proprio simbolo

						if(casella>'i'||casella<'a')											//se la casella e' inesistente
						{
							printf("La casella inserita non esiste, inseriscine una valida: ");	//da un feedback all'utente
						}


						switch(casella)//controllo che la casella sia libera e compilazione della casella
						{
							case 'a':				//ogni caso ha la stessa struttura:
								if(a==' '){			//se la casella è vuota
									a=player;		//metti il simbolo in questione in quella casella
									repeat=false;	//non far ripetere il ciclo
								}else{
									repeat=true;
								}

								break;
							case 'b':
								if(b==' '){
									b=player;
									repeat=false;
								}else{
									repeat=true;
								}

								break;
							case 'c':
								if(c==' '){
									c=player;
									repeat=false;
								}else{
									repeat=true;
								}

								break;
							case 'd':
								if(d==' '){
									d=player;
									repeat=false;
								}else{
									repeat=true;
								}

								break;
							case 'e':
								if(e==' '){
									e=player;
									repeat=false;
								}else{
									repeat=true;
								}

								break;
							case 'f':
								if(f==' '){
									f=player;
									repeat=false;
								}else{
									repeat=true;
								}

								break;
							case 'g':
								if(g==' '){
									g=player;
									repeat=false;
								}else{
									repeat=true;
								}

								break;
							case 'h':
								if(h==' '){
									h=player;
									repeat=false;
								}else{
									repeat=true;
								}

								break;
							case 'i':
								if(i==' '){
									i=player;
									repeat=false;
								}else{
									repeat=true;
								}

								break;

						}


						if(repeat==true){//se la casella è occupata
							printf("La casella scelta e' gia' occuppata, inserisci il tuo simbolo in un'altra casella: ");//da un feedback all'utente
						}

					}
					while(casella<'a'||casella>'i'||repeat==true);//controllo dell'input della casella che permette il reinserimeto in caso questa sia occupata o inesistente

				}


				match++;

				system("cls");


				//stabilire il vincitore
				if((a=='O'&&b=='O'&&c=='O')||(d=='O'&&e=='O'&&f=='O')||(g=='O'&&h=='O'&&i=='O')||(a=='O'&&d=='O'&&g=='O')||(b=='O'&&e=='O'&&h=='O')||(c=='O'&&f=='O'&&i=='O')||(a=='O'&&e=='O'&&i=='O')||(c=='O'&&e=='O'&&g=='O'))
				{
					printf("Il giocatore O ha vinto!");
					match+=9;//per uscire dal loop di gioco
					winner=true;
				}
				else if(match>9)
				{
					printf("Abbiamo un pareggio!");
				}
			}
	}


	printf("\n\n	 %c | %c | %c\n",a,b,c);//stampa della mappa attuale
	printf("	-----------\n");
	printf(" 	 %c | %c | %c\n",d,e,f);
	printf("	-----------\n");
	printf(" 	 %c | %c | %c\n\n",g,h,i);


}
