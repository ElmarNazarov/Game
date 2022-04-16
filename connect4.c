///////////////////
// Elmar Nazarov // 
///////////////////
#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include <stdlib.h>
void PrintMap(char map[6][8]);
int adding(char map[6][8], int index, char player);
void rem(char map[6][8],int index);
int winner(char map[6][8]);
int player1(char map[6][8]);
int player2(char map[6][8],int L[7]);
bool colcheker(char map[6][8],int u);
int F(char map[6][8], int L[7]);
int computer(char map[6][8], int L[7]);
void main()
{   
	srand(time(NULL));   
	int L[7];
    char t;
	char map[6][8]= {{"       "},
	                 {"       "},
					 {"       "},
					 {"       "},
					 {"       "},
					 {"       "}};
	PrintMap(map);
	printf("Do you want play with computer(Y/n): ");
	scanf("%c",&t);
	if (t == 'Y'||t == 'y')
	{
		while (true)
		{
			if (player1(map)){
                break;
            }
			computer(map,L);
            PrintMap(map);
			if (winner(map)){
                printf("Winner is yellow\n");
                break;
            }
		}	
	}	
	else{
		while(true){
			if (player1(map)){
				break;
			}
			if (player2(map,L)){
				break;
			}
		}
	}
}
void PrintMap(char map[6][8])
{
    printf("  1 2 3 4 5 6 7  \n");
    for (int i = 0; i < 6; i++){
        printf("%i ",i+1);
        for (int k = 0; k < 7; k++){
            printf("%c ",map[i][k]);
        }   
        printf("%i \n",i+1);
    } 
    printf("  1 2 3 4 5 6 7  \n");
}
int adding(char map[6][8], int index, char player){
	for(int i = 5; i >= 0; i--){
		if(map[i][index-1] == ' '){
            map[i][index-1] = player;
            break;
        }
	}
}

void rem(char map[6][8],int index){
    for(int i = 0; i < 6; i++){
        if(map[i][index-1] != ' '){
            map[i][index-1] = ' ';
            break;
        }
    }
}

int winner(char map[6][8]){
    // Horizontal
    for (int i=0;i<6;i++){
        for(int j = 0;j<4;j++){
            if (map[i][j]==' '){
                continue;
            }
            for (int k=1;k<4;k++){
                if (map[i][j]!=map[i][j+k]){
                    break;
                }
                else if (k == 3){
                    return true;
                }                       
            }                    
        }
    }
    // Vertical
    for (int i=0;i<3;i++){
        for (int j=0;j<7;j++){
            if (map[i][j]==' '){
                continue;
            }
            for (int k=1;k<4;k++){
                if (map[i][j]!=map[i+k][j]){
                    break;
                }
                else if (k == 3){
                    return true;
                }
            }      
        }
    }
    // Diagonal 1
    for(int i=0;i<3;i++)
    {
        for (int j=3;j<7;j++){
            if (map[i][j]==' '){
                continue;
            }
            for (int k=1;k<4;k++){
                if (map[i][j]!=map[i+k][j-k]){
                    break;
                }
                else if (k == 3){
                    return true;
                }
            }
        }
    }
    // Diagonal 2
    for(int i=0;i<3;i++){
        for (int j=0;j<4;j++){
            if (map[i][j]==' '){
                continue;
            }
            for(int k=1;k<4;k++){
                if (map[i][j]!=map[i+k][j+k]){
                    break;
                }
                else if (k == 3){
                    return true;
                }
            }
        }
    }
    return false;
}
int player1(char map[6][8]){
	int col;
	printf("Write the column number: ");
	scanf("%i",&col);
    if (colcheker(map,col)){
        adding(map,col,'*');
        PrintMap(map);
        if (winner(map)){
            printf("Winner is red\n");
            return true;
        }  
    }
    else{
        printf("Chosen colomn is full, try again\n");
        player1(map);
    }
}
int player2(char map[6][8],int L[7]){
    int c=0;
    int col;
	F(map,L);
    for (int u = 0; u < 7; u++){
        if (L[u] < 0 || L[u] > 7){
            continue;
        }
        else{
            adding(map,u+1,'o');
            if (winner(map)){
                rem(map,u+1);
                printf("You will win if you will write %d \n",u+1);
                printf("Write the column number: ");
                scanf("%i",&col);
                if (colcheker(map,col)){
                    adding(map,col,'o');
                    PrintMap(map);
                    c=c+1;
                    if (winner(map)){
                            printf("Winner is yellow\n");
                            return true;
                        }
                }
                else{
                    printf("Try again\n");
                    player2(map,L);
                }
            }
            else if (!winner(map)){
                rem(map,u+1);
                adding(map,u+1,'*');
                if (!winner(map)){
                    rem(map,u+1);
                }
                else{
                    rem(map,u+1);
                    printf("You will not lose if you will write %d\n",u+1);
                    printf("Write the column number: ");
                    scanf("%i",&col);
                    if (colcheker(map,col)){
                        adding(map,col,'o');
                        PrintMap(map);
                        c=c+1;
                        if (winner(map)){
                                printf("Winner is yellow\n");
                                return true;
                            }
                    }
                    else{
                        printf("Try again\n");
                        player2(map,L);
                    }
                }
            }
            else{
                printf("Write the column number: ");
                scanf("%i",&col);
                if (colcheker(map,col)){
                    adding(map,col,'o');
                    PrintMap(map);
                    c=c+1;
                    if (winner(map)){
                            printf("Winner is yellow\n");
                            return true;
                        }
                }
                else{
                    printf("Try again\n");
                    player2(map,L);
                }
            }       
        }    
    }
        if (c==0){
                printf("Write your column number: ");
                scanf("%i",&col);
                if (colcheker(map,col)){
                    adding(map,col,'o');
                    PrintMap(map);
                }
                else{
                    printf("Try again\n");
                    player2(map,L);
                }
        }
        else if(c!=0){
                c-=1;
                return c;
        }
	if (winner(map)){
		printf("Winner is yellow\n");
		return true;
	}
}
bool colcheker(char map[6][8],int u){
    bool colchek = false;   
    for (int i = 0; i < 6; i++){
        if (map[i][u-1] == ' '){
            colchek = true;
        }     
    }
    return colchek;
}
int F(char map[6][8], int L[7]){
    int c;
    for (int u = 0; u < 7; u++){
        int U1[6];
        for (int row = 0; row < 6; row++){
            if (map[row][u] == ' '){
                L[u]=u+1;
                break;
            }
            else{
                L[u]=12;
            }
        }
    }

}
int computer(char map[6][8], int L[7]){
	F(map,L);
    for (int u = 0; u < 7; u++){
        if (L[u] < 0 || L[u] > 7){
            continue;
        }
        else{
            adding(map,u+1,'o');
            if (!winner(map)){
                rem(map,u+1);
                adding(map,u+1,'*');
                if (!winner(map)){
                        rem(map,u+1);
                }
                else{
                    rem(map,u+1);
                    adding(map,u+1,'o');
                    return 0;
                }
                }
            else{
                return 0;
            } 
        }
    }
    adding(map, (rand()%7)+1,'o');
}