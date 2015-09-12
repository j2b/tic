//
//  ticboard.c
//  tic
//
//  Created by John McGlinn on 9/12/15.
//  Copyright (c) 2015 j2b. All rights reserved.
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
    
    return board->sz;
}

void tic_destroy_board(ticBoard *board){
    assert(board->sz > 0);
    board->sz = 0;
    board->x = 0;
    board->y = 0;
    free(board->field);
}
