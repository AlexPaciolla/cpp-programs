//Primo eperimento con le librerie <chrono> e <thread>
//Parecchio interessante, da approfondire

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
	//???perchè è obbligatorio l'utilizzo dell'"using namespace std" senza la possibilità di ometterlo???

	//le due seguenti funzioni sono unioni delle funzioni incluse nelle librerie chrono e thread
    sleep_for(nanoseconds(10));						//la funzione sleep for viene da thread, la funzione nanoseconds deriva da chrono
	//												  l'utilizzo simultaneo di queste funzioni consente di attivare una diversa versione
	//												  della funzione comunemente conosciuta come Sleep(), inclusa in windows.h,
	//												  con la possibilità di utilizzare unità di misura differenti da.

    sleep_until(system_clock::now() + seconds(1));	//sarebbe interessante l'approfondimento della funzione system_clock, che è mi attualmente sconosciuta

    int a=1;

	do
	{
		a++;

		cout<<a;

		//riempie le prime 20 righe all'inizio a velocità normale, poi rallenta
		if(a>20){
			if(a%2==0)
			{
				printf("?!I MISSED THE RAGE!?\n");
				//sleep_for(milliseconds(100));
			}
			else
			{
				printf("?!I MISSED HER AGE!?\n");
				sleep_for(milliseconds(100));
			}
		}
		else
		{
			if(a%2==0)
			{
				printf("?!I MISSED THE RAGE!?\n");
			}
			else
			{
				printf("?!I MISSED HER AGE!?\n");
			}
		}

	}
	while(a<30000000000);	//si riesce a leggere un numero di tipo intero di 11 cifre (possibile?!)

}