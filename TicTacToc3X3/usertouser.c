#include <stdio.h>
#include <stdlib.h>

char board[3][3] = {
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'}
};

void drawboard() {
	for (int i = 0; i<3; i++){
		printf("%c|%c|%c\n",board[i][0], board[i][1], board[i][2]);
		if (i != 2){
			printf("---|---|---\n");
		}
	}
}

int checkwin(){
	//Rows
          for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return 1;
        }
    } 
