/*
 * life.c
 *
 * Implements Conway's Game of Life.
 *
 * Usage: ./life [input]
 * where input is a text file containing
 * an initial state.
 *
 * @author chindesaurus
 * @version 1.00
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "helpers.h"


/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* function prototypes */
void clear(void);
void next_generation(void);
int get_next_state(int x, int y);
int num_neighbors(int x, int y);
 

int 
main(int argc, char **argv) {

    // if there's command-line argument
    // use it to initialize the Game of Life
    if (argc == 2) {
        initialize_world_from_file(argv[1]);
     
       // evolve for NUM_GENERATIONS 
        for (int i = 0; i < NUM_GENERATIONS; i++) {
            clear();
            output_world();
            next_generation();
            usleep(250000);     // sleep for 0.25 seconds
        }
    }
    // else initialize world with hard-coded pattern
    else {
        // awesome infinite glider gun
        initialize_world_from_file("./inputs/gun.txt");
        while (1) {
            clear();
            output_world();
            next_generation();
            usleep(250000);     // sleep for 0.25 seconds
        }
    }

    // kthxbai
    return 0;
}


/*
 * Clears screen using ANSI escape sequences.
 */
void
clear() {
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}


/* 
 * For every cell, set the state in the next
 * generation according to the Game of Life rules.
 */
void 
next_generation(void) {
    int width = get_world_width();   
    int height = get_world_height();   
 
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            set_cell_state(i, j, get_next_state(i, j));

    finalize_evolution();
}


/* 
 * For the specified cell, compute the state in
 * the next generation using the rules.
 * Returns ALIVE or DEAD indicating next state
 * of the cell at (x, y).
 */
int 
get_next_state(int x, int y) {
    int n = num_neighbors(x, y);

    if (get_cell_state(x, y) == ALIVE)
        return (n == 2 || n == 3) ? ALIVE : DEAD;
    else
        return (n == 3) ? ALIVE : DEAD;
}


/* 
 * For the specified cell, return the number of
 * neighbors that are ALIVE.
 */
int 
num_neighbors(int x, int y) {

    int count = 0;

    /* check all eight neighbors */
    
    // look left
    if (get_cell_state(x - 1, y) == ALIVE)
        count += 1;
    // look right
    if (get_cell_state(x + 1, y) == ALIVE)
        count += 1;
    // look up
    if (get_cell_state(x, y - 1) == ALIVE)
        count += 1;
    // look down 
    if (get_cell_state(x, y + 1) == ALIVE)
        count += 1;
    // look to the upper-left
    if (get_cell_state(x - 1, y - 1) == ALIVE)
        count += 1;
    // look to the upper-right
    if (get_cell_state(x + 1, y - 1) == ALIVE)
        count += 1;
    // look to the lower-left
    if (get_cell_state(x - 1, y + 1) == ALIVE)
        count += 1;
    // look to the lower-right
    if (get_cell_state(x + 1, y + 1) == ALIVE)
        count += 1;

    return count;
}
