/*
	Name: snake
	Copyright: none
	Author: Alex Paciolla
	Date: 15/02/22
	Description: snake game
*/

/*
ARGOMENTI NON SVOLTI:

-FONDAMENTALI:
matrici		//per formare il campo di gioco e registrare le posizioni del serpente
kbhit()		//per ottenere l'input in momenti non definiti dal programmatore
system("cls")	//per cancellare tutto ciò che è presente sullo schermo//sostituibile con una serie di \b

-NON FONDAMENTALI:
frecce				//permette l'utilizzo delle frecce					//sostituibili con wasd
system("color **")		//cambia il colore dello sfondo e delle scritte		//evitabile
system("pause")		//in pratica attende che venga premuto un tasto		//fattibile a mano o evitabile
sleep(*)				//crea una pausa di * millisecondi					//possibile con un ciclo for o evitabile
file system (modificare, registrare, ottenere informazioni da un file)		//evitabile


*/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

//FRECCE
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

//DIMENSIONI DEL CAMPO DI GIOCO
#define X 50
#define Y 25

void initmatrix(int matrix[][X]);											//crea i bordi del campo
void printmatrix(int matrix[][X]);											//stampa il campo e tutto quello che c'è dentro
void zeromatrix(int snakePos[][2]);										//azzera tutti i valori di snakePos[][2]
void reinitmatrix(int matrix[][X], int snakePos[][2], int snakeDim, int applePos[]);	//aggiorna la matrice
void newApple(int applePos[], int snakePos[][2], int snakeDim);					//posiziona una nuova mela
void initSnake(int snakePos[][2]);											//posiziona il serpente all'inizio del gioco
void changePos(int snakePos[][2], int snakeDim);								//fa scalare gli elementi di snakePos[][2] avanti di una posizione per lasciare libera la posizione 0
void initGame(int matrix[][X], int snakePos[][2]);							//esegue le funzioni di inizio gioco
bool Loose(int snakePos[][2], int snakeDim);									//vero se si perde, altrimenti falso
char checkInput(int cmd, int oldcmd);										//controlla l'input e permette l'utilizzo delle frecce
char checkArrow(int cmd, int oldcmd);										//controllo che non sia una feccia, in caso positivo correggo il comando
int RcrdExperiment(int score);											//funzione sperimentale, salva il miglior punteggio in record.txt
//MOVIMENTO
void moveSnake(int cmd, int snakePos[][2]);									//chiama le funzioni di movimento in base all'input
void Down(int snakePos[][2]);
void Up(int snakePos[][2]);
void Right(int snakePos[][2]);
void Left(int snakePos[][2]);

//INTERFACCE GRAFICHE 
void gameOver(int score, int record);//finale
void youWon(int score, int record);	//finale
void Snake();			//iniziale

//provare a rendere piu efficiente il gioco

int main(){
	int matrix[Y][X];				//campo di gioco
	int snakePos[(X-2) * (Y-2)][2];	//elenco delle posizioni assunte dal serpente (0=X; 1=Y)
	
	while(true){
		char cmd=0;				//mossa inserita dall'utente
		char oldcmd=0;				//registra il comando precndente per controllare l'input
		bool win = false;			//variabile che pone fine al gioco quando il serpente copre tutta la mappa
		bool loose = false;			//variabile che pone fine al gioco quando si perde
		int snakeDim = 4;			//lunghezza iniziale del serpente
		int score = 0;				//punteggio
		int applePos[2] = {24, 17};	//posizione della mela (0=X; 1=Y)	
	
		Snake();
		initGame(matrix, snakePos);
		
		while(win!=true && loose!=true){
			reinitmatrix(matrix, snakePos, snakeDim, applePos);	//aggiorna i valori della matrice
	       	system("cls");									//cancella tutto ciò che era presente in precedenza
			printmatrix(matrix);							//stampa la matrice
			printf("\n\n\tSCORE: %d", score);
			
			if(cmd=='w' || cmd=='W' || cmd=='s' || cmd=='S' ){	//se si muove in verticale
				Sleep(30);	//crea un delay di X millisecondi (la funzione è inclusa in windows.h e accetta solo valori interi, ma sfrutta i millisecondi al posto dei secondi)
			}
			
			oldcmd = cmd;
			
			if (kbhit()){		//soluzione dell'input facoltativo: getch() prende l'informazione che causa l'attivazione di kbhit()
				cmd = getch();	//getch() riesce a ricevevre in input anche i caratteri inseriti prima della chiamata, come quello che ha fatto diventare vero kbhit
			}
			
			cmd = checkArrow(cmd, oldcmd);	//le frecce non permettono precisione nei comandi
			cmd = checkInput(cmd, oldcmd);
			
			if(cmd!=0){
				changePos(snakePos, snakeDim);//traslo tutte le posizioni del serpente più avanti nell'array
			}
			
			moveSnake(cmd, snakePos);
			
			if(applePos[0] == snakePos[0][0] && applePos[1] == snakePos[0][1]){//aumento la dimensione del serpente , incremento il punteggio e crea una nuova mela
				snakeDim++;						
				newApple(applePos, snakePos, snakeDim);	
				score++;
			}
				
			if(score == (X-2) * (Y-2) -5){
				win=true;
			}
			if(Loose(snakePos, snakeDim)){
				loose=true;
			}
		}//fine partita
		
		system("cls");
	
		int record = RcrdExperiment(score);	//PARTE SPERIMENTALE SUL SALVATAGGIO DEL MIGLIOR PUNTEGGIO IN UN FILE record.txt
		
		
		if(loose==true){
			gameOver(score, record);
		}
		if(win==true){
			youWon(score, record);
		}	
		
	}
}

int RcrdExperiment(int score){
	//PARTE SPERIMENTALE SUL SALVATAGGIO DEL MIGLIOR PUNTEGGIO IN UN FILE record.txt
	int record;
	FILE *filereader = fopen("SNAKErecord.txt", "r");
	
	fscanf(filereader, "%d", &record);	//prendo il valore contenuto in record.txt e lo registro in record
	
	if(score > record){
		FILE *filewriter = fopen("SNAKErecord.txt", "w");	//quando apre il file, cancella quello che c'è dentro
		
		fprintf(filewriter, "%d", score);	//scrivo nel file il valore di score
		record = score;
		
		fclose(filewriter);
	}
	
	fclose(filereader);//come di regola chiudo le due copie del file aperte
	
	return record;
	//FINE PARTE SPERIMENTALE
}

void moveSnake(int cmd, int snakePos[][2]){
	switch(cmd){//muove il serpente
		case 's':
		case 'S':
			Down(snakePos);
			break;
			
		case 'w':	
		case 'W':
			Up(snakePos);
			break;
			
		case 'd':	
		case 'D':
			Right(snakePos);
			break;
			
		case 'a':
		case 'A':
			Left(snakePos);
			break;
}
}

void reinitmatrix(int matrix[][X], int snakePos[][2], int snakeDim, int applePos[]){
	for(int i=1; i<Y-1; i++){
		for(int j=1; j<X-1; j++){
			for(int k=0; k<snakeDim; k++){
				if(snakePos[k][1] == i  &&  snakePos[k][0] == j){
					matrix[i][j]='$';	//'$' è un valore provvisorio, che viene cambiato nel ciclo for successivo
				}
			}
		}
	}
	
	for(int i=1; i<Y-1; i++){
		for(int j=1; j<X-1; j++){
			if(matrix[i][j] == '$'){
				matrix[i][j]='#';
			}else if(applePos[1] == i && applePos[0] == j){
				matrix[i][j]='@';
			}else{
				matrix[i][j]=' ';
			}
			
		}
	}
}

char checkArrow(int cmd, int oldcmd){
	if(cmd == 72){//controllo che non sia una feccia, in caso positivo correggo il comando
		cmd ='w';
	}else if(cmd == 80){
		cmd ='s';
	}else if(cmd == 75){
		cmd ='a';
	}else if(cmd ==77){
		cmd ='d';
	}
	
	return cmd;
}

char checkInput(int cmd, int oldcmd){
	if(cmd!=0){
		if((cmd=='s' || cmd=='S') && (oldcmd=='w' || oldcmd=='W')){//controllo che non si voglia invertire il senso di marcia e correggo
			cmd=oldcmd;
		}else if((cmd=='w' || cmd=='W') && (oldcmd=='s' || oldcmd=='S')){
			cmd=oldcmd;
		}else if((cmd=='a' || cmd=='A') && (oldcmd=='d' || oldcmd=='D')){
			cmd=oldcmd;
		}else if((cmd=='d' || cmd=='D') && (oldcmd=='a' || oldcmd=='A')){
			cmd=oldcmd;
		}
		else if((cmd!='w' && cmd!='W' && cmd!='s' && cmd!='S' && cmd!='a' && cmd!='A' && cmd!='d' && cmd!='D')){//se non è un comando riconosciuto
			cmd=oldcmd;
		}
	}
	return cmd;
}

void changePos(int snakePos[][2], int snakeDim){
	for(int i=snakeDim; i>=1; i--){ 
		snakePos[i][0] = snakePos[i-1][0];
		snakePos[i][1] = snakePos[i-1][1];
	}
}

//muovo solo la testa del serpente
void Down(int snakePos[][2]){
	snakePos[0][1] = snakePos[1][1]+1;
}
void Up(int snakePos[][2]){
	snakePos[0][1] = snakePos[1][1]-1;
}
void Right(int snakePos[][2]){
	snakePos[0][0] = snakePos[1][0]+1;
}
void Left(int snakePos[][2]){
	snakePos[0][0] = snakePos[1][0]-1;
}

void initSnake(int snakePos[][2]){
	snakePos[0][0]=(X-2)/2; 
	snakePos[1][0]=(X-2)/2;
	snakePos[2][0]=(X-2)/2;
	snakePos[3][0]=(X-2)/2;
	
	snakePos[0][1]=(Y-2)/2;
	snakePos[1][1]=(Y-2)/2 -1;
	snakePos[2][1]=(Y-2)/2 -2;
	snakePos[3][1]=(Y-2)/2 -3;
}

bool Loose(int snakePos[][2], int snakeDim){
	int flag=false;	

	if(snakePos[0][0]==0 || snakePos[0][1]==0 || snakePos[0][0]==X-1 || snakePos[0][1]==Y-1){
		flag=true;
		
	}else if(flag==false){
		for(int i=1; i<snakeDim && flag==false; i++){
			if(snakePos[0][0]==snakePos[i][0] && snakePos[0][1]==snakePos[i][1]){
				flag=true;
			}
		}
	}
	
	return flag;
}

void newApple(int applePos[], int snakePos[][2], int snakeDim){
	srand(time(NULL));
	bool flag=true;
	
	applePos[0]=(rand() % (X-3)) +1;
	applePos[1]=(rand() % (Y-3)) +1;
	
	for(int i=0; i<snakeDim && flag==1; i++){
		if(applePos[0]==snakePos[i][0] && applePos[1]==snakePos[i][1]){
			flag=false;
		}
	}
	
	if(flag==false){
		newApple(applePos, snakePos, snakeDim);
	}
}

void zeromatrix(int snakePos[][2]){
	for(int i=0; i<(X-2) * (Y-2); i++){
		for(int j=0; j<2; j++){
			snakePos[i][j]=0;
		}
	}
}

void initmatrix(int matrix[][X]){
	for(int i=0; i<Y; i++){
		for(int j=0; j<X; j++){
 			matrix[i][j]=' ';

			if(j==0 || j==X-1 || i==0 || i==Y-1){
	   		     matrix[i][j]='|';//tanti puntini vicini
			}
		}
	}
}

void printmatrix(int matrix[][X]){
	for(int i=0; i<Y; i++){
		printf("\n\t");
		
		for(int j=0; j<X; j++){
			printf("%c",matrix[i][j]);
		}
	}
}

void initGame(int matrix[][X], int snakePos[][2]){
	initmatrix(matrix);		//assegna i valori alla matrice
	zeromatrix(snakePos);	//azzera tutti i valori in snakePos
	initSnake(snakePos);	//inizializza le posizioni del serpente	
	system("color 80");
}

void Snake(){
	system("color 02");
	printf("\t ____ __    _     _     _  _  ____      \n");
	printf("\t|  __|  \\  | |   / \\   | |/ /|  __|   \n");
	printf("\t| |__|   \\ | |  /   \\  |   / |  _|    \n");
	printf("\t|___ | |\\ \\| | / ___ \\ |   \\ | |__  \n");
	printf("\t|____|_| \\___|/_/   \\_\\|_|\\_\\|____|\n\n");
	printf("\tCOMMANDS: WASD, wasd, or arrows\n\n\t");
	printf("\tGOOD LUCK!\n\n\t");
	system("pause");
}

void gameOver(int score, int record){
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
	printf("\tYOUR SCORE: %d\n\n\t", score);
	printf("\tYOUR RECORD: %d\n\n\t", record);
	system("pause");
	system("cls");
}

void youWon(int score, int record){
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
	printf("\t\tYOUR SCORE: %d\t", score);	
	printf("\t\tBEST RECORD: %d\n\n\t", record);
	system("pause");
	system("cls");
}