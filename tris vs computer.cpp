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
	char usr;
	char cmp;

	do
	{
		printf("Vuoi giocare come giocatore X o come giocatore O? ");
		scanf(" %c",&symbol);

		if(symbol!='X'&&symbol!='O'){
			printf("Il simbolo puo' essere solo X oppure O");
		}
	}
	while(symbol!='X'&&symbol!='O');


	do
	{
		if(symbol=='O')
		{
			cmp=
		}
	}
}
