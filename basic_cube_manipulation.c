// This file contains main functions for cube manipulation

// contents: 

//      - string_to_side()     --> recieves a string and returns the side of cube corresponding to the string
//      - string_to_color()    --> recieves a string and returns the color corresponding to the string
//      - get_color()          --> recieves a T_COLOR and returns a string with color code (for displaying the cube)
//      - create_rubiks()      --> creates the rubiks cube with dynamic allocation
//      - grey_cube()          --> fill the cube with the grey color
//      - display_rubiks()     --> displays the rubik's cube in the terminal
//      - free_cube()          --> free's the cube from memory
//      - pivot_face()         --> turns a face clockwise or anticlockwise (only face not rings)
//      - rotate_face()        --> rotates a full face (using pivot_face) and the rings aroudn the face
//      - side_name_rotation() --> rotates a face (give only face as paramater and big switch finds adjacent faces)
//      - shuffle_cube()       --> shuffle randomly a cube by using side_name_rotation function
//      - rotate_cube()        --> rotates cube horizontally(right or left) or vertically(up or down), 



# include "rubiks.c"

T_SIDE string_to_side(char side[20]){
    // recieves a string and returns the side of cube corresponding to the string
    // used for user input while naviguating through the menu
    if (!strcmp(side, "front")) return FRONT;
    else if (!strcmp(side, "back")) return BACK;
    else if (!strcmp(side, "right")) return RIGHT;
    else if (!strcmp(side, "left")) return LEFT;
    else if (!strcmp(side, "up")) return UP;
    else return DOWN;
}

T_COLOR string_to_color(char clr[20]){
    // recieves a string and returns the color corresponding to the string
    // used for user input while naviguating through the menu
    if (!strcmp(clr, "r")) return R;
    else if (!strcmp(clr, "b")) return B;
    else if (!strcmp(clr, "g")) return G;
    else if (!strcmp(clr, "y")) return Y;
    else if (!strcmp(clr, "w")) return W;
    else if (!strcmp(clr, "o")) return O;
    else return LG;
}

char* get_color(T_COLOR clr){
    // Returns the color as a string whith color code
    switch(clr){
        case R: return "1;31mR"; break;
        case B: return "1;36mB"; break;
        case G: return "1;32mG"; break;
        case W: return "1;37mW"; break;
        case Y: return "1;93mY"; break;
        case O: return "1;33mO"; break;
        case LG: return "1;90mG"; break;
    }

    
}

int *** create_rubiks(){
    // create the rubiks cube with dynamic alllocation
    int *** cube;
    int i, j, k;
    
    
    cube = (int***)calloc(6, sizeof(int**));

    for (i=0; i<6; i++){
        *(cube+i) = (int**)calloc(3, sizeof(int*));

        for (j=0; j<3; j++){
            *(*(cube+i)+j) = (int*)calloc(3, sizeof(char));

            for (k=0; k<3; k++){
                *(*(*(cube+i)+j)+k) = (T_COLOR)i;
            }
        }
        
    }
    return cube;
}

void grey_cube(int *** cube){
    // fill the cube with the grey color
    int face, y, x;
    for (face=0; face<6; face++){
        for (y=0; y<3; y++){
            for (x=0; x<3; x++){
                *(*(*(cube+face)+y)+x) = LG;
            }
        }
    }
}

void display_rubiks(int*** cube){
    // displays the rubik's cube in the terminal
    int face;
    int x, y, k;
    T_SIDE line_of_faces[4] = {LEFT, FRONT, RIGHT, BACK};

    // display UP face
    printf("\n             ");
    face=UP;
    for(y=0; y<3; y++){
        for(x=0; x<3; x++){
            printf("\x1b[%s   \x1b[0m", get_color(*(*(*(cube+face)+y)+x)));
        }
        if (y!=2)printf("\n             ");
    }
    printf("\n");

    // display LEFT, FRONT, RIGHT, BACK Faces
    for (y=0; y<3; y++){
        for(x=0; x<4; x++){
            face = line_of_faces[x];
            for (k=0; k<3; k++)
                printf("\x1b[%s   \x1b[0m", get_color(*(*(*(cube+face)+y)+k)));
            printf(" ");
        }
        printf("\n");

    }
    
    //display DOWN Face
    printf("             ");
    face=DOWN;
    for(y=0; y<3; y++){
        for(x=0; x<3; x++){
            printf("\x1b[%s   \x1b[0m", get_color(*(*(*(cube+face)+y)+x)));
        }
        if (y!=2)printf("\n             ");
    }
    printf("\n");
}

void free_cube(int *** cube){
    // free the cube from memory
    int cpt, cpt2;
    for (cpt=0; cpt<6; cpt++){
        for (cpt2=0; cpt2<3; cpt2++){
            free(*(*(cube+cpt)+cpt2));
        }
    }
}



void pivot_face(int*** cube, T_SIDE face, int dir){
    // turns a face passed as paramter clockwise or anti-clockwise
    // turns only the face (not rings around the face)
    // direction = -1 for counter clockwise
    // direction = 1 for clockwise
    int i;
    T_COLOR saved1, saved2;
    // clockwise 
    if (dir == 1){
        for (i=0; i<2; i++){
                saved1 = *(*(*(cube+face))+i);
                *(*(*(cube+face))+i) = *(*(*(cube+face)+2-i));
                saved2 = *(*(*(cube+face)+i)+2);
                *(*(*(cube+face)+i)+2) = saved1;
                saved1 = *(*(*(cube+face)+2)+2-i);
                *(*(*(cube+face)+2)+2-i) = saved2;
                *(*(*(cube+face)+2-i)) = saved1;
            }
    }
    // anticlockwise
    if (dir == -1){
        for (i=0; i<2; i++){
                saved1 = *(*(*(cube+face)+i));
                *(*(*(cube+face)+i)) = *(*(*(cube+face))+2-i);
                saved2 = *(*(*(cube+face)+2)+i);
                *(*(*(cube+face)+2)+i) = saved1;
                saved1 = *(*(*(cube+face)+2-i)+2);
                *(*(*(cube+face)+2-i)+2) = saved2;
                *(*(*(cube+face))+2-i) = saved1;
            }
    }
    }

void rotate_face(int*** cube, T_SIDE face, T_SIDE left, T_SIDE right, T_SIDE up, T_SIDE down, int dir){
    // Turns the face and rings to the adjacent faces
    // adjacent faces need to be turned beforehand, so that the junction between the faces corresponds
    // direction = -1 for counter clockwise
    // direction = 1 for clockwise
    T_COLOR saved1, saved2;
    int i;


    // rotates rings around face
    if (dir == 1){  // if rotation is clockwise
        for (i=0; i<3; i++){
            saved1 = *(*(*(cube+up)+2)+i);
            *(*(*(cube+up)+2)+i) = *(*(*(cube+left)+2-i)+2);
            saved2 = *(*(*(cube+right)+i));
            *(*(*(cube+right)+i)) = saved1;
            saved1 = *(*(*(cube+down))+2-i);
            *(*(*(cube+down))+2-i) = saved2;
            *(*(*(cube+left)+2-i)+2) = saved1;
        }
        pivot_face(cube, face, 1);
    }
    if (dir == -1){ // if rotation is anti-clockwise
        for (i=0; i<3; i++){
            saved1 = *(*(*(cube+up)+2)+2-i);
            *(*(*(cube+up)+2)+2-i) = *(*(*(cube+right)+2-i));
            saved2 = *(*(*(cube+left)+i)+2);
            *(*(*(cube+left)+i)+2) = saved1;
            saved1 = *(*(*(cube+down))+i);
            *(*(*(cube+down))+i) = saved2;
            *(*(*(cube+right)+2-i)) = saved1;
        }
        pivot_face(cube, face, -1);
    }
}

void side_name_rotation(int *** cube, T_SIDE face, int type, int dir){
    // rotates a face
    // before using the rotate face function, we need to pivot faces adjacent to the desired face to turn,
    // This is the role of this big and scary switch case

    // dir = -1 -> anticlockwise
    // dir = 1 -> clockwise
    // type = 1 -> quarter turn
    // if type = 2 -> half turn
    switch(face){
        case FRONT: 
            rotate_face(cube, face, LEFT, RIGHT, UP, DOWN, dir); 
            break;
        case RIGHT: 
            pivot_face(cube, UP, 1);
            pivot_face(cube, DOWN, -1);
            rotate_face(cube, face, FRONT, BACK, UP, DOWN, dir);
            pivot_face(cube, UP, -1);
            pivot_face(cube, DOWN, 1);
            break;
        case BACK: 
            pivot_face(cube, UP, 1);
            pivot_face(cube, UP, 1);
            pivot_face(cube, DOWN, -1);
            pivot_face(cube, DOWN, -1);
            rotate_face(cube, face, RIGHT, LEFT, UP, DOWN, dir);
            pivot_face(cube, UP, -1);
            pivot_face(cube, UP, -1);
            pivot_face(cube, DOWN, +1);
            pivot_face(cube, DOWN, +1);
            break;    
        case LEFT: 
            pivot_face(cube, UP, -1);
            pivot_face(cube, DOWN, 1);
            rotate_face(cube, face, BACK, FRONT, UP, DOWN, dir);
            pivot_face(cube, UP, 1);
            pivot_face(cube, DOWN, -1);
            break;    
        case DOWN: 
            pivot_face(cube, RIGHT, 1);
            pivot_face(cube, LEFT, -1);
            pivot_face(cube, BACK, -1);
            pivot_face(cube, BACK, -1);
            rotate_face(cube, face, LEFT, RIGHT, FRONT, BACK, dir);
            pivot_face(cube, RIGHT, -1);
            pivot_face(cube, LEFT, 1);
            pivot_face(cube, BACK, 1);
            pivot_face(cube, BACK, 1);
            break;
        case UP: 
            pivot_face(cube, RIGHT, -1);
            pivot_face(cube, LEFT, 1);
            pivot_face(cube, BACK, -1);
            pivot_face(cube, BACK,-1); 
            rotate_face(cube, face, LEFT, RIGHT, BACK, FRONT, dir);
            pivot_face(cube, RIGHT, 1);
            pivot_face(cube, LEFT, -1);
            pivot_face(cube, BACK, 1);
            pivot_face(cube, BACK, 1);
            break;
    }
    if (type == 2) side_name_rotation(cube, face, 1, dir);
    cube_counter.n_rotation++;
}




void shuffle_cube(int *** cube, int n_rotations){
    // This function randomly shuffles a cube by using side_name_rotation function
    int rand(void), cpt, dir;
    time_t t;
    srand((unsigned) time(&t)); // initialise random number generator

    for (cpt=0; cpt<n_rotations; cpt++){
        dir = rand()%2;
        if (dir==0) dir = -1;
        side_name_rotation(cube, rand()%6, (rand()%2)+1, dir);
    }

}

void rotate_cube(int***cube, char direction[2], char sens[2]){
    int**saved;
    // This function rotates cube horizontally or vertically
    if (!strcmp(direction, "v")){      
        if (!strcmp(sens, "u")){     // turns the cube upward
            pivot_face(cube, BACK, -1);
            pivot_face(cube, BACK, -1);
            saved = *(cube+DOWN);
            *(cube+DOWN) = *(cube+BACK);
            *(cube+BACK) = *(cube+UP);
            *(cube+UP) = *(cube+FRONT);
            *(cube+FRONT) = saved;
            pivot_face(cube, RIGHT, 1);
            pivot_face(cube, LEFT, -1);
            pivot_face(cube, BACK, -1);
            pivot_face(cube, BACK, -1);
        }
        if (!strcmp(sens, "d")){
            // turn down
            pivot_face(cube, BACK, -1);
            pivot_face(cube, BACK, -1);
            saved = *(cube+DOWN);
            *(cube+DOWN) = *(cube+FRONT);
            *(cube+FRONT) = *(cube+UP);
            *(cube+UP) = *(cube+BACK);
            *(cube+BACK) = saved;
            pivot_face(cube, RIGHT, -1);
            pivot_face(cube, LEFT, 1);
            pivot_face(cube, BACK, -1);
            pivot_face(cube, BACK, -1);
        }
        
    }
    if (!strcmp(direction, "h")){ 
        if (!strcmp(sens, "r")){   // turns the cube rightward
            saved = *(cube+BACK);
            *(cube+BACK) = *(cube+RIGHT);
            *(cube+RIGHT) = *(cube+FRONT);
            *(cube+FRONT) = *(cube+LEFT);
            *(cube+LEFT) = saved;
            pivot_face(cube, UP, -1);
            pivot_face(cube, DOWN, 1);
        }   
        if (!strcmp(sens, "l")){ 
            // rotate left
            saved = *(cube+BACK);
            *(cube+BACK) = *(cube+LEFT);
            *(cube+LEFT) = *(cube+FRONT);
            *(cube+FRONT) = *(cube+RIGHT);
            *(cube+RIGHT) = saved;
            pivot_face(cube, UP, 1);
            pivot_face(cube, DOWN, -1);
        }  
        
    }
}