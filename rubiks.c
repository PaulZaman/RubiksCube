// This file contains the imports and structure definitions

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>



typedef enum {UP, LEFT, FRONT, RIGHT, BACK, DOWN } T_SIDE ;
typedef enum {W, O, G, R, B, Y, LG} T_COLOR;

typedef struct {
	int n_rotation;
} counter;

counter cube_counter;
