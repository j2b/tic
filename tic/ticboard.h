//
//  ticboard.h
//  tic
//
//  Created by J.P. McGlinn on 9/11/15.
//  Copyright (c) 2015 j2b. All rights reserved.
//  Copyright (c) 2015 J.P. McGlinn. All rights reserved.
//

#ifndef tic_ticboard_h
#define tic_ticboard_h

#include <stdlib.h>

//board cell states
#define EX    1
#define EMPTY 0
#define OH    2

//board is a 3x3 grid, but could be larger
typedef struct{
    size_t sz;
    int x;
    int y;
    char* field;
} ticBoard;

void tic_destroy_board(ticBoard *board);
size_t tic_init_board(int x, int y, ticBoard *board);
char tic_get(int x, int y, ticBoard *board);
char tic_put(int x, int y, ticBoard *board, char cellstate);

#endif
