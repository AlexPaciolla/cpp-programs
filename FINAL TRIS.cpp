/*
	Name: 	FINAL TRIS
	Copyright: none
	Author: Alex Paciolla, con la collaborazione di Andrea Brambilla
	Date: 25/11/21 08:54
	Description: Software che permette di giocare a Tris, sia in player vs player, sia contro il computer, con diversi gradi di difficoltà
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//funzione per la stampa del nome del gioco e per la stampa di una mappa campione
void interfaccia()
{
	printf("	 _______   ______   _   ______\n");
	printf("	|__   __| |  __  | | | |  ____|\n");
	printf("	   | |    | |__| | | | | |____\n");
	printf("	   | |    |  _  _| | | |____  |\n");
	printf("	   | |    | | | |  | |  ____| |\n");
	printf("	   |_|    |_|  |_| |_| |______|\n");
	printf("\n");
	
	printf("Ricorda di inserire le caselle come lettere minuscole...");
	printf("\n\n");
	printf("	 A | B | C \n");//stampa di una mappa campione
	printf("	-----------\n");
	printf(" 	 D | E | F \n");
	printf("	-----------\n");
	printf(" 	 G | H | I \n");
	printf("\n");
}


int main(){
	srand(time(NULL));

	while(true)
	{
		char a=' ';	//le seguenti sono caselle, inizializzate come vuote
		char b=' ';
		char c=' ';
		char d=' ';
		char e=' ';
		char f=' ';
		char g=' ';
		char h=' ';
		char i=' ';

		char num_players;	//se viene assegnato come valore 1 si gioca contro il computer, altrimenti si gioca contro un altro giocatore
		char difficulty;	//scelta della difficoltà tra facile e media
		char symbol;		//nel caso in cui ci sia solo un giocatore, si decide se far iniziare per primo il computer o no
		char player;		//prende il valore di X o di O
		char casella;		//casella in cui l'utente decide di inserire il suo simbolo
		int match=1;		//numero di turni del gioco. quando viene superato il 9 viene messa fine al game loop
		int computer_choice;//variabile casuale che stabilisce se far fare sempre la mossa migliore al computer
		bool repeat=true;	//variabile utilizzata per il controllo dell'input, inizializzata come NON FALSA, per far ripetere il ciclo nel caso in cui venisse inserita una casella occupata

		printf("	 _______   ______   _   ______ \n");
		printf("	|__   __| |  __  | | | |  ____|\n");
		printf("	   | |    | |__| | | | | |____ \n");
		printf("	   | |    |  _  _| | | |____  |\n");
		printf("	   | |    | | | |  | |  ____| |\n");
		printf("	   |_|    |_|  |_| |_| |______|\n");

		printf("\nRicorda di inserire le caselle come lettere minuscole durante il gioco!\n\n");

		do
		{
			printf("Seleziona il numero di giocatori [1 / 2]: ");
			scanf(" %c",&num_players);

			if(num_players!='1'&&num_players!='2')
			{
				printf("I giocatori possono essere solo 1 o 2!\n");
			}
		}
		while(num_players!='1'&&num_players!='2');


		switch(num_players)
		{
			case '1':
				//SCELTA DELLA DIFFICOLTA' A CUI SI VUOLE GIOCARE
				do
				{
					printf("\nSeleziona la difficolta':\n	f	facile\n	m	media\n\nA che difficolta' vuoi giocare? ");
					scanf(" %c",&difficulty);

					if(difficulty!='f'&&difficulty!='m')
					{
						printf("Grado di difficoltà non riconosciuto.");
					}
				}
				while(difficulty!='f'&&difficulty!='m');

				//SCELTA DEL SIMBOLO CON CUI SI VUOLE GIOCARE
				//La X inizia per prima in qualsiasi partita
				do
				{
					printf("Vuoi giocare come giocatore X o come giocatore O? ");	//si decide che simbolo si vuole usare, il giocatore X inizia sempre per primo
					scanf(" %c",&symbol);

					if(symbol!='X'&&symbol!='O')
					{
						printf("Il simbolo puo' essere solo X oppure O\n");			//se il simbolo è diverso da X o da O si da un feedback all'utente
					}
				}
				while(symbol!='X'&&symbol!='O');			//si consente il reinserimento
				//IL SIMBOLO è STATO SCELTO

				system("cls");

				while(match<=9)
				{
					interfaccia();

					printf("\n\n	 %c | %c | %c\n",a,b,c);//stampa della mappa attuale
					printf("	-----------\n");
					printf(" 	 %c | %c | %c\n",d,e,f);
					printf("	-----------\n");
					printf(" 	 %c | %c | %c\n\n",g,h,i);


					if((match%2==1&&symbol=='X')||(match%2==0&&symbol=='O'))
					{
						printf("Dove vuoi mettere il tuo simbolo? ");
					}

					do
					{

						if((match%2==1&&symbol=='X')||(match%2==0&&symbol=='O'))	//SCELTA DELLA CASELLA DA PARTE DELL'UTENTE
						{
							if(symbol=='X')
							{
								player='X';
							}
							else
							{
								player='O';
							}

							scanf(" %c",&casella);

							if(casella>'i'||casella<'a')											//se la casella e' inesistente
							{
								printf("La casella inserita non esiste, inseriscine una valida: ");	//da un feedback all'utente
							}
						}
						else														//SCELTA DELLA CASELLA DA PARTE DEL COMPUTER
						{
							if(symbol=='O')
							{
								player='X';
							}
							else
							{
								player='O';
							}

							if(difficulty=='f')
							{
								//SCELTA DELLA CASELLA IN MODO COMPLETAMENTE CASUALE
								casella=(rand()%9)+'a';
							}
							else if(difficulty=='m')
							{
								//SCELTA DELLA CASELLA """INTELLIGENTE"""
								//LA SCELTA INTELLIGENTE DELLA CASELLA E' ATTUALMENTE IN FASE DI PROGRAMMAZIONE
								//Il frammento di codice seguente prende in considerazione tutti i casi possibili,
								//	verrà presto pubblicato il codice programmato con array bidimensionali e con
								//  un conseguente aumento della chiarezza del codice.
								
								computer_choice=rand()%3;
								
								if(a==b&&b!=' '){
									casella='c';
								}else if(a==c&&c!=' '&&b==' '){
									casella='b';
								}else if(c==b&&b!=' '&&a==' '){
									casella='a';
								}else if(e==f&&f!=' '&&d==' '){
									casella='d';
								}else if(e==d&&d!=' '&&f==' '){
									casella='f';
								}else if(f==d&&d!=' '&&e==' '){
									casella='e';
								}else if(g==h&&h!=' '&&i==' '){
									casella='i';
								}else if(g==i&&i!=' '&&h==' '){
									casella='h';
								}else if(i==h&&h!=' '&&g==' '){
									casella='g';
								}else if(a==i&&i!=' '&&e==' '){
									casella='e';
								}else if(a==e&&e!=' '&&i==' '){
									casella='i';
								}else if(i==e&&e!=' '&&a==' '){
									casella='a';
								}else if(c==e&&e!=' '&&g==' '){
									casella='g';
								}else if(c==g&&g!=' '&&e==' '){
									casella='e';
								}else if(e==g&&g!=' '&&c==' '){
									casella='c';
								}else if(a==d&&d!=' '&&g==' '){
									casella='g';
								}else if(a==g&&g!=' '&&d==' '){
									casella='d';
								}else if(d==g&&g!=' '&&a==' '){
									casella='a';
								}else if(b==e&&e!=' '&&h==' '){
									casella='h';
								}else if(b==h&&h!=' '&&e==' '){
									casella='e';
								}else if(e==h&&h!=' '&&b==' '){
									casella='b';
								}else if(c==f&&f!=' '&&i==' '){
									casella='i';
								}else if(c==i&&i!=' '&&f==' '){
									casella='f';
								}else if(f==i&&i!=' '&&c==' '){
									casella='c';
								}else if(symbol=='O'&&a==' '){
									casella='a';
								}else if(symbol=='O'&&c==' '){
									casella='c';
								}else if(symbol=='O'&&g==' '){
									casella='g';
								}else if(symbol=='O'&&i==' '){
									casella='i';
								}else if((computer_choice==1||computer_choice==2)&&e==' '){ //computer choice è una variabile casuale che stabilisce
									casella='e';                     						//se occupare una casella vincente, facendo in modo che la partita
								}else if(b==' '){                   				        //vada in pareggio, oppure mettere il proprio simbolo in un'altra casella
									casella='b';
								}else if(d==' '){
									casella='d';
								}else if(h==' '){
									casella='h';
								}else if(f==' '){
									casella='f';
								}else{
									casella=(rand()%9)+'a';
								}
							}

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
						}//fine dello switch


						if(repeat==true&&((player=='X'&&match%2==1)||(player=='O'&&match%2==0)))
						{																									//se la casella è occupata ed è il turno dell'utente
							printf("La casella scelta e' gia' occuppata, inserisci il tuo simbolo in un'altra casella: ");	//da un feedback all'utente
						}

					}
					while(casella<'a'||casella>'i'||repeat==true);


					system("cls");//pulizia dello schermo

					match++;//aggiornamento della mossa


					//stabilire il vincitore
					if((a=='O'&&b=='O'&&c=='O')||(d=='O'&&e=='O'&&f=='O')||(g=='O'&&h=='O'&&i=='O')||(a=='O'&&d=='O'&&g=='O')||(b=='O'&&e=='O'&&h=='O')||(c=='O'&&f=='O'&&i=='O')||(a=='O'&&e=='O'&&i=='O')||(c=='O'&&e=='O'&&g=='O'))
					{
						printf("\n  Il giocatore O ha vinto!");
						match+=9;//per uscire dal loop di gioco
					}
					else if((a=='X'&&b=='X'&&c=='X')||(d=='X'&&e=='X'&&f=='X')||(g=='X'&&h=='X'&&i=='X')||(a=='X'&&d=='X'&&g=='X')||(b=='X'&&e=='X'&&h=='X')||(c=='X'&&f=='X'&&i=='X')||(a=='X'&&e=='X'&&i=='X')||(c=='X'&&e=='X'&&g=='X'))
					{
						printf("\n  Il giocatore X ha vinto!");
						match+=9;//per uscire dal loop di gioco
					}
					else if(match>9)
					{
						printf("\n  Abbiamo un pareggio!");
					}

				}

				break;

			case '2':

				system("cls");

				while(match<=9)//inizio del loop di gioco
				{
					interfaccia();

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
							default:
								repeat=false;
						}


						if(repeat==true)																					    //se la casella è occupata
						{
							printf("\nLa casella scelta e' gia' occuppata, inserisci il tuo simbolo in un'altra casella: ");	//da un feedback all'utente
						}

					}
					while(casella<'a'||casella>'i'||repeat==true);//controllo dell'input della casella che permette il reinserimeto in caso questa sia occupata o inesistente


					match++;

					system("cls");


					//stabilire il vincitore
					//per stabilire il vincitore vengono attualmente elencati tutti i casi possibili
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
		}

		printf("\n\n	 %c | %c | %c\n",a,b,c);//stampa della mappa attuale
		printf("	-----------\n");
		printf(" 	 %c | %c | %c\n",d,e,f);
		printf("	-----------\n");
		printf(" 	 %c | %c | %c\n\n",g,h,i);

		system("pause");

		system("cls");
	}
}