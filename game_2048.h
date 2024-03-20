#ifndef GAME_2048  // Include guards to prevent multiple inclusion
#define GAME_2048

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

#define ERR -1
#define OK 0
#define RESET 1
#define EXIT 2
#define BOARD_SIZE 4

int score;

typedef struct game
{
    int score;
    vector<vector<int>> board = vector<vector<int>>(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
} Game;

void display_board(Game &curr_game);

int generate_value();

void save_board(Game &curr_game);

void reset(Game &curr_game);

int initialize_board(Game &curr_game);

void start_game(Game &curr_game);

int update_board(Game &curr_game);

int move_up(Game &curr_game);

int merge_up(Game &curr_game);

int move_down(Game &curr_game);

int merge_down(Game &curr_game);

int move_left(Game &curr_game);

int merge_left(Game &curr_game);

int move_right(Game &curr_game);

int merge_right(Game &curr_game);


Game backup;

#endif  // MYHEADER_H