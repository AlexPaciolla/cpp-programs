/*
	Name: tris
	Copyright: none
	Author: Alex Paciolla
	Date: 24/11/21 08:05
	Description: software che permette di giocare una partita a tris a 2 giocatori.
*/


#include <stdlib.h>
#include <stdio.h>

int main(){
	char a=' ';	//le seguenti sono caselle, inizializzate come vuote
	char b=' ';
	char c=' ';
	char d=' ';
	char e=' ';
	char f=' ';
	char g=' ';
	char h=' ';
	char i=' ';

	char player;		//prende il valore di X o di O
	char casella;		//casella in cui l'utente decide di inserire il suo simbolo
	int match=1;		//numero di turni del gioco. quando viene superato il 9 viene messa fine al game loop
	bool repeat=true;	//variabile utilizzata per il controllo dell'input, inizializzata come NON FALSA, per far ripetere il ciclo nel caso in cui venisse inserita una casella occupata


	printf("Ricorda di inserire le caselle come lettere minuscole durante il gioco!\n\n");


	while(match<=9)//inizio del loop di gioco
	{
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


		if(match%2==0)//i turni dei giocatorisi alternano, il primo turno spetta sempre alle X
		{
			printf("E' il turno del giocatore O.\nQuale casella scegli? ");
			player='O';
		}
		else
		{
			printf("E' il turno del giocatore X.\nQuale casella scegli? ");
			player='X';
		}


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
					}

					break;
				case 'b':
					if(b==' '){
						b=player;
						repeat=false;
					}

					break;
				case 'c':
					if(c==' '){
						c=player;
						repeat=false;
					}

					break;
				case 'd':
					if(d==' '){
						d=player;
						repeat=false;
					}

					break;
				case 'e':
					if(e==' '){
						e=player;
						repeat=false;
					}

					break;
				case 'f':
					if(f==' '){
						f=player;
						repeat=false;
					}

					break;
				case 'g':
					if(g==' '){
						g=player;
						repeat=false;
					}

					break;
				case 'h':
					if(h==' '){
						h=player;
						repeat=false;
					}

					break;
				case 'i':
					if(i==' '){
						i=player;
						repeat=false;
					}

					break;
			}


			if(repeat!=false){//se la casella è occupata
				printf("La casella scelta e' gia' occuppata, inserisci il tuo simbolo in un'altra casella: ");//da un feedback all'utente
			}

		}
		while(casella<'a'||casella>'i'||repeat!=false);//controllo dell'input della casella che permette il reinserimeto in caso questa sia occupata o inesistente


		match++;

		system("cls");


		//stabilire il vincitore
		if((a=='O'&&b=='O'&&c=='O')||(d=='O'&&e=='O'&&f=='O')||(g=='O'&&h=='O'&&i=='O')||(a=='O'&&d=='O'&&g=='O')||(b=='O'&&e=='O'&&h=='O')||(c=='O'&&f=='O'&&i=='O')||(a=='O'&&e=='O'&&i=='O')||(c=='O'&&e=='O'&&g=='O'))
		{
			printf("Il giocatore O ha vinto!");
			match+=9;//per uscire dal loop di gioco
		}
		else if((a=='X'&&b=='X'&&c=='X')||(d=='X'&&e=='X'&&f=='X')||(g=='X'&&h=='X'&&i=='X')||(a=='X'&&d=='X'&&g=='X')||(b=='X'&&e=='X'&&h=='X')||(c=='X'&&f=='X'&&i=='X')||(a=='X'&&e=='X'&&i=='X')||(c=='X'&&e=='X'&&g=='X'))
		{
			printf("Il giocatore X ha vinto!");
			match+=9;//per uscire dal loop di gioco
		}
		else if(match>9)
		{
			printf("Abbiamo un pareggio!");
		}

	}//fine del game loop


	printf("\n\n");
	printf("	 %c | %c | %c\n",a,b,c);
	printf("	-----------\n");
	printf(" 	 %c | %c | %c\n",d,e,f);
	printf("	-----------\n");
	printf(" 	 %c | %c | %c\n\n",g,h,i);


}
