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
#include <math.h>
#include "ticboard.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int get_term_width();
void tic_display_board_nc();
void tic_display_board_cli(ticBoard *board);
void tic_refresh_board(ticBoard *board);
void tic_update_board(short int play_x, short int play_y, ticBoard *board, char player);
void tic_update_cell_nc(short int play_x, short int play_y, char marker);
void welcome(void);
//short int wscr, hscr;
short int wscr, hscr;
short int wbrd, hbrd;
short int wcel, hcel;
WINDOW *ticwin;

int main(int argc, const char * argv[]) {
    ticBoard board;
    if(tic_init_board(3, 3, &board) == 0){
        fprintf(stderr, "Unable to allocate board\n");
        exit(EXIT_FAILURE);
    }

    initscr();

    welcome();
    
    tic_display_board_nc(&board);
    tic_update_cell_nc(0,0,'x');
    tic_update_cell_nc(0,1,'o');
    tic_update_cell_nc(0,2,'x');

    tic_update_cell_nc(1,0,'o');
    tic_update_cell_nc(1,1,'x');
    tic_update_cell_nc(1,2,'o');

    tic_update_cell_nc(2,0,'x');
    tic_update_cell_nc(2,1,'o');
    tic_update_cell_nc(2,2,'x');
    goto out;
    
    
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
    
out:    
    getch();
    tic_destroy_board(&board);
    delwin(ticwin);
    endwin();
    
    exit(EXIT_SUCCESS);
}


int get_term_width(){
    //should find out the terminal width, but for now 80
    return 80;
}

void tic_display_board_nc(void){
    refresh();
    ticwin = newwin(0, 0, 0, 0);
    getmaxyx(ticwin,hscr,wscr);
    hbrd = hscr;
    wbrd = wscr;
    hcel = hbrd / 3;
    wcel = wbrd / 3;
    box(ticwin, 0 , 0);		/* 0, 0 gives default characters     */
    wrefresh(ticwin);
    wmove(ticwin, hcel, 0); whline(ticwin, '-', wbrd);
    wmove(ticwin, 2*hcel, 0); whline(ticwin, '-', wbrd);
    wmove(ticwin, 0, wcel); wvline(ticwin, '|', hbrd);
    wmove(ticwin, 0, 2*wcel); wvline(ticwin, '|', hbrd);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    wbkgd(ticwin, COLOR_PAIR(1));
    wrefresh(ticwin);

    //mvprintw(0,0,"wscr=%d, hscr=%d, wbrd=%d, hbrd=%d, wcel=%d, hcel=%d\n", wscr, hscr, wbrd, hbrd, wcel, hcel);
    //mvprintw(2,0,"wscr=%d, hscr=%d, wbrd=%d, hbrd=%d, wcel=%d, hcel=%d\n", wscr, hscr, wbrd, hbrd, wcel, hcel);
    //mvprintw(4,0,"wscr=%d, hscr=%d, wbrd=%d, hbrd=%d, wcel=%d, hcel=%d\n", wscr, hscr, wbrd, hbrd, wcel, hcel);
    //wmove(ticwin, hcel, 0); whline(ticwin, '-', 3*wcel);
    //move(hbrd-3, wbrd); hline('-', 3*wcel);

    //move(hbrd-(1*hcel), wbrd-(3*wcel)); hline('-', 3*wcel);
    //move(hbrd-(1*hcel), wbrd-(1*wcel)); hline('-', 3*wcel);
    //move(hbrd-(3*hcel), wbrd-(3*wcel)); vline('-', 3*hcel);
    //move(hbrd-(3*hcel), wbrd-(3*wcel)); vline('-', 3*hcel);
#if 0
    mvprintw((hscr/2)-5, (wscr/2)-4,      "  | |  ");
    mvprintw((hscr/2)-4, (wscr/2)-4,      "-------");
    mvprintw((hscr/2)-3, (wscr/2)-4,      "  | |  ");
    mvprintw((hscr/2)-2, (wscr/2)-4,      "-------");
    mvprintw((hscr/2)-1, (wscr/2)-4,      "  | |  ");
#endif
    //refresh();
}

#define DEGTORAD(deg) (deg * (180.0f/M_PI))
void tic_update_cell_nc(short int row, short int col, char marker){
    //mvaddch((hscr/2)-5 + play_y*2, (wscr/2)-3+2*play_x, marker);
    int h=0, w;
    if (marker == 'x') {
        for (h=w=0; w<hcel-3; w++, h++) {
            mvwaddch(ticwin, row*hcel+h+2, col*wcel+w+2, marker);
        }
        for (h=w=0; w<hcel-3; w++, h++) {
            mvwaddch(ticwin, (row+1)*hcel-h-2, col*wcel+col+w+2, marker);
        }
    } else {
        float deg, width, height;
        width = wcel/2;
        height = hcel/2;
        int y, x;
        for (deg = 0; deg < 360.0f; deg += 1.0f) {
            x = width+(int)(width * cos(DEGTORAD(deg))) + col * wcel;
            y = height+(int)(height * sin(DEGTORAD(deg))) + row * hcel;
            mvwaddch(ticwin, y, x, '.');
        }
        
    }
    wrefresh(ticwin);
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
