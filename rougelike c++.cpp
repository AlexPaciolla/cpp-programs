/*
	Name: rougelike c++

	Copyright: none

	Author: Alex Paciolla

	Description: videogioco di tipo rougelike, programmato seguendo parzialmente i tutorial
				del prof. Andrea Polini (video su Youtube).
				Link al primo video della serie:
					https://www.youtube.com/watch?v=0OR-p3l_ipQ
*/

/*****************************************************************************************************************************/

#include <iostream>

using namespace std;


//larghezza e lunghezza della mappa del gioco
constexpr auto W=50;
constexpr auto H=30;

char map[W][H];


//inizializzazione mappa
void init_map(){
	for(auto y=0; y<H; y++) {
		for(auto x=0; x<W; x++) {
			map[y][x]='.';
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


//comand prompt
char comand_prompt(){
	char cmd;
	cout<<endl<<"> ";
	cin>>cmd;

	return cmd;
}


/*****************************************************************************************************************************/


//Ready Player 1
//(game)
int main (){

	//dichiarazione di entità, e variabili
	entity ghost{40,20,'#'};
	entity hero{2,20,'@'};

	entity wall1{0,0,'|'};
	entity wall2{0,0,'-'};


	int score=0;
	int tries=3;

	bool running = true;



	//limitazione del movimento all'interno dei muri
	//NON FUNZIONA
	clamp(hero.x, wall1.x-1, wall1.x+1);
	clamp(hero.y, wall2.y-1, wall2.y+1);


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
				//stampa dei muri orizzontali
				if((wall2.x==30||wall2.x==15&&y==15))
				{
					cout<<wall2.glyph;
				}
				else if(hero.x == x && hero.y == y)
				{
					cout<<hero.glyph;
				}
				else if (ghost.x == x && ghost.y == y)
				{
					cout<<ghost.glyph;
				}
				else
					cout<<map[y][x];
			}
			cout<<endl;
		}


		//output delle statistiche di gioco temporanee attuali
		cout<<"Score:"<<score;
		cout<<"     Tentativi rimasti:"<<tries<<"\n";


		//comandi
		char cmd=comand_prompt();


		switch(cmd){
			case 'd':
			case 'D':
				hero.move(+1, 0);//muove l'eroe
				break;

			case 'a':
			case 'A':
				hero.move(-1, 0);//muove l'eroe
				break;

			case 'w':
			case 'W':
				hero.move(0, -1);//muove l'eroe
				break;

			case 's':
			case 'S':
				hero.move(0, +1);//muove l'eroe
				break;


			case 'q'://comando di abbadono della partita
			case 'Q':
				system("cls");

				char quitYN;

				cout<<"\n\n\nAre you sure you want to quit?[y/n]";//richiesta di conferma
				cin>>quitYN;

				switch(quitYN)
				{
					case 'y':
						running=false;
						break;

					case 'q':
						running=false;
						break;
				}

				break;
		}


		//muove automaticamente l'entità "ghost"
		if(hero.x>ghost.x)
			{
				ghost.move(+1,0);
			}
		else if(hero.x<ghost.x)
			{
				ghost.move(-1,0);
			}
		else if(hero.y<ghost.y)
			{
				ghost.move(0,-1);
			}
		else if(hero.y>ghost.y)
			{
				ghost.move(0,+1);
			}


		//da usare se "ghost" è cattivo
		if((hero.x==ghost.x)&&(hero.y==ghost.y))
		{
			if(tries>0)
			{
				hero.x=W/2;
				hero.y=H/2;

				tries=tries-1;
			}
			else
			{
				running=false;
			}
		}
	}


	system("cls");

	cout<<"|-------|      /|      ||    /|  |-------|\n";
	cout<<"|             /  |     | |  / |  |        \n";
	cout<<"|    ____    /----|    |  |/  |  |-----|  \n";
	cout<<"|       |   /      |   |      |  |        \n";
	cout<<"|-------|  /        |  |      |  |-------|\n";
	cout<<"\n";
	cout<<"\n";
	cout<<"|-------|  |        /  |-------|  |-------|\n";
	cout<<"|       |   |      /   |          |       |\n";
	cout<<"|       |    |    /    |-----|    |_______|\n";
	cout<<"|       |     |  /     |          |    |__ \n";
	cout<<"|_______|      |/      |-------|  |       |\n";
	cout<<"\n";
	cout<<"\n";
	cout<<"\n";
	cout<<"            YOUR SCORE WAS: "<<score<<"\n\n";

	return 0;
}


/*
TO DO:

	bisogna creare una clamp efficace per i muri

		bisogna trovare un modo più efficace per disegnare la mappa

			creare il gioco

*/

/*
BUGS:
*/