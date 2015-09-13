//
//  ticboard.c
//  tic
//
//  Created by J.P. McGlinn on 9/12/15.
//  Copyright (c) 2015 j2b. All rights reserved.
//  Copyright (c) 2015 J.P. McGlinn. All rights reserved.
//

#include "ticboard.h"
#include <assert.h>
#include <strings.h>

size_t tic_init_board(int x, int y, ticBoard *board){
    board->sz = (size_t) x * (size_t) y;
    board->x = x;
    board->y = y;
    board->field = malloc(board->sz);
    memset(board->field, EMPTY, board->sz);
    return board->field!=NULL?board->sz:0;
}

void tic_destroy_board(ticBoard *board){
    assert(board->sz > 0);
    board->sz = 0;
    board->x = 0;
    board->y = 0;
    free(board->field);
}

char tic_get(int x, int y, ticBoard *board){
    assert(board->sz > 0);
    assert(board->sz > (size_t) (x * y));
    
    return board->field[y*board->x + x];
}

char tic_put(int x, int y, ticBoard *board, char cellstate){
    assert(board->sz > 0);
    assert(board->sz > (size_t) (x * y));
    
    board->field[y*board->x + x] =cellstate;
    return board->field[y*board->x + x];
}
