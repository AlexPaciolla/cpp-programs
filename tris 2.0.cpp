#include <stdlib.h>
#include <stdio.h>

struct casella
{
	int x;
	int y;
	char symbol;
};

int main(){
	char tris[3][3];
	int x,y;
	char symbol='O';

	casella qualsiasi{h,w,symbol};

	for(int y=0; y<3; y++){
		for(int x=0; x<3; x++){
			tris[x][y]='#';
		}
	}


	for(int y=0; y<3; y++){
		for(int x=0; x<3; x++){
			printf("%c",tris[x][y]);
		}
		printf("\n");
	}
}
