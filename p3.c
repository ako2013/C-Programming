// version 1.1
// changelog
// - improved A.I

#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <string.h>

int connect_4 [7][6];
/* 
 * PRINT THE GAME BOARD AND CHECK IF FULL
 * @return 1 if board is full
 */
int printBoard(){
    int checkFull = 1;
    
    printf(" 1 2 3 4 5 6 7 \n");
    printf(" -------------\n");
    for(int i = 5; i >= 0; i--){
        for(int j = 0; j < 7; j++){
            printf(" %d",connect_4[j][i]);
            if(connect_4[j][i] == 0)
                checkFull = 0;
        }printf("\n");
    }return checkFull;
}
/*
 * CHECK WINNING MOVE
 * @num row position
 * @player 1/2
 * @col column position
 * @return 1 if it's winning move
 */
int winningCondition (int num, int player, int col){
    int check = 0;
    //check horizontally
    for(int j = 0; j < 6;j++){
        if(connect_4[num][j] == player){
            check++;
        }else
            check = 0; //reset the count
        if(check == 4)
            return 1;
    }check = 0; //reset the count for next condition
    //check vertically
    for(int j = 0; j < 7;j++){
        if(connect_4[j][col] == player){
            check++;
            if(check == 4)
                return 1;
        }else check = 0;
    }check =0; //reset the count for next condition
    //check diagonally up/down
    for(int k = 0; k < 7*2;k++){          //diagonally up
        for(int j = 0; j <= k; j++){
            int i = k-j;
            //int x = 6-i;
            if(i < 7 && j < 6){
                if(connect_4[i][j] == player){
                    check++;
                    if(check == 4) return 1;
                }else check = 0;
            }
        }check = 0; //reset the count for next condition
        for(int j = 0; j <= k; j++){     //diagonally down
            int i = k-j;
            int x = 6-i;
            if(i < 7 && j < 6){
                if(connect_4[x][j] == player){
                    check++;
                    if(check == 4) return 1;
                }else check = 0;
            }
        }check = 0;
    }return 0;
}
/*
 * SHOW PLAYER MOVES
 * @column - column chose
 * @value - player 1/2 ( input = 0/1 )
 * @return 1 if winning
 */
int insert_board(int column, int value){
    int i;
    for(i = 0; i < 6; i++){
        if(connect_4[column-1][i] == 0){
            connect_4[column-1][i] = value+1;
            return winningCondition(column-1, value+1,i);
        }
    }return 0;
}
/* 
 * PLAYER(S) MOVE
 * @player take in player number 0/1 -> 1/2
 * @return 1 for draw game/ 0 for a player won the game
 */
int player2Move(int player){
    int move;
    printf("\nPlayer %d turns to play ",player+1);
    printf("\nPlease choose a number from 1 to 7: ");
    for(;;){ //input validation
        scanf("%d", &move);
        if(move == 1 || move == 2 || move == 3 || move == 4 || move == 5 || move == 6 || move == 7){
            if(connect_4[move-1][5] == 0)  //check if the column is full
                break;
        }printf("Invalid number/Columm is full, please choose again: ");
    }
    int check = insert_board(move,player); //move = 1-7
    int checkFull = printBoard();  //check if all board is full
    if(checkFull == 1){
        printf("\n !! DRAW !! \n");
        return 1;
    }
    if(check == 1){
        printf("PLAYER %d WON\n", player+1);
        return 0;
    }return 9; // return nothing
}
/*
 * CHECK IF ANY POSSIBLE WINNING MOVE BY INSERT TEMPORARY NUMBER IN THE BOARD
 * @param value takes in player number
 * @return return the winning column or 9 for nothing
 */
int checkWinningComputer(int value)
{
    int tempInsert=0;
    int move = 9;
    for(int i = 1; i < 8; i++){
        if(connect_4[i-1][5] != 1 && connect_4[i-1][5] != 2){
            tempInsert = insert_board(i, value);
            if(tempInsert==1)move = i; //if winning condition is true, save the column
            for(int k = 5; k >= 0; k--){ //delete temp insert
                if(connect_4[i-1][k] == value+1){
                    connect_4[i-1][k] = 0;
                    break;
                }
            }
        }
    }return move;
}
/* A.I LOGICS HERE */
int next_move(){
    int move = 9;
    int check1, check2;
    
    check1= checkWinningComputer(1); // check if there's a winning move
    if(check1 != 9) return check1;
    check2= checkWinningComputer(0); // check opponent's winning moves
    if(check2 != 9) return check2;
    //opening movesets
    if(connect_4[3][0] == 0) return 4;
    else if(connect_4[3][1] == 0) return 4;
    else if(connect_4[3][2] == 0 && connect_4[3][1] == 2) return 4;
    else if(connect_4[3][1] != 0 && connect_4[4][0] == 0) return 5;
    else if(connect_4[3][2] != 0 && connect_4[5][0] == 0) return 6;
    else if(connect_4[4][0] != 0 && connect_4[5][0] == 0) return 6;
    else if(connect_4[2][0] != 0 && connect_4[1][0] == 0) return 2;
    else if(connect_4[1][1] != 0 && connect_4[0][0] == 0) return 1;
    else if(connect_4[5][0] != 0 && connect_4[6][0] == 0) return 7;
    else{
        move = rand() % 7; //random a number between 0 and 6
        //loop to re-random another number if the column is full
        while(connect_4[move][5] != 0){
            move = rand() % 7;
        }
    }return move+1; // +1 to match the input for the board e.g (1-7)
}
/* MAIN BODY */
int main()
{
    int option,count;
    for(;;){
        memset(connect_4,0,sizeof(int)*7*6);
        count = 0;
        printf("~~~~~~~~~Welcome to Connect Four Game~~~~~~~~~~~ \n\n");
        printBoard();
        printf("\nChoose an option: \n 1. Player vs. Computer \n 2. Player vs. Player \n Your Choice: ");
        for(;;){ //input validation
            scanf("%d", &option);
            if(option == 1 || option == 2) break;
            printf("Invalid number! Enter again: ");
        }
        for(;;){
            if(option == 2){
                count++;
                printf("Turn # %d \n", count);//PVP
                int check = player2Move(0);
                if(check==1 || check==0) break;
                count++;
                printf("Turn # %d \n", count);
                int check2 = player2Move(1);
                if(check2==1 || check2==0) break;
            }else{                                //PVE
                
                int move = next_move();
                int check2 = insert_board(move, 1);
                printf("\n COMPUTER'S TURN\n");
                int checkFull = printBoard();
                if(checkFull == 1){
                    printf("\n !! DRAW !! \n");
                    break;
                }
                count++;
                printf("Turn # %d \n", count);
                printf("Computer chose column %d \n",move);
                if(check2 ==1){
                    printf("COMPUTER WON\n");
                    break;
                }
                int check = player2Move(0);
                count++;
                printf("Turn # %d \n", count);
                if(check==1 || check==0) break;
            }
        }
        printf("Enter 3 to exit or any other number to play again: ");
        scanf("%d",&option);
        if(option == 3) break;
    }return 0;
}



