/*
 * helpers.h
 *
 * Interface of helper functions for the Game of Life.
 *
 * @author chindesaurus
 * @version 1.00
 */

#ifndef HELPERS_H_
#define HELPERS_H_

/* state constants */
#define DEAD 0
#define ALIVE 1


/*
 * Initializes the world from file filename, assuming that
 * character x of line y represents world[x][y]. Sets the
 * next generation to DEAD.
 */
extern void initialize_world_from_file(const char *filename);


/* initialize_world -- set up world, all cells initialized
   to DEAD or ALIVE; all cells in next generation are
   initialized to DEAD */
extern void initialize_world(void);


/*
 * Returns the width of the world.
 */
extern int get_world_width(void);


/*
 * Returns the height of the world.
 */
extern int get_world_height(void);


/* 
 * Returns the state (DEAD or ALIVE) of the cell at (x,y);
 * coordinates go from x = 0,...,width-1 and y = 0,...,height-1; 
 * returns DEAD for cells outside this range.
 */
extern int get_cell_state(int x, int y);


/* 
 * Sets the state (DEAD or ALIVE) of the cell at (x,y) in
 * the next generation; range of coordinates same as in
 * get_cell_state(); calls abort() if invalid coordinates
 * are specified.
 */
extern void set_cell_state(int x, int y, int state);


/* 
 * Updates world state to next generation and resets all
 * next generation states to DEAD.
 */
extern void finalize_evolution(void);


/* 
 * Outputs the current world state to the console.
 */
extern void output_world(void);


#endif /* HELPERS_H_ */
