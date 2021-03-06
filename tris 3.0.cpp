/*
	Name: tris 3.0
	Copyright: none
	Author: Alex Paciolla
	Date: 02/12/21 12:50
	Description: software per giocare a tris, codificato con l'utilizzo di matrici bidimensionali.
	   				
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//funzione per la stampan del titolo
void titolo()
{
	printf("	 _______   ______   _   ______ \n");
	printf("	|__   __| |  __  | | | |  ____|\n");
	printf("	   | |    | |__| | | | | |____ \n");
	printf("	   | |    |  _  _| | | |____  |\n");
	printf("	   | |    | | | |  | |  ____| |\n");
	printf("	   |_|    |_|  |_| |_| |______|\n");
	printf("\n");
	
	printf("Ricorda di inserire le caselle come lettere minuscole...\n\n");
}


int main(){
	while(true)
	{
		char toPrint[3][3];
		char realOne[3][3];
		char init='a';
		char symbol='X';
		char input;
		char num_players;
		char player;
		bool reinput;
		bool winner;
		int match=1;
		
		srand(time(NULL));
	
		//INIZIALIZZAZIONE MAPPA DA STAMPARE CON SPAZI VUOTI
		for(int y=0; y<3; y++){
			for(int x=0; x<3; x++){
				toPrint[x][y]=' ';
			}
		}
	
		//INIZIALIZAZZIONE DELLA MAPPA REALE CON LETTERE MINUSCOLE
		for(int y=0; y<3; y++){
			for(int x=0; x<3; x++){
				realOne[x][y]=init;
				init++;
			}
		}
	
		//output del titolo
		titolo();
	
		//RICHIESTA DI GIOCARE CONTRO IL COMPUTER O IN PvP
		do
		{
			printf("\nSeleziona il numero di giocatori [1 / 2]: ");
			scanf(" %c",&num_players);
	
			if(num_players!='1'&&num_players!='2')
			{
				printf("I giocatori possono essere solo 1 o 2!\n");
			}
		}
		while(num_players!='1'&&num_players!='2');
	
		if(num_players=='1')//SE SI GIOCA CONTRO IL COMPUTER
		{
			//SCELTA DEL SIMBOLO CON CUI SI VUOLE GIOCARE
			//La X inizia per prima in qualsiasi partita
			do
			{
				printf("Vuoi giocare come giocatore X o come giocatore O? ");	//si decide che simbolo si vuole usare, il giocatore X inizia sempre per primo
				scanf(" %c",&symbol);
	
				if(symbol!='X'&&symbol!='O')
				{
					printf("Il simbolo puo' essere solo X oppure O\n");			//se il simbolo ?? diverso da X o da O si da un feedback all'utente
				}
			}
			while(symbol!='X'&&symbol!='O');			//si consente il reinserimento
			//IL SIMBOLO ?? STATO SCELTO
		}
	
		//PULIZIA SCHERMO
		system("cls");
	
		//INIZIO DEL GAME LOOP
		while(match<=9)
		{
			//STAMPO IL TITOLO
			titolo();
	
			//STAMPA DELLA MAPPA CAMPIONE
			for(int y=0; y<3; y++){
	
				printf("	");//il seguente printf contiene elementi "decorativi"
	
				for(int x=0; x<3; x++){
					printf(" %c ",realOne[x][y]);
	
					if(x!=2){//il seguente if contiene elementi "decorativi"
						printf("|");
					}
				}
	
				if(y!=2){//il seguente if contiene elementi "decorativi"
					printf("\n	-----------\n");
				}
			}
	
			printf("\n\n");
	
			//STAMPA DELLA MAPPA ATTUALE
			for(int y=0; y<3; y++){
	
				printf("	");//il seguente printf contiene elementi "decorativi"
	
				for(int x=0; x<3; x++){
					printf(" %c ",toPrint[x][y]);
	
					if(x!=2){//il seguente if contiene elementi "decorativi"
						printf("|");
					}
				}
	
				if(y!=2){//il seguente if contiene elementi "decorativi"
					printf("\n	-----------\n");
				}
			}
	
	
			//I TURNI SI ALTERNANO
			if(match%2==1){
				player='X';
			}else{
				player='O';
			}
	
			do
			{
				if(num_players=='2'||(num_players=='1'&&((symbol=='X'&&player=='X')||(symbol=='O'&&player=='O')))){		//elenco dei casi in cui il giocatore deve inserire la casella
					//INPUT DEL GIOCATORE
					do
					{
						printf("\n\nE' il turno del giocatore %c.\nDove vuoi mettere il tuo simbolo? ", player);
						scanf(" %c",&input);
	
						if(input>'i'||input<'a')
						{
							printf("La casella inserita non esiste!");
						}
					}while(input>'i'||input<'a');
				}
				else if(num_players=='1'&&((symbol=='X'&&player=='O')||(symbol=='O'&&player=='X'))){		            //il computer deve inserire la sua casella
					input=(rand()%9)+'a';                                                                               //al momento la scelta della casella ?? casuale
				}                                                                                                       //la selezione intelligente arriver?? in futuro
	
	                                                                                                                               
				//COMPILAZIONE DELLA CASELLA
				for(int y=0; y<3; y++){
					for(int x=0; x<3; x++){
						if(realOne[x][y]==input&&toPrint[x][y]==' '){
							reinput=false;
							toPrint[x][y]=player;
						}else if(realOne[x][y]==input&&toPrint[x][y]!=' '){
							reinput=true;
							
							//FEEDBACK IN CASO DI CASELLA OCCUPATA
							if(num_players=='2'||(num_players=='1'&&((symbol=='X'&&match%2==1)||(symbol=='O'&&match%2==0)))){
								printf("La casella selezionata e' gia' occupata!");
							}                                                                             
						}                                                                                               
					}
				}
	
			}while(reinput==true);
	
			//PULIZIA SCHERMO
			system("cls");
	
			//AGGIORNAMENTO DEL TURNO
			match++;
	
			//CONTROLLO SE CI SONO VINCITORI
			//controllo le righe
			for(int y=0;y<3;y++){
				int x=0;
	
				if(toPrint[x][y]==toPrint[x+1][y]&&toPrint[x+1][y]==toPrint[x+2][y]&&toPrint[x+2][y]!=' '){
					match+=9; 
					winner=true;
					printf("\n\nIl giocatore %c ha vinto!\n\n", player);
				}
			}
	
			//controllo le colonne
			for(int x=0;x<3;x++){
				int y=0;
	
				if(toPrint[x][y]==toPrint[x][y+1]&&toPrint[x][y+1]==toPrint[x][y+2]&&toPrint[x][y+2]!=' '){
					match+=9;
					winner=true;
					printf("\n\nIl giocatore %c ha vinto!\n\n", player);
				}
			}
	
			//controllo la diagonale "aei"
			int x=0; int y=0;
			if(toPrint[x][y]==toPrint[x+1][y+1]&&toPrint[x][y]==toPrint[x+2][y+2]&&toPrint[x][y]!=' '){
				match+=9; 
				winner=true;
				printf("Il giocatore %c ha vinto!\n\n", player);
			}
			
			//controllo la diagonale "ceg"
			x=2; y=2;
			if(toPrint[x][y]==toPrint[x-1][y-1]&&toPrint[x][y]==toPrint[x-2][y-2]&&toPrint[x][y]!=' '){
				match+=9;
				winner=true;
				printf("Il giocatore %c ha vinto!\n\n", player);			
			}
	
			//in caso di pareggio
			if(match>9&&winner==false){
				printf("Abbiamo un pareggio!\n\n");
			}
		}
	
	
		//STAMPA DELLA MAPPA ATTUALE
		for(int y=0; y<3; y++){
	
			printf("	");//il seguente printf contiene elementi "decorativi"
	
			for(int x=0; x<3; x++){
				printf(" %c ",toPrint[x][y]);
	
				if(x!=2){//il seguente if contiene elementi "decorativi"
					printf("|");
				}
			}
	
			if(y!=2){//il seguente if contiene elementi "decorativi"
				printf("\n	-----------\n");
			}
		}
		
		//Azioni finali
		printf("\n\n");
		system("pause");
		system("cls");
	}
}
