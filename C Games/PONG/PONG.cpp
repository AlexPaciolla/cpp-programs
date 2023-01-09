/*
	Name: PONG 1vs1, PONG VS WALL, PONG VS AI
	Copyright: none
	Author: Alex Paciolla
	Date: 15/02/22
	Description: arcade pong, la pallina rimbalza contro il muro e lo distrugge
*/


//creare angoli di direzione meno ampi
//creare la modalità difficile: la pallina viaggia in modo molto piu casuale rispetto alla modalità normale

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

#define UP 72
#define DOWN 80

#define X 50	
#define Y 25

char chooseMode();													//permette di scegliere la modalità di gioco
void initmatrix(int matrix[][X]);										//crea i bordi del campo
void initGame(int matrix[][X], int bat1[][2], int bat2[][2]);				//posiziona le racchette e cambia colore
void zeromatrix(int bat[][2]);										//azzera i valori di posizione delle racchette
void printmatrix(int matrix[][X]);										//stampa il campo
void reinitmatrix(int matrix[][X], int bat1[][2], int bat2[][2], int ball[]);	//aggiorna la motrice
void initBat(int bat[][2], int nbat);									//posiziona le racchette
int checkDirection(int bat1[][2], int bat2[][2], int ball[], int direzione);	//modifica la direzione della pallina
void moveBall(int *direzione, int ball[], int *score1, int *score2);			//sposta la palla e quando necessario incrementa il punteggio
void Clamp(int ball[]);												//tiene la palla dentro lo schermo
int checkScore(int ball[]);											//controlla se si ha fatto punto
int CommandIn();													//riceve la direzione in cui muovere la palina dall'utente

//MOVIMENTO RACCHETTE
void moveBat_mode2(int bat[][2], int cmd);
void UPBat(int bat[][2]);
void DOWNBat(int bat[][2]);

//MODALITA DI GIOCO
void Mode1(int matrix[][X]);
void Mode2(int matrix[][X]);

//INTERFACCE GRAFICHE
void Pong();				//iniziale	//generale
void win1();				//finale
void win2();				//finale
void gameOver();			//finale
void youWon();				//finale

int main(){
	int matrix[Y][X];
	srand(time(NULL));
		
	while(true){
		Pong();
		
		char mode = chooseMode();
		
		initmatrix(matrix);		
		
		if(mode == '1'){				//PONG 1vs1
			Mode1(matrix);
			
		}else if(mode == '2'){			//PONG vs AI
			Mode2(matrix);
		}
	}
}

char chooseMode(){	//permette di inserire la modalità
	char usr;
	
	do{
		printf("\tChoose a game mode: ");
		usr = getch();
		printf("%c", usr);
		
		if(usr!='1' && usr!='2'){
			printf("\n\tMODE NOT AVAILABLE!\n");
		}
	}while(usr!='1' && usr!='2');
	
	return usr;
}

void initmatrix(int matrix[][X]){			//creai i bordi del campo
	for(int i=0; i<Y; i++){
		for(int j=0; j<X; j++){
 			matrix[i][j]=' ';

			if(j==0 || j==X-1 || i==0 || i==Y-1){
	   		     matrix[i][j]='|';
			}
		}
	}
}

void printmatrix(int matrix[][X]){			//stampa il campo
	for(int i=0; i<Y; i++){
		printf("\n\t");
		
		for(int j=0; j<X; j++){
			printf("%c",matrix[i][j]);
		}
	}
}

void zeromatrix(int bat[][2]){			//azzera i valori di una matrice 5*2
	for(int i=0; i<5; i++){
		for(int j=0; j<2; j++){
			bat[i][j]=0;
		}
	}
}

void initBat(int bat[][2], int nbat){	//stabilisco le posizioni iniziali delle racchette
	for(int i=0; i<5; i++){
		bat[i][0] = Y/2 -2 +i;
	}
		
	if(nbat == 1){
		for(int i=0; i<5; i++){
			bat[i][1] = 1;			
		}
	}else if(nbat == 2){
		for(int i=0; i<5; i++){
			bat[i][1] = X-2;			
		}		
	}
}

void initGame(int matrix[][X], int bat1[][2], int bat2[][2]){
	initmatrix(matrix);		//crea i bordi del campo
	
	zeromatrix(bat1);		//azzera tutti i valori precedenti delle racchette per sicurezza
	zeromatrix(bat2);
	
	initBat(bat1, 1);		//inizializza le posizioni delle racchette
	initBat(bat2, 2);
	system("color 80");		//cambia colore
}

void reinitmatrix(int matrix[][X], int bat1[][2], int bat2[][2], int ball[]){	//aggiorna la matrice
	for(int i=1; i<Y-1; i++){
		for(int j=1; j<X-1; j++){
			for(int k=0; k<5; k++){
				if(bat1[k][0] == i && bat1[k][1] == j  ||  bat2[k][0] == i && bat2[k][1] == j){
					matrix[i][j]='$';	//'$' è un valore provvisorio, che viene cambiato nel ciclo for successivo
				}
			}
		}
	}
	
	for(int i=1; i<Y-1; i++){
		for(int j=1; j<X-1; j++){
			if(matrix[i][j] == '$'){
				matrix[i][j]='#';
			}else if(ball[0] == i && ball[1] == j){
				matrix[i][j]='@';
			}else{
				matrix[i][j]=' ';
			}
			
		}
	}
}

int checkScore(int ball[]){	//controlla se si ha fatto punto
	if(ball[1] == 1){
		ball[0] = Y/2;
		ball[1] = X/2;
		return 1000;
	}else if(ball[1] == X-2){
		ball[0] = Y/2;
		ball[1] = X/2;
		return 2000;
	}else{
		return 0;
	}
}

int checkDirection(int bat1[][2], int bat2[][2], int ball[], int direzione){	//si occupa i modificare la direzione della pallina
	for(int i=0; i<5; i++){								//controllo che la palla non sia in prossimità delle racchette
		if(bat1[i][0] == ball[0] && bat1[i][1] == ball[1]){
			switch(i){			//in base al punto di contatto cambia la direzione della pallina
				case 0:
					return 60;
				case 1:
					return 45;
				case 2:
					return 0;
				case 3:
					return -45;
				case 4:
					return -60;
			}
		}else if(bat2[i][0] == ball[0] && bat2[i][1] == ball[1]){
			switch(i){
				case 0:
					return 120;
				case 1:
					return 135;
				case 2:
					return 180;
				case 3:
					return -135;
				case 4:
					return -120;
			}
		}
	}
	
	if(ball[1] == 1){	//controllo se è stato fatto punto e in caso positivo riposiziono la pallina al centro
		ball[0] = Y/2;
		ball[1] = X/2;
		return 1000;
		
	}else if(ball[1] == X-2){
		ball[0] = Y/2;
		ball[1] = X/2;
		return 2000;
		
	}else if(ball[0] == 1 || ball[0] == Y-2){	//inverto la direzione se la pallina va contro un muro
		return -1*direzione;
	}else{
		return direzione;	//se non ci sono contatti con niente la pallina matiene la sua direzione
	}
}

void moveBall(int *direzione, int ball[], int *score1, int *score2){
	switch(*direzione){	//muovo la palla
		case 60://approx 60°
			ball[1]+=2;
			ball[0]-=1+(rand()%2);	//la variabilità rende più alta l'inclinazione
			break;
		case 45://approx 45°
			ball[1]+=2;
			ball[0]-=1;
			break;
		case 0:
			ball[1]+=2;
			break;
		case -45:
			ball[1]+=2;
			ball[0]+=1;
			break;
		case -60:
			ball[1]+=2;
			ball[0]+=1+(rand()%2);
			break;
		case -120:
			ball[1]-=2;
			ball[0]+=1+(rand()%2);
			break;
		case -135:
			ball[1]-=2;
			ball[0]+=1;
			break;
		case 180:
			ball[1]-=2;
			break;
		case 135:
			ball[1]-=2;
			ball[0]-=1;
			break;
		case 120:
			ball[1]-=2;
			ball[0]-=1+(rand()%2);
			break;
		case 1000:
			*score2+=1;
			*direzione = 180;
			break;
		case 2000:
			*score1+=1;
			*direzione = 0;	
			break;
	}
}

void Clamp(int ball[]){	//fa in modo che la palina rimanga dentro i muri
	while(ball[0] < 1){
		ball[0]++;
	}
	while(ball[0] > Y-2){
		ball[0]--;		
	}
	while(ball[1] < 1){
		ball[1]++;		
	}
	while(ball[1] > X-2){
		ball[1]--;		
	}
}

int CommandIn(){			//riceve l'input dell'utente
	int cmd;
	
	if (kbhit()){			//soluzione dell'input facoltativo: getch() prende l'informazione di kbhit()
		cmd = getch();
		return cmd;
	}else{
		return 0;
	}
}

void UPBat(int bat[][2]){				//muove la racchetta verso l'alto
	if(bat[0][0] > 1){
		for(int i=0; i<5; i++){
			bat[i][0]--;
		}		
	}
}
void DOWNBat(int bat[][2]){
	if(bat[4][0] < Y-2){
		for(int i=0; i<5; i++){
			bat[i][0]++;
		}		
	}
}

void moveBat(int bat1[][2], int bat2[][2], int cmd){	//riceve i comandi per muovere la racchetta e la muove
	switch(cmd){
		case 'W':
		case 'w':
			UPBat(bat1);
			break;
		case 'S':
		case 's':
			DOWNBat(bat1);
			break;
		case 'O':
		case 'o':
		case UP:
			UPBat(bat2);
			break;
		case 'L':
		case 'l':
		case DOWN:
			DOWNBat(bat2);
			break;
	}
}

void moveBat_mode2(int bat[][2], int cmd){	//riceve i comandi per muovere la racchetta 1 e la muove
	switch(cmd){
		case 'W':
		case 'w':
		case 'O':
		case 'o':
		case UP:
			UPBat(bat);
			break;
		case 'S':
		case 's':
		case 'L':
		case 'l':
		case DOWN:
			DOWNBat(bat);
			break;
	}
}

void Mode1(int matrix[][X]){
	bool win = false;			//vero se qualcuno vince
	int ball[2] = {Y/2, X/2};	//1=x, 0=y; coordinate della palla
	int cm1, cm2, cm3, cm4;		//comandi dati dai giocatori (sono 4 per aumentare la sensibilità del programma
	int bat1[5][2], bat2[5][2];	//1=x, 0=y; coordinate delle racchette
	int score1=0; int score2=0;	//punteggi di ogni giocatore
	int direzione;				//direzione della pallina, in base al suo valore la direzione cambia
	
	if(rand()%2==0){	//a ogni partita ha il 50% di possibilità di partire in direzione di una specifica racchetta
		direzione=0;
	}else{
		direzione=180;
	}
	
	initGame(matrix, bat1, bat2);	//operazioni di inizio gioco
	
	while(win!=true){
		cm1 = CommandIn();		
		cm2 = CommandIn();	
		cm3 = CommandIn();	
		cm4 = CommandIn();
		
		moveBat(bat1, bat2, cm1);	//muovo le racchette
		moveBat(bat1, bat2, cm2);	//muovo le racchette
		moveBat(bat1, bat2, cm3);	//muovo le racchette
		moveBat(bat1, bat2, cm4);	//muovo le racchette
		
		reinitmatrix(matrix, bat1, bat2, ball);	//aggiorna i valori della matrice
		system("cls");						//pulisco lo schermo
		printmatrix(matrix);				//ristampo la matrice
		printf("\n\tSCORE 1:\t\t\t\tSCORE 2:\n\t%d\t\t\t\t\t%d", score1, score2);
		
		direzione = checkDirection(bat1, bat2, ball, direzione);	//cambio la direzione della palla
		
		moveBall(&direzione, ball, &score1, &score2);
		
		Clamp(ball);	//reimmetto la pallina nel campo 
		
		if(score1==10 || score2==10){	//termino il ciclo se qualcuno ha vinto
			win=true;
		}
		
		cm1=0; //azzerando i comandi si fa in modo che la mazza non continui a muoversi
		cm2=0;		
	}
	
	if(score1>score2){	//stampo l'interfaccia finale
		win1();
	}else{
		win2();
	}
}

void Mode2(int matrix[][X]){
	bool win = false;			//vero se qualcuno vince
	int ball[2] = {Y/2, X/2};	//1=x, 0=y; coordinate della palla
	int cmd;					//comand0 dato dal giocatore
	int bat1[5][2], bat2[5][2];	//1=x, 0=y; coordinate delle racchette
	int score1=0; int score2=0;	//punteggi di ogni giocatore
	int direzione;				//direzione della pallina, in base al suo valore la direzione cambia
	
	if(rand()%2==0){	//a ogni partita ha il 50% di possibilità di partire in direzione di una specifica racchetta
		direzione=0;
	}else{
		direzione=180;
	}
	
	initGame(matrix, bat1, bat2);	//operazioni di inizio gioco
	
	while(win!=true){
		cmd = CommandIn();	
		
		moveBat_mode2(bat2, cmd);	//muovo la racchetta dell'utente
		
		if(ball[0] > bat1[4][0]){	//muovo la racchetta automatica
			DOWNBat(bat1);			
		}else if(ball[0] < bat1[0][0]){
			UPBat(bat1);
		}
		
		reinitmatrix(matrix, bat1, bat2, ball);		//aggiorna i valori della matrice
		system("cls");							//pulisco lo schermo
		printmatrix(matrix);					//ristampo la matrice
		printf("\n\tSCORE 1:\t\t\t\tSCORE 2:\n\t%d\t\t\t\t\t%d", score1, score2);
		
		direzione = checkDirection(bat1, bat2, ball, direzione);	//cambio la direzione della palla
		
		moveBall(&direzione, ball, &score1, &score2);
		
		Clamp(ball);	//reimmetto la pallina nel campo 
		
		if(score1==10 || score2==10){	//termino il ciclo se qualcuno ha vinto
			win=true;
		}
		
		cmd=0; //azzerando i comandi si fa in modo che la mazza non continui a muoversi		
	}
	
	system("cls");
	
	if(score1>score2){	//stampo l'interfaccia finale
		gameOver();
	}else{
		youWon();
	}	
}

void Pong(){
	system("cls");
	system("color 0f");
	printf("\t _____ _______ __    _ _______ \n");
	printf("\t|     |  ___  |  \\  | |  _____|\n");
	printf("\t|  O  | |   | |   \\ | | |  ___  \n");
	printf("\t|  ___| |___| | |\\ \\| | |_|_  | \n");
	printf("\t|_|   |_______|_| \\___|_______| \n");
	printf("\t COMMANDS: W and S, O and L\n");
	printf("\t PONG MODES:\n\n");
	printf("\t 1\tPONG PvP\n");
	printf("\t 2\tPONG vs COMPUTER\n\n");
}

void win1(){
	system("cls");
	system("color 0a");
	printf("\t  __  _    _ _ __    _ ____ \n");
	printf("\t /  || |  | | |  \\  | |  __|\n");
	printf("\t  | || |  | | |   \\ | | |__ \n");
	printf("\t  | || \\/\\/ | | |\\ \\| |___ |\n");
	printf("\t  |_| \\_/\\_/|_|_| \\___|____|\n\n\t");
	system("pause");
}
void win2(){
	system("cls");
	system("color 0a");
	printf("\t ____  _    _ _ __    _ ____ \n");
	printf("\t/__  || |  | | |  \\  | |  __|\n");
	printf("\t|  __|| |  | | |   \\ | | |__ \n");
	printf("\t| |__ | \\/\\/ | | |\\ \\| |___ |\n");
	printf("\t|____| \\_/\\_/|_|_| \\___|____|\n\n");
	system("pause");
}

void gameOver(){
	system("color 0c");
	printf("\t _______     _     __    __ ______   \n");
	printf("\t|  _____|   / \\   |  \\  /  |  ____|\n");
	printf("\t| | ____   /   \\  | |\\\\//| |  ___|\n");
	printf("\t| |_|_  | / ___ \\ | | \\/ | | |____ \n");
	printf("\t|_______|/_/   \\_\\|_|    |_|______|\n");
	printf("\t _______ __      __ ______ _____     \n");
	printf("\t|  ___  |\\ \\    / /|  ____|     \\ \n");
	printf("\t| |   | | \\ \\  / / |  ___||   __/  \n");
	printf("\t| |___| |  \\ \\/ /  | |____| |\\ \\ \n");
	printf("\t|_______|   \\__/   |______|_| \\_\\ \n\n\t");
	system("pause");
	system("cls");
}

void youWon(){
	system("color 0a");
	printf("\t _    _  _______ _    _     \n");
	printf("\t\\ \\  / /|  ___  | |  | |  \n");
	printf("\t \\ \\/ / | |   | | |  | |  \n");
	printf("\t  \\  /  | |___| | |__| |   \n");
	printf("\t  |__|  |_______|______|    \n");
	printf("\t _    _ _______ __    _     \n");
	printf("\t| |  | |  ___  |  \\  | |   \n");
	printf("\t| |  | | |   | |   \\ | |   \n");
	printf("\t| \\/\\/ | |___| | |\\ \\| |\n");
	printf("\t \\_/\\_/|_______|_| \\___| \n\n");
	system("pause");
	system("cls");
}