/*
 * helpers.c
 *
 * Implements helper functions for the Game of Life.
 *
 * @author chindesaurus
 * @version 1.00
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "helpers.h"

/* hard-coded world size */
#define WORLDWIDTH 39
#define WORLDHEIGHT 20

/* max line length */
#define MAX_LINE_LENGTH 256

/* character representations of cell states */
#define CHAR_ALIVE '*'
#define CHAR_DEAD ' '

/* current cell states of the world */
static int world[WORLDWIDTH][WORLDHEIGHT];

/* next generation cell states */
static int nextstates[WORLDWIDTH][WORLDHEIGHT];


/*
 * Initializes the world from file filename, assuming that
 * character x of line y represents world[x][y]. Sets the
 * next generation to DEAD.
 */
void 
initialize_world_from_file(const char *filename) {

    FILE *fp;
    int col = 0, row = 0, len;
    char strread[MAX_LINE_LENGTH];

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr,"Could not open file %s for reading.\n", filename);
        exit(1);
    }

    while (row < WORLDHEIGHT && !feof(fp)) {
        
        if (fgets(strread, MAX_LINE_LENGTH, fp) == NULL)
            break;
        
        len = strlen(strread);
        if (len > WORLDWIDTH)
            len = WORLDWIDTH;

        for (col = 0; col < len; col++) {
            if (strread[col] == CHAR_ALIVE)
                world[col][row] = ALIVE;
            else
                world[col][row] = DEAD;
        }

        // consider remaining cells in row DEAD
        for (; col < WORLDWIDTH; col++)
            world[col][row] = DEAD;
        
        row++;
    }

    // mark cells in remaining rows as DEAD 
    for (; row < WORLDHEIGHT; row++)
        for (col = 0; col < WORLDWIDTH; col++)
            world[col][row] = DEAD;

    // initialize next generation to DEAD
    for (col = 0; col < WORLDWIDTH; col++)
        for (row = 0; row < WORLDHEIGHT; row++)
            nextstates[col][row] = DEAD;

    fclose(fp);
}


/*
 * Initializes the world to a hard-coded pattern, and resets
 * all the cells in the next generation to DEAD 
 */
void 
initialize_world(void) {
    int i, j;

    for (i = 0; i < WORLDWIDTH; i++)
        for (j = 0; j < WORLDHEIGHT; j++)
            world[i][j] = nextstates[i][j] = DEAD;

    /* hard-code pattern "glider" */
    world[1][2] = ALIVE;
    world[3][1] = ALIVE;
    world[3][2] = ALIVE;
    world[3][3] = ALIVE;
    world[2][3] = ALIVE;
}


/*
 * Returns the width of the world.
 */
int 
get_world_width(void) {
    return WORLDWIDTH;
}


/*
 * Returns the height of the world.
 */
int 
get_world_height(void) {
    return WORLDHEIGHT;
}


/* 
 * Returns the state (DEAD or ALIVE) of the cell at (x,y);
 * coordinates go from x = 0,...,width-1 and y = 0,...,height-1; 
 * returns DEAD for cells outside this range.
 */
int 
get_cell_state(int x, int y) {
    if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT)
        return DEAD;
    return world[x][y];
}


/* 
 * Sets the state (DEAD or ALIVE) of the cell at (x,y) in
 * the next generation; range of coordinates same as in
 * get_cell_state(); calls abort() if invalid coordinates
 * are specified.
 */
void 
set_cell_state(int x, int y, int state) {
    if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT) {
        fprintf(stderr,"Error: coordinates (%d,%d) are invalid.\n", x, y);
        abort();
    }
    nextstates[x][y] = state;
}


/* 
 * Updates world state to next generation and resets all
 * next generation states to DEAD.
 */
void 
finalize_evolution(void) {
    int x, y;
    for (x = 0; x < WORLDWIDTH; x++) {
        for (y = 0; y < WORLDHEIGHT; y++) {
            world[x][y] = nextstates[x][y];
            nextstates[x][y] = DEAD;
        }
    }
}


/* 
 * Outputs the current world state to the console.
 */
void 
output_world(void) {
   
    char worldstr[2 * WORLDWIDTH + 2];
    int i, j;

    worldstr[2 * WORLDWIDTH + 1] = '\0';
    worldstr[0] = '+';
    
    for (i = 1; i < 2 * WORLDWIDTH; i++)
        worldstr[i] = '-';
    
    worldstr[2 * WORLDWIDTH] = '+';
    puts(worldstr);
    
    for (i = 0; i <= 2 * WORLDWIDTH; i+=2)
        worldstr[i] = '|';
    
    for (i = 0; i < WORLDHEIGHT; i++) {
        for (j = 0; j < WORLDWIDTH; j++)
            worldstr[2 * j + 1] = world[j][i] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
        puts(worldstr);
    }

    worldstr[0] = '+';
    for (i = 1; i < 2 * WORLDWIDTH; i++)
        worldstr[i] = '-';

    worldstr[2*WORLDWIDTH] = '+';
    puts(worldstr);
}
