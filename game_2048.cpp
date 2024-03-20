/* 
game_2048.cpp - made by André Tita
andre.tita217@gmail.com
*/

#include "game_2048.h"

// Auxiliar Functions

void display_board(Game &curr_game){
    cout << "+ ------------------- +\n";
    for(int row = 0; row < 4; row++){
        cout << "| ";
        for(int col = 0; col < 4; col++){
            if(curr_game.board[row][col] < 10) cout << "  " << curr_game.board[row][col] << "  ";
            
            else if(curr_game.board[row][col] < 100) cout << " " << curr_game.board[row][col] << "  ";
            
            else if(curr_game.board[row][col] < 1000) cout << " " << curr_game.board[row][col] << " ";
            
            else cout << curr_game.board[row][col] << " ";
        }
        cout << "|\n";
    }
    cout << "+ ------------------- +\n";
}

/*  + ------------------- +
    |"  4 " 48 " 048"2048"|
*/

int generate_value(){
    int value = 2;
    
    srand((unsigned) time(NULL));
    // Get a random percentage 1 to 100;
    int percentage = rand() % 100 + 1;
    
    // Percentage of the value being 4 is 12%
    if(percentage <= 12)
        value = 4;
    return value;
}

int random_piece(Game &curr_game){
    int _end = 0;
    int piece = generate_value();
    do
    {
        // Get a random position, 0 to 15
        int pos = rand() % 16;

        if(pos < 0 || pos > 15)
            return ERR;

        // Respective row and column of the position
        int row = pos / 4;
        int col = pos % 4;
        if(curr_game.board[row][col] == 0){
            _end = 1;
            curr_game.board[row][col] = piece;
        }

    } while (_end == 0);
    
    return OK;
}

void save_board(Game &curr_game){ backup.board = curr_game.board; }

void reset_game(Game &curr_game){
    curr_game.score = 0;
    for (auto& row : curr_game.board) {
        for (int& element : row) {
            element = 0;
        }
    }
}

int exit_game(Game &curr_game){
    cout << "Are you sure you want to leave ? Your progress will be lost.\n\t Yes -> E\n\t No -> Q\n";
    char key;
    while (true) {
        read(STDIN_FILENO, &key, 1);
        if (key == 'Q' || key == 'q') return OK;
        if (key == 'E' || key == 'e') return EXIT;
    }
    return EXIT;
}

int pause_game(Game &curr_game){
    cout << "\t\tPaused\n\tContinue - Q\n\tReset - R\n\tExit - E\n";
    char key;
    read(STDIN_FILENO, &key, 1);
    while (key != 'Q' || key != 'q') {
        if (key == 'R' || key == 'r') return RESET;
        if (key == 'E' || key == 'e') return EXIT;
        read(STDIN_FILENO, &key, 1);
    }
    return OK;
}

/*
Function that analyzes the board and returns:
0 - the player can still play;
1 - game over, no more space to play;
2 - win, the player reached 2048;
*/

int is_over(Game &curr_game){
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            if(curr_game.board[row][col] == 0) { return 0; }

            if (curr_game.board[row][col] == 2048) { return 2; }
            
        }
    }
    return 1;
}

// Crucial Functions
void start_game(Game &curr_game){
    curr_game.score = 0;
    backup.score = 0;
}

int update_board(Game &curr_game){
    int new_score = 0;
    for (auto& row : curr_game.board) {
        for (int& element : row) {
            new_score += element;
        }
    }

    if(new_score <= curr_game.score) return ERR;
    return OK;
}

int move_up(Game &curr_game){
    for(int col = 0; col < BOARD_SIZE; col++){
        for(int row = 1; row < BOARD_SIZE; row++){

            if(curr_game.board[row][col] != 0){
                int up = row - 1;
                while(up >= 0 && curr_game.board[up][col] == 0){
                    curr_game.board[up][col] = curr_game.board[up + 1][col];
                    curr_game.board[up + 1][col] = 0;
                    up--;
                }
            }
        }
    }
    return OK;
}

int merge_up(Game &curr_game){
    for(int col = 0; col < BOARD_SIZE; col++){
        for(int row = 1; row < BOARD_SIZE; row++){
            if(curr_game.board[row][col] != 0){
                if(curr_game.board[row - 1][col] == curr_game.board[row][col]){
                    curr_game.board[row - 1][col] = (curr_game.board[row - 1][col] + curr_game.board[row - 1][col]);
                    curr_game.board[row][col] = 0;
                }
            }
        }
    }
    return OK;
}

int move_down(Game &curr_game){
    for(int col = 0; col < BOARD_SIZE; col++){
        for(int row = 2; row >= 0; row--){

            if(curr_game.board[row][col] != 0){
                int down = row + 1;
                while(down < 4 && curr_game.board[down][col] == 0){
                    curr_game.board[down][col] = curr_game.board[down - 1][col];
                    curr_game.board[down - 1][col] = 0;
                    down++;
                }
            }
        }
    }
    return OK;
}

int merge_down(Game &curr_game){
    for(int col = 0; col < BOARD_SIZE; col++){
        for(int row = 2; row >= 0; row--){
            if(curr_game.board[row][col] != 0){
                if(curr_game.board[row + 1][col] == curr_game.board[row][col]){
                    curr_game.board[row + 1][col] = (curr_game.board[row][col] + curr_game.board[row][col]);
                    curr_game.board[row][col] = 0;
                }
            }
        }
    }
    return OK;
}

int move_left(Game &curr_game){
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 1; col < BOARD_SIZE; col++){
            if(curr_game.board[row][col] != 0){

                int left = col;
                while(left > 0){
                    if(curr_game.board[row][left - 1] == 0){
                        curr_game.board[row][left - 1] = curr_game.board[row][left];
                        curr_game.board[row][left] = 0;
                    }
                    left-- ;
                }
            
            }
        }
    }

    return OK;
}

int merge_left(Game &curr_game){
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 1; col < BOARD_SIZE; col++){
            if(curr_game.board[row][col] != 0){
                
                if(curr_game.board[row][col - 1] == curr_game.board[row][col]){
                    curr_game.board[row][col - 1] = (curr_game.board[row][col] + curr_game.board[row][col]);
                    curr_game.board[row][col] = 0;
                }

            }
        }
    }
    return OK;
}

int move_right(Game &curr_game){
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 2; col >= 0; col--){
            if(curr_game.board[row][col] != 0){
                
                int right = col;
                while(right < 3){
                    if(curr_game.board[row][right + 1] == 0){
                        curr_game.board[row][right + 1] = curr_game.board[row][right];
                        curr_game.board[row][right] = 0;
                    }
                    right++;
                }
            
            }
        }
    }
    return OK;
}

int merge_right(Game &curr_game){
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 2; col >= 0; col--){
            if(curr_game.board[row][col] != 0){
            
                if(curr_game.board[row][col + 1] == curr_game.board[row][col]){
                    curr_game.board[row][col + 1] = (curr_game.board[row][col] + curr_game.board[row][col]);
                    curr_game.board[row][col] = 0;
                }

            }
        }
    }
    return OK;
}

int main(){
    //
    char key;
    Game curr_game;
    int result = 0;

    cout << "\t\tWelcome !\n Press T anytime to pause the game.\n";

    start_game(curr_game);
    cout << "Use W,A,S,D to play.\n";
    
    do
    {
        random_piece(curr_game);
        display_board(curr_game);
        save_board(curr_game);
        result = is_over(curr_game);
        

        read(STDIN_FILENO, &key, 1);
        if(key == 'W' || key == 'w'){
            move_up(curr_game);
            merge_up(curr_game);
            move_up(curr_game);
        }

        else if(key == 'A' || key == 'a'){
            move_left(curr_game);
            merge_left(curr_game);
            move_left(curr_game);
        }

        else if(key == 'S' || key == 's'){
            move_down(curr_game);
            merge_down(curr_game);
            move_down(curr_game);
        }

        else if(key == 'D' || key == 'd'){
            move_right(curr_game);
            merge_right(curr_game);
            move_right(curr_game);
        }

        else if(key == 'T' || key == 't'){
            int pause = pause_game(curr_game);
            while (pause != OK) {
                if (pause == RESET) {
                    reset_game(curr_game);
                    break;
                }

                else if(pause == EXIT) if (exit_game(curr_game) == EXIT) return 0;
                
                pause = pause_game(curr_game);
            }
        }

        read(STDIN_FILENO, &key, 1); //Reads the new line.
        while(key != '\n') read(STDIN_FILENO, &key, 1); //Reads the new line.
    } while (result == 0);

    switch (result)
    {
    case 2:
        cout << "\n + - GG Well Played - +\n";
        break;
    
    default:
        cout << "\n + - Game Over - +\n";
        break;
    }

    return 0;
}