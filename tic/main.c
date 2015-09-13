//
//  main.c
//  tic
//
//  Created by J.P. McGlinn on 9/11/15.
//  Copyright (c) 2015 j2b. All rights reserved.
//  Copyright (c) 2015 J.P. McGlinn. All rights reserved.
//  Copyright (c) 2015 Bart Bartel. All rights reserved.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "ticboard.h"

int get_term_width();
void tic_display_board_nc();
void tic_display_board_cli(ticBoard *board);
void tic_refresh_board(ticBoard *board);
void tic_update_board(short int play_x, short int play_y, ticBoard *board, char player);
void tic_update_cell_nc(short int play_x, short int play_y, char marker);
void welcome(void);
short int scr_x, scr_y;

int main(int argc, const char * argv[]) {
    ticBoard board;
    if(tic_init_board(3, 3, &board) == 0){
        fprintf(stderr, "Unable to allocate board\n");
        exit(EXIT_FAILURE);
    }

    initscr();

    welcome();
    
    tic_display_board_nc(&board);
    
    
    //BEGIN DEBUG

    tic_update_board(0, 0, &board, EX);
    tic_update_board(0, 1, &board, OH);
    tic_update_board(0, 2, &board, EX);
    tic_update_board(1, 0, &board, OH);
    tic_update_board(1, 1, &board, EX);
    tic_update_board(1, 2, &board, OH);
    tic_update_board(2, 0, &board, EX);
    tic_update_board(2, 1, &board, OH);
    tic_update_board(2, 2, &board, EX);
    getch();

    tic_put(0, 0, &board, OH);
    tic_put(0, 1, &board, EX);
    tic_put(0, 2, &board, OH);
    tic_put(1, 0, &board, EX);
    tic_put(1, 1, &board, OH);
    tic_put(1, 2, &board, EX);
    tic_put(2, 0, &board, OH);
    tic_put(2, 1, &board, EX);
    tic_put(2, 2, &board, OH);
    tic_refresh_board(&board);
    getch();

    //END DEBUG
    
    
    tic_destroy_board(&board);
    endwin();
    
    exit(EXIT_SUCCESS);
}


int get_term_width(){
    //should find out the terminal width, but for now 80
    return 80;
}

void tic_display_board_nc(void){
    getmaxyx(stdscr,scr_y,scr_x);
    mvprintw((scr_y/2)-5, (scr_x/2)-4,      "  | |  ");
    mvprintw((scr_y/2)-4, (scr_x/2)-4,      "-------");
    mvprintw((scr_y/2)-3, (scr_x/2)-4,      "  | |  ");
    mvprintw((scr_y/2)-2, (scr_x/2)-4,      "-------");
    mvprintw((scr_y/2)-1, (scr_x/2)-4,      "  | |  ");
    refresh();
}

void tic_update_cell_nc(short int play_x, short int play_y, char marker){
    mvaddch((scr_y/2)-5 + play_y*2, (scr_x/2)-3+2*play_x, marker);
}

void tic_update_board(short int play_x, short int play_y, ticBoard *board, char player){
    char marker = ' ';
    
    tic_put(play_x, play_y, board, player);
    
    if(player == EX)
        marker = 'X';
    if(player == OH)
        marker = 'O';

    tic_update_cell_nc(play_x, play_y, marker);
    curs_set(1);
    refresh();
    
    return;
}

void tic_refresh_board(ticBoard *board){
    char marker = ' ';

    for(int y = board->y - 1; y >= 0; y--){
        for(int x = 0; x < board->x; x++) {
            switch(tic_get(x, y, board)){
                case EX:
                    marker = 'X';
                    break;
                case OH:
                    marker = 'O';
                    break;
            }
            
            tic_update_cell_nc(x, y, marker);
        }
    }

    curs_set(1);
    refresh();
    
    return;
}

void tic_display_board_cli(ticBoard *board){
    size_t horizontal_bar_sz = board->x * 2;
    char horizontal_bar[horizontal_bar_sz];
    memset(horizontal_bar, '-', horizontal_bar_sz - 1);
    horizontal_bar[horizontal_bar_sz - 1] = 0;
    
    for(int y = board->y - 1; y >= 0; y--){
        for(int x = 0; x < board->x; x++) {
            switch(tic_get(x, y, board)){
                case EX:
                    printf("X");
                    break;
                case OH:
                    printf("O");
                    break;
                default:
                    printf(" ");
            }
            if(x < board->x -1)
                printf("|");
        }
        printf("\n");
        if(y > 0)
            printf("%s\n", horizontal_bar);
    }
}

void welcome(void){
    // TODO make a center function
    size_t margin, msglen;
    char *spaces;
    const char welcome_msg[] = "WELCOME TO TIC TAC TOE";
    msglen = strlen(welcome_msg);
    
    if(get_term_width()<msglen)
        margin = 0;
    else
        margin = get_term_width() - strlen(welcome_msg) / 2;
    
    spaces = malloc(margin + 1);
    memset(spaces, ' ', margin);
    spaces[margin]=0;
    
    printf("%s%s\n\n", spaces, welcome_msg);
}
