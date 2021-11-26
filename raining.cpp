/*
	Name: raining
	Copyright: none
	Author: Alex Paciolla, prendendo la base del codice dal precedente programma "rougelike c++.cpp"
	Date: 26/11/21 19:55
	Description: Esperimento sulla funzione Sleep() e sulla stampa di matrici quadratiche (rimasta attualmente incompresa)
*/


#include <iostream>
#include <windows.h>
#include <winable.h>

using namespace std;


//larghezza e lunghezza della mappa del gioco
constexpr auto W=30;
constexpr auto H=20;

char map[W][H];


//inizializzazione mappa
void init_map(){
	for(auto y=0; y<H; y++) {
		for(auto x=0; x<W; x++) {
			map[y][x]=' ';
		}
	}
}


//limitare la mobilità del personaggio all'interno dello schermo
void clamp(int& value, int min_value, int max_value){
	if (value <= min_value){
		value = min_value;
		return;
	}
	if (value >= max_value){
		value = max_value;
		return;
	}
}


//dichiaro la struttura delle entità
struct entity {

	int x;
	int y;
	char glyph;

	//funzione di movimento
	void move(int dx, int dy){
		x += dx;
		y += dy;
		clamp(x, 0, W-1);
		clamp(y, 0, H-1);
	}
};


/*****************************************************************************************************************************/


//Ready Player 1
//(game)
int main (){
	entity a{2,4,'@'};
	entity b{10,15,'#'};

	bool running = true;


	//fase di gioco
	while(running==true){

		//pulisco schermo
		system("cls");

		//inizializzo mappa
		init_map();


		//stampare mappa con entità
		for(auto y=0; y<H; y++)
		{
			for(auto x=0; x<W; x++)
			{
				if(a.x == x && a.y == y)
				{
					cout<<a.glyph;
				}
				else if(b.x == x && b.y == y)
				{
					cout<<b.glyph;
				}
				else
					cout<<map[y][x];
			}
			cout<<endl;
		}

		b.y++;
		b.x++;

		if(b.y==(H-1)){
			b.y=0;
		}

		if(b.x==(W-1)){
			b.x=0;
		}


		a.y++;
		a.x++;

		if(a.y==(H-1)){
			a.y=0;
		}

		if(a.x==(W-1)){
			a.x=0;
		}

		Sleep(100);
	}



	return 0;
}
