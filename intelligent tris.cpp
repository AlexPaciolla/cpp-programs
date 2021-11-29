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

	char symbol;
	char player;		//prende il valore di X o di O
	char casella;		//casella in cui l'utente decide di inserire il suo simbolo
	int match=1;		//numero di turni del gioco. quando viene superato il 9 viene messa fine al game loop
	bool repeat=true;	//variabile utilizzata per il controllo dell'input, inizializzata come NON FALSA, per far ripetere il ciclo nel caso in cui venisse inserita una casella occupata

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


	while(match<=9)
	{
		printf("\n\n	 A | B | C\n");//stampa di una mappa campione
		printf("	-----------\n");
		printf(" 	 D | E | F\n");
		printf("	-----------\n");
		printf(" 	 G | H | I\n\n");


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

			if((match%2==1&&symbol=='X')||(match%2==0&&symbol=='O'))
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
			else
			{
				if(symbol=='O')
				{
					player='X';
				}
				else
				{
					player='O';
				}

				//LA SCELTA INTELLIGENTE DELLA CASELLA E' ATTUALMENTE IN FASE DI PROGRAMMAZIONE
				//Il frammento di codice seguente è difettoso in quanto questo, in alcuni casi,
				//	fa andare in loop il programma: il computer inizia a provare all'infinito a
				//	mettere il suo simbolo in caselle occupate.
				if(a==b&&b!=' '){
					casella='c';
				}else if(a==c&&c!=' '){
					casella='b';
				}else if(c==b&&b!=' '){
					casella='a';
				}else if(e==f&&f!=' '){
					casella='d';
				}else if(e==d&&d!=' '){
					casella='f';
				}else if(f==d&&d!=' '){
					casella='e';
				}else if(g==h&&h!=' '){
					casella='i';
				}else if(g==i&&i!=' '){
					casella='h';
				}else if(i==h&&h!=' '){
					casella='g';
				}else if(a==i&&i!=' '){
					casella='e';
				}else if(a==e&&e!=' '){
					casella='i';
				}else if(i==e&&e!=' '){
					casella='a';
				}else if(c==e&&e!=' '){
					casella='g';
				}else if(c==g&&g!=' '){
					casella='e';
				}else if(e==g&&g!=' '){
					casella='c';
				}else if(a==d&&d!=' '){
					casella='g';
				}else if(a==g&&g!=' '){
					casella='d';
				}else if(d==g&&g!=' '){
					casella='a';
				}else if(b==e&&e!=' '){
					casella='h';
				}else if(b==h&&h!=' '){
					casella='e';
				}else if(e==h&&h!=' '){
					casella='b';
				}else if(c==f&&f!=' '){
					casella='i';
				}else if(c==i&&i!=' '){
					casella='f';
				}else if(f==i&&i!=' '){
					casella='c';
				}else if(symbol=='O'&&a==' '){
					casella='a';
				}else if(symbol=='O'&&c==' '){
					casella='c';
				}else if(symbol=='O'&&g==' '){
					casella='g';
				}else if(symbol=='O'&&i==' '){
					casella='i';
				}else if(e==' '){
					casella='e';
				}else if(b==' '){
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

	}

	printf("\n\n	 %c | %c | %c\n",a,b,c);//stampa della mappa attuale
	printf("	-----------\n");
	printf(" 	 %c | %c | %c\n",d,e,f);
	printf("	-----------\n");
	printf(" 	 %c | %c | %c\n\n",g,h,i);

}
