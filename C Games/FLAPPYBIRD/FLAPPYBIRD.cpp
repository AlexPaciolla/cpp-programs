/*
	Name: FLAPPY BIRD
	Copyright: none
	Author: Alex Paciolla
	Date: 15/02/22
	Description: flappy bird (arcade)
*/
//difficoltà: creare nuovi muri e far scorrere la mappa al posto dell'uccellino. per saltare basta fare riferimento al concetto di direzione

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

#define X 20
#define Y 15

void initmatrix(int matrix[][X]);							//crea i bordi del campo
void printmatrix(int matrix[][X]);							//stampa il campo e tutto quello che c'è dentro
void reinitmatrix(int matrix[][X], int wall1[][2], int bird[]);	//aggiorna la matrice
int CommandIn();										//riceve il comando di saltare dall'utente
int RcrdExperiment(int score);							//funzione sperimentale, salva il miglior punteggio in record.txt
void zeromatrix(int wall[][2]);							//azzera i valori del muro
void createWall(int wall[][2]);							//crea il muro e tunnel 
void moveWall(int wall[][2]);								//sposta il muro verso sinistra
bool Loose(int wall1[][2], int ball[]);						//ritorna vero se si perde
void MoveBird(int bird[]);								//permette all'uccello di saltare verso l'alto
void Gravity(int bird[]);								//fa cadere l'uccello

//INTERFACCE GRAFICHE
void FlappyBird();										//iniziale
void gameOver(int score, int record);						//finale

int main(){
	srand(time(0));
	while(true){
		int matrix[Y][X];			//campo di gioco
		int bird[2] = {X/3, Y/2};	//0=x, 1=y	//coordinate uccello
		int wall1[Y-1][2];			//0=x, 1=y	//coordiante muro 
		int loose=false;			//se vero termina la partita
		int score=0;				//punteggio
		int cmd=' ';				//comando utente
		int fase_salto;			//permette un innalzamento progressivo dell'uccello
		
		initmatrix(matrix);	//creo i bordi del campo
		zeromatrix(wall1);	//azzero tutti i valori del muro, per permetterne lea creazione in seguito
		
		FlappyBird();		//stampo l'interfaccia iniziale
		
		while(!loose){
			if(wall1[0][0]<=0){		//creo il nuovo muro se necessario
				createWall(wall1);
			}
			
			reinitmatrix(matrix, wall1, bird);		//aggiorna i valori
			printmatrix(matrix);				//stampa il campo e cancella la versione precedente
			printf("\n\n\tSCORE: %d", score);		
			Sleep(10);						//mette in pausa il programma per x millisecondi

			cmd=CommandIn();					//prende il comando dell'utente o lo azzera
			
			if(cmd!=0){						//inizia il salto
				fase_salto=4;				
			}
			
			if(fase_salto!=0){					//salta gradualmente
				MoveBird(bird);
				fase_salto--;
			}
			
			Gravity(bird);						//fa cadere l'uccello
			
			moveWall(wall1);					//sposta il muro
			//INCREMETO IL PUNTEGGIO SE NECESSARIO
			if(wall1[0][0]+1 == bird[0] || wall1[0][0]+2 == bird[0]){	//per impedire che in qualche dimensione di X non venga contato il punteggio
				score++;
			}
			//CONTROLLO SE SI HA PERSO
			loose=Loose(wall1, bird);
		}
		
		int record = RcrdExperiment(score);	//PARTE SPERIMENTALE SUL SALVATAGGIO DEL MIGLIOR PUNTEGGIO IN UN FILE record.txt
		
		gameOver(score, record);
	}
}

int RcrdExperiment(int score){
	//PARTE SPERIMENTALE SUL SALVATAGGIO DEL MIGLIOR PUNTEGGIO IN UN FILE record.txt
	int record;
	FILE *filereader = fopen("FLAPPYBIRDrecord.txt", "r");
	
	fscanf(filereader, "%d", &record);	//prendo il valore contenuto in record.txt e lo registro in record
	
	if(score > record){
		FILE *filewriter = fopen("FLAPPYBIRDrecord.txt", "w");	//quando apre il file, cancella quello che c'è dentro
		
		fprintf(filewriter, "%d", score);	//scrivo nel file il valore di score
		record = score;
		
		fclose(filewriter);
	}
	
	fclose(filereader);//come di regola chiudo le due copie del file aperte
	
	return record;
	//FINE PARTE SPERIMENTALE
}

void createWall(int wall[][2]){
	zeromatrix(wall);			//azzero tutti i valori
	
	for(int i=0; i<Y-1; i++){	//lo posiziono in fondo al campo (destra)
		wall[i][0] = X-1;
	}
	
	int inizio_tunnel = (rand() % (Y-2-6)) + 2;	//stabilisco dove inizia il tunnel
	
	int i=0;
	while(i<inizio_tunnel){	//creo il muro dino all'inizio del tunnel
		wall[i][1] = i;
		i++;
	}		
	i+=3;				//non creo nulla dove c'è il tunnel
	while(i<Y-1){			//riprendo a creare il muro
		wall[i][1] = i;
		i++;
	}	
}

void moveWall(int wall[][2]){	//sposta il muro verso sx
	for(int i=0; i<Y-1; i++){
		wall[i][0]-=2;
	}
}

void MoveBird(int bird[]){	//aumenta la quota dell'uccello
	bird[1]-=2;
}

void Gravity(int bird[]){	//diminuisce la quota dell'uccello
	bird[1]+=1;
}

void initmatrix(int matrix[][X]){	//creo i bordi del campo
	for(int i=0; i<Y; i++){
		for(int j=0; j<X; j++){
 			matrix[i][j]=' ';

			if(j==0 || j==X-1 || i==0 || i==Y-1){
	   		     matrix[i][j]='|';//tanti puntini vicini
			}
		}
	}
}

void printmatrix(int matrix[][X]){	//stampo il campo
	system("cls");									//cancella tutto ciò che era presente in precedenza

	for(int i=0; i<Y; i++){
		printf("\n\t");
		
		for(int j=0; j<X; j++){
			printf("%c",matrix[i][j]);
		}
	}
}

bool Loose(int wall1[][2], int bird[]){	//controllo se ho perso
	if(bird[1]>Y-2 || bird[1]<1){			//controllo se ho toccato terra o il soffitto, se sì perdo
		return true;
	}
	
	for(int i=0; i<Y-2; i++){
		if(wall1[i][1] == bird[1] && wall1[i][0] == bird[0]){		//controllo se ho toccato il muro
			return true;
		}
		if(wall1[i][1] == bird[1] && wall1[i][0]+1 == bird[0]){//+1 perche il muro si muove di 2 quindi a seconda di X potrebbe non passare mai per bird[0]
			return true;
		}
	}
	
	return false;
}

void reinitmatrix(int matrix[][X], int wall1[][2], int bird[]){	//aggiorna la matrice
	for(int i=1; i<Y-1; i++){
		for(int j=1; j<X-1; j++){
			for(int k=1; k<Y; k++){
				if(wall1[k-1][1] == i && wall1[k-1][0] == j){
					matrix[i][j]='$';	//'$' è un valore provvisorio, che viene cambiato nel ciclo for successivo
				}
			}
		}
	}
	
	for(int i=1; i<Y-1; i++){
		for(int j=1; j<X-1; j++){
			if(matrix[i][j] == '$'){
				matrix[i][j]='#';
			}else if(bird[1] == i && bird[0] == j){
				matrix[i][j]='@';
			}else{
				matrix[i][j]=' ';
			}
		}
	}
}

void zeromatrix(int wall[][2]){			//azzera i valori di una matrice
	for(int i=0; i<Y-1; i++){
		for(int j=0; j<2; j++){
			wall[i][j]=0;
		}
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

void FlappyBird(){
	system("color bf");
	system("cls");
	printf("\t _____ _        _    _____ _____ _  _ \n");
	printf("\t|  ___| |      / \\  |     |     | \\/ /\n");
	printf("\t|  __|| |     /   \\ |  O  |  O  |\\  / \n");
	printf("\t| |   | |___ / ___ \\| ,---| ,---'/ /  \n");
	printf("\t|_|   |_____|_/   \\_|_|   |_|   /_/   \n");
	printf("\t\t _____  _ _____  ____\n");
	printf("\t\t|     || |     \\|  _ \\\n");
	printf("\t\t|  O  /| |   __/| | | |\n");
	printf("\t\t|  O  \\| | |\\ \\ | |_| |\n");
	printf("\t\t|_____||_|_| \\_\\|____/\n\n\t");
	system("pause");
}

void gameOver(int score, int record){
	system("cls");
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