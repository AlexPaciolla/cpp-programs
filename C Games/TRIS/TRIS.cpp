/*
	Name: TRIS
	Copyright: none
	Author: Alex Paciolla
	Date: 15/02/22
	Description: versione definitiva di tris, che in passato era stato creato in modo eccessivamente complesso
*/

//NB: la modalità MEDIUM non è imbattibile e risulta spesso vulnerabile, ma è ciò che si voleva fare

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

void Interfaccia(int c[]);			//interfaccia grafica
void azzera(int c[], int D);			//tutti i valori di c diventano ' '
int chooseMode();					//permette l'inserimento della modalità di gioco
void symbols(int *p1, int *p2);		//stabilisce chi inizia
void getcasusr(int p, int c[]);		//riceve la casella dall'utente
void getcascmp1(int p, int c[]);		//compila casualmente una casella	//utilizzato principalmente in mode 2
void getcascmp2(int p, int c[]);		//calcola che casella compilare	//utilizzato principalmente in mode 3
int getcascmp2_vittoria(int p, int c[]);	//controlla se si può vincere e nel caso vince
int getcascmp2_salvataggio(int p, int c[]);	//prova a non perdere
int checkEnd(int c[]);				//controlla se e come è finita la partita

//FINALI
void End(char win, int c[]);		//indica che interfaccia finale mostrare
void Xwin(int c[]);
void Owin(int c[]);
void NOwin(int c[]);

int main(){
	srand(time(0));
	
	while(true){
		int win = 0;		//se !=0 termina la partita con un vincitore
		const int D = 9;	//num caselle
		int c[D];			//caselle
		int mode;			//modalità di gioco
		int p1, p2;		//simboli dei giocatori	//se contro il computer p1 è sempre l'utente
		
		azzera(c, D);
		mode=chooseMode();
		symbols(&p1, &p2);
		
		while(win == 0){
			system("cls");
			Interfaccia(c);
			
			if(p1 == 'X'){
				getcasusr(p1, c);			//prende l'input dall'utente
				
				win=checkEnd(c);
				
				if(win==0){
					Interfaccia(c);
					if(mode == 1){				//prende l'input dall'utente 2
						getcasusr(p2, c);//ricevi casella utente
					}else if(mode == 2){		//compila una casella casuale
						getcascmp1(p2, c);//ricevi casella computer (modo 1)
					}else if(mode == 3){		//calcola quale casella compilare
						getcascmp2(p2, c);//ricevi casella computer (modo 2)
					}				
				}
			}else if(p2 == 'X'){
				if(mode == 1){
					getcasusr(p2, c);
				}else if(mode == 2){
					getcascmp1(p2, c);
				}else if(mode == 3){
					getcascmp2(p2, c);
				}
						
				win=checkEnd(c);
				
				if(win==0){
					Interfaccia(c);
					getcasusr(p1, c);				
				}	
			}
			
			win=checkEnd(c);
		}
		
		End(win, c);
	}
}

void End(char win, int c[]){
	if(win=='X'){
		Xwin(c);
	}else if(win=='O'){
		Owin(c);
	}else if(win==1){
		NOwin(c);
	}	
}

int checkEnd(int c[]){
	for(int i=1; i<8; i+=3){				//righe
		if(c[i]==c[i+1] && c[i]==c[i-1] && c[i]!=' '){
			return c[i];
		}
	}
	
	for(int i=3; i<6; i++){				//colonne
		if(c[i]==c[i+3] && c[i]==c[i-3] && c[i]!=' '){
			return c[i];
		}		
	}
	
	for(int i=0; i<3; i+=2){				//diagonali
		if(c[4]==c[0+i] && c[4]==c[8-i] && c[i]!=' '){
			return c[4];
		}
	}
	
	for(int i=0; i<9; i++){
		if(c[i]==' '){
			return 0;
		}
	}
	
	return 1;	//finisce la partita
}

void getcascmp1(int p, int c[]){
	int cmp = -1;
	bool compilation=false;
	
	while(cmp<0 || compilation==false){
		cmp = rand() % 9;
		
		if(c[cmp] == ' '){
			c[cmp] = p;
			compilation=true;
		}
	}
}

void getcascmp2(int p, int c[]){
	int spazivuoti=0;
	for(int i=0; i<9; i++){	//calcola a che turno è la partita
		if(c[i] == ' '){
			spazivuoti++;
		}
	}
	
	if(spazivuoti==9){
		c[((rand()%4)+1)*2] = p; 			//1) p=='X' al primo turno tenta di posizionarsi in caselle pari (quindi angoli eccetto c[0] e centro)

	}else if(spazivuoti==8 && c[4] == ' '){
		c[4] = p;							//2) p=='O' al primo turno tenta di posizionarsi al centro
		
	}else if(getcascmp2_vittoria(p, c)==0){		//3) prova a vincere
	
		if(getcascmp2_salvataggio(p, c)==0){	//4) impedisce all'avversario di vincere
		
			getcascmp1(p, c);				//5)dopo aver considerato tutte le alternative migliori compilo casualmente
		}
	}
}

int getcascmp2_salvataggio(int p, int c[]){	//prova a non perdere
	int flag=0;
	for(int i=1; i<9 && flag==0; i+=3){	//righe
		if(c[i]==c[i-1] && c[i+1]==' ' && c[i] != p && c[i] != ' '){
			c[i+1]=p;
			flag=1;
		}else if(c[i+1]==c[i] && c[i-1]==' ' && c[i] != p && c[i] != ' '){
			c[i-1]=p;
			flag=1;
		}else if(c[i+1]==c[i-1] && c[i]==' ' && c[i+1] != p && c[i+1] != ' '){
			c[i]=p;
			flag=1;
		}
	}
	
	for(int i=3; i<6 && flag==0; i+=1){	//colonne
		if(c[i]==c[i-3] && c[i+3]==' ' && c[i] != p && c[i] != ' '){
			c[i+3]=p;
			flag=1;
		}else if(c[i+3]==c[i] && c[i-3]==' ' && c[i] != p && c[i] != ' '){
			c[i-3]=p;
			flag=1;
		}else if(c[i+3]==c[i-3] && c[i]==' ' && c[i+3] != p && c[i+3] != ' '){
			c[i]=p;
			flag=1;
		}
	}
	
	for(int i=0; i<3 && flag==0; i+=2){	//diagonali
		if(c[4]==c[0+i] && c[8-i]==' ' && c[4] != p && c[4] != ' '){
			c[8-i]=p;
			flag=1;
		}else if(c[8-i]==c[4] && c[0+i]==' ' && c[4] != p && c[4] != ' '){
			c[0+i]=p;
			flag=1;
		}else if(c[8-i]==c[0+i] && c[4]==' ' && c[0+i] != p && c[0+i] != ' '){
			c[4]=p;
			flag=1;
		}
	}
	
	return flag;	
}

int getcascmp2_vittoria(int p, int c[]){	//controlla se si può vincere e nel caso vince
	int flag=0;
	for(int i=1; i<9 && flag==0; i+=3){	//righe
		if(c[i]==c[i-1] && c[i]==p && c[i+1]==' '){
			c[i+1]=p;
			flag=1;
		}else if(c[i+1]==c[i] && c[i]==p && c[i-1]==' '){
			c[i-1]=p;
			flag=1;
		}else if(c[i+1]==c[i-1] && c[i+1]==p && c[i]==' '){
			c[i]=p;
			flag=1;
		}
	}
	
	for(int i=3; i<6 && flag==0; i+=1){	//colonne
		if(c[i]==c[i-3] && c[i]==p && c[i+3]==' '){
			c[i+3]=p;
			flag=1;
		}else if(c[i+3]==c[i] && c[i]==p && c[i-3]==' '){
			c[i-3]=p;
			flag=1;
		}else if(c[i+3]==c[i-3] && c[i+3]==p && c[i]==' '){
			c[i]=p;
			flag=1;
		}
	}
	
	for(int i=0; i<3 && flag==0; i+=2){	//diagonali
		if(c[4]==c[0+i] && c[4]==p && c[8-i]==' '){
			c[8-i]=p;
			flag=1;
		}else if(c[8-i]==c[4] && c[4]==p && c[0+i]==' '){
			c[0+i]=p;
			flag=1;
		}else if(c[8-i]==c[0+i] && c[8-i]==p && c[4]==' '){
			c[4]=p;
			flag=1;
		}
	}
	
	return flag;
}

void getcasusr(int p, int c[]){	//p sta per player
	char usr;
	bool compilation=false;
	
	do{
		printf("\n\tInserisci una casella [%c]: ", p);
		usr=getch();
		printf("%c", usr);
		
		if(usr>'9' || usr<'1' || c[usr-'1']!=' '){
			printf("\n\n\tCASELLA NON VALIDA\n");
		}else{
			c[usr-'1'] = p;
			compilation=true;
		}
	}while(usr>'9' || usr<'1' || compilation==false);
}

void symbols(int *p1, int *p2){
	if(rand() % 2 == 0){
		*p1='X';
		*p2='O';
	}else{
		*p1='O';
		*p2='X';
	}	
}

int chooseMode(){
	char usr;
	
	system("cls");
	printf("\t _______   ______   _   ______\n");
	printf("\t|__   __| |  __  | | | |  ____|\n");
	printf("\t   | |    | |__| | | | | |____\n");
	printf("\t   | |    |  _  _| | | |____  |\n");
	printf("\t   | |    | | | |  | |  ____| |\n");
	printf("\t   |_|    |_|  |_| |_| |______|\n");
	printf("\n\n\t");
	printf("\tMODES:\n");
	printf("\t1\tPlayer vs Player\n");
	printf("\t2\tPlayer vs Computer // EASY\n");
	printf("\t3\tPlayer vs Computer // MEDIUM\n");
	
	do
     {
     	printf("\n\tSeleziona la modalita': ");
     	usr = getch();
		printf("%c", usr);
          
     	if(usr<'1' || usr>'3')
     	{
			printf("\n\tMODALITA' INESISTENTE");
     	}
     }while(usr<'1' || usr>'3');
     
     return usr-'1'+1;	//converto char nel suo valore int
}

void azzera(int c[], int D){
	for(int i=0; i<D; i++){
		c[i]=' ';	//spazio, non 0
	}
}

void Interfaccia(int c[]){
	system("cls");
	printf("\t _______   ______   _   ______\n");
	printf("\t|__   __| |  __  | | | |  ____|\n");
	printf("\t   | |    | |__| | | | | |____\n");
	printf("\t   | |    |  _  _| | | |____  |\n");
	printf("\t   | |    | | | |  | |  ____| |\n");
	printf("\t   |_|    |_|  |_| |_| |______|\n");
	printf("\n\n");
	printf("\t 1 | 2 | 3 \n");//stampa di una mappa campione
	printf("\t-----------\n");
	printf("\t 4 | 5 | 6 \n");
	printf("\t-----------\n");
	printf("\t 7 | 8 | 9 \n");
	printf("\n");	
	printf("\t %c | %c | %c \n", c[0], c[1], c[2]);
	printf("\t-----------\n");
	printf("\t %c | %c | %c \n", c[3], c[4], c[5]);
	printf("\t-----------\n");
	printf("\t %c | %c | %c \n", c[6], c[7], c[8]);
	printf("\n");
}

void Xwin(int c[]){
	Interfaccia(c);
	printf("\t _  _  _    _ _ __    _ ____ \n");
	printf("\t\\ \\/ /| |  | | |  \\  | |  __|\n");
	printf("\t \\  / | |  | | |   \\ | | |__ \n");
	printf("\t /  \\ | \\/\\/ | | |\\ \\| |___ |\n");
	printf("\t/_/\\_\\ \\_/\\_/|_|_| \\___|____|\n\n\t");
	system("pause");
}
void Owin(int c[]){
	Interfaccia(c);
	printf("\t _______  _    _ _ __    _ ____ \n");
	printf("\t|  ___  || |  | | |  \\  | |  __|\n");
	printf("\t| |   | || |  | | |   \\ | | |__ \n");
	printf("\t| |___| || \\/\\/ | | |\\ \\| |___ |\n");
	printf("\t|_______| \\_/\\_/|_|_| \\___|____|\n\n\t");
	system("pause");
}
void NOwin(int c[]){
	Interfaccia(c);
	printf("\t ____  _____    _   _    _\n");
	printf("\t|  _ \\|     \\  / \\ | |  | |\n");
	printf("\t| | | |   __/ /   \\| |  | |\n");
	printf("\t| |_| | |\\ \\ / ___ | \\/\\/ | \n");
	printf("\t|____/|_| \\_/_/   \\_\\_/\\_/ \n\n\t");
	system("pause");
}