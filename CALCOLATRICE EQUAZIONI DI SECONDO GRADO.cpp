/*
	Name:la sfida
	Copyright: none
	Author: Alex Paciolla
	Date: 27/09/22
	Description:
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>		//false, true
#include <math.h>			//sqrt(), pow()
void mostraMenu();						//stampa il menu
int Scelta();							//permette l'inserimento della scelta (con controllo dell'input)
void leggiCoeff(float coeff[], int D);	//legge i coefficienti a, b e c 
float calcolaDet(float coeff[], int D);	//se non sono ancora inseriti i coefficienti chiama la funzione per calcolarli, poi calcola, stampa e ritorna il determinante
void calcolaSol(float coeff[], int D);	//chiama la funzione per calcolare il determinante poi calcola le soluzioni e le stampa
void StampaEq(float coeff[], int D);	//stampa l'equazione di secondo grado con i suoi coefficienti



int main(){
	int flag=true;			//inizializzo una flag per terminare il programma
	const int D=3;			//la dimmensione è tre, come i coefficienti dell'equazione
	float coeff[D]={0,0,0};	//inizializzo un vettore in cui inserire i coefficienti azzerando tutti i valori
	
	mostraMenu();
	
	do{	
		int scelta=Scelta();
		
		switch(scelta){		//in base alla scelta esegue una funzione diversa
			case 1:
				leggiCoeff(coeff, D);
				break;
			case 2:
				calcolaDet(coeff, D);
				break;
			case 3:
				calcolaSol(coeff, D);
				break;
			case 4:
				coeff[0]=0; coeff[1]=0; coeff[2]=0; 
				calcolaSol(coeff, D);
				break;
			default:
				flag=false;
		}
	}while(flag=true);		//se si inserisce 5 il programma termina
}


void mostraMenu(){						//stampa il menu
	printf("*****************************************\n");
	printf("*   RISOLUZIONE EUQUAZIONI DI 2^GRADO   *\n");
	printf("*****************************************\n");
	printf("\n");
	printf("*****************************************\n");
	printf("*       Menu' utente principale         *\n");
	printf("*****************************************\n");
	printf("* 1 ACQUISIZIONE DEI COEFFICIENTI       *\n");
	printf("* 2 CALCOLO DEL DETERMINANTE            *\n");
	printf("* 3 CALCOLO DELLE SOLUZIONI             *\n");
	printf("* 4 NUOVA EQUAZIONE                     *\n");
	printf("* 5 =======> USCITA                     *\n");
	printf("*****************************************\n");
}

int Scelta(){							//permette l'inserimento della scelta
	int usr=0;
	
	do{
		printf("\nInserire scelta (1, 2, 3, 4 oppure 5)	:");
		scanf("%d", &usr);
		
		if(usr<1 || usr>5){
			printf("Inserisci un numero compreso tra 0 e 5!\n");
		}
	}while(usr<0 || usr>5);
	
	return usr;
}

void leggiCoeff(float coeff[], int D){	//legge i coefficienti a, b e c 
	for(int i=0; i<D; i++){
		printf("Inserisci %c: ", i+97);
		scanf("%f", &coeff[i]);
	}
	
	StampaEq(coeff, D);
}

float calcolaDet(float coeff[], int D){	//se non sono ancora inseriti i coefficienti chiama la funzione per calcolarli, poi calcola e stampa il determinante
	if(coeff[0]==0 && coeff[1]==0 && coeff[2]==0){
		leggiCoeff(coeff, D);
	}
	
	float det = pow(coeff[1], 2) - 4*coeff[0]*coeff[2];
	
	printf("\n\n      DELTA = %f\n\n", det);
	
	return det;
}

void calcolaSol(float coeff[], int D){	//chiama la funzione per calcolare il determinante poi calcola le soluzioni e le stampa
	float det=calcolaDet(coeff, D);
	float sol1, sol2;
	
	if(det>=0 && coeff[0]!=0){	//se l'euqazione non è di secondo grado la risolve comunque
		sol1= (-coeff[1] + sqrt(det)) / (2*coeff[0]);
		sol2= (-coeff[1] - sqrt(det)) / (2*coeff[0]);
	
		printf("\n\n      x(1) = %f \n      x(2) = %f\n\n",sol1,sol2);
	}else if(coeff[0]==0){
		sol1=-coeff[2]/coeff[1];
		
		printf("\n\n      x(1) = %f \n", sol1);
	}else{
		printf("\n\n      L'equazione e' impossibile.\n\n");
	}
}

void StampaEq(float coeff[], int D){	//stampa l'equazione di secondo grado con i suoi coefficienti
	printf("\n\n      (%f)x^2 + (%f)x + (%f) = 0\n\n", coeff[0], coeff[1], coeff[2]);
}