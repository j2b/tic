//
//  main.c
//  tic
//
//  Created by J.P. McGlinn on 9/11/15.
//  Copyright (c) 2015 j2b. All rights reserved.
//  Copyright (c) 2015 J.P. McGlinn. All rights reserved.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ticboard.h"

int get_term_width();
void tic_display_board(ticBoard *board);
void welcome(void);


int main(int argc, const char * argv[]) {
    ticBoard board;
    if(tic_init_board(3, 3, &board) == 0){
        fprintf(stderr, "Unable to allocate board\n");
        exit(EXIT_FAILURE);
    }
    
    welcome();
    
    tic_display_board(&board);
    
    
    //BEGIN DEBUG
    tic_put(0, 0, &board, EX);
    tic_put(0, 1, &board, EX);
    tic_put(2, 0, &board, OH);
    tic_put(2, 2, &board, OH);
    
    printf("\n\n 0,0 X; 0,1 X; 2,0 O; 2,2 0\n");
    tic_display_board(&board);
    //END DEBUG
    
    tic_destroy_board(&board);
    
    exit(EXIT_SUCCESS);
}


int get_term_width(){
    //should find out the terminal width, but for now 80
    return 80;
}

void tic_display_board(ticBoard *board){
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
