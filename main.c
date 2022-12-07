// This file contains the main menu, it manipulates functions from the other files depending on the user input

//      - display_commands()    --> takes as parameter the screen user is on, and prints the corresponding commands he can type in
//      - rotate()              --> rotates a face using the user input
//      - next_step()           --> realises next step for solving the cube 

//      - fill_grey_cube()      --> fills the grey cube manually
//      - new_cube()            --> menu screen to manipulate the cube
//      - main_menu()           --> main menu screen

//      - main()                --> MAIN



# include "solving_algorithm.c"



void display_commands(char menustate[10]){
    // takes as parameter the screen user is on, and prints the corresponding commands he can type in
    printf("Commands :\n");
    if (!strcmp(menustate, "main")){
        printf(" -- new                     (create a cube and enter resolving menu)\n");
        printf(" -- about                   (get info about the programm)\n");
        printf(" -- exit                    (exit the game)\n");
    }
    else if (!strcmp(menustate, "cubemenu")){
        printf(" -- shuffle                 (randomely shuffle the cube)\n");
        printf(" -- turncube                (rotate cube horizontally or vertically)\n");
        printf(" -- rotate                  (rotate a face)\n");
        printf(" -- quicksolve              (solve cube completely)\n");
        printf(" -- timetest                (solve cube a predefinied amount and time the execution)\n");
        printf(" -- next                    (go to next step in solving the cube)\n");
        printf(" -- reset                   (reset the cube to solved)\n");
        printf(" -- grey                    (make the cube all grey in order to fill colors manually)\n");
        printf(" -- return                  (go back to main menu)\n");
        printf(" -- exit                    (exit the game)\n");
    }
}

void rotate(int *** cube, char side[20], int dir, int type){
    // rotates a face using the user input
    if (type>1) type=2;
    side_name_rotation(cube, string_to_side(side), type, dir);
}

void next_step(int***cube, int current_step){
    // realises next step for solving the cube 
    switch(current_step){
        case 1:{
            cube_counter.n_rotation = 0;
            top_cross(cube);
            printf("\n__Executed top cross__\n");
            break;
        }
        case 2:{
            top_corners(cube);
            printf("\n__Executed top face and first row__\n");
            break;
        }
        case 3:{
            second_layer(cube);
            printf("\n__Executed second row__\n");
            break;
        }
        case 4:{
            down_face(cube);
            printf("\n__Executed down face__\n");
            break;
        }
        case 5:{
            down_corners(cube);
            printf("\n__Executed down corners__\n");
            break;
        }
        case 6:{
            bottom_middle_pieces(cube);
            printf("\n__Executed bottom middle pieces__\nCUBE SOLVED\n");
            printf("Solved in %d moves\n", cube_counter.n_rotation);
            cube_counter.n_rotation = 0;
            break;
        }
        default: printf("\n___cube is already solved___\n");
    }
}

void fill_grey_cube(int***cube){
    // function to fill cube manually
    int done=1, line=0, cpt;
    char face[10], color[3], options[10];
    grey_cube(cube);


    while(done){
        display_rubiks(cube);
        printf("\nEnter face you would like to modify or return to exit('front', 'up', 'down', 'left', 'right', 'back')\n >> ");
        scanf("%s", face);

        if (!strcmp(face, "return")) return;
        printf("Fill whole %s face in one go ? (yes or no)\n >> ", face);
        scanf("%s", options);


        if (!strcmp("yes", options)){ 
              // if fullface is  on
            for (line=0; line<3; line++){
                for (cpt=0; cpt<3; cpt++){
                    printf("Enter a color for line %d of %s face position %d ('r', 'b', 'g', 'y', 'o', 'w')\n >> ", line+1, face, cpt+1);
                    scanf("%s", color);
                    *(*(*(cube+string_to_side(face))+line)+cpt) = string_to_color(color);
                    display_rubiks(cube);
                }
            }
        }
        else {
            printf("Which line of %s face ? (1, 2, or 3) \n >> ", face);
            scanf("%d", &line);
            for (cpt=0; cpt<3; cpt++){
                printf("Enter a color for line %d of %s face position %d ('r', 'b', 'g', 'y', 'o', 'w')\n >> ", line, face, cpt+1);
                scanf("%s", color);
                *(*(*(cube+string_to_side(face))+line-1)+cpt) = string_to_color(color);
                display_rubiks(cube);
            }
        }
        
    }
    
}

int new_cube(){
    // menu screen to manipulate the cube
    char action[20], face[20], direction[3];
    int *** cube;
    int run=1, dir, n_rotation, current_step=0;
    cube = create_rubiks();
    cube_counter.n_rotation=0;
    printf("\n\n\x1b[1;31mCUBE MENU\n\n\x1b[0m");
    display_commands("cubemenu");
    printf("\nType in a command or 'help' to get list of commands\n\n");
    while (run) {
        
        
        if (strcmp(action, "exit")){        // if action is not exit
            printf("This is your cube : \n");
            display_rubiks(cube);
            printf(" >> ");
            scanf("%s", action);
        }
        
            

        // actions
        if (!strcmp("help", action)) display_commands("cubemenu");
        else if (!strcmp("shuffle", action)) {
            shuffle_cube(cube, 50);
            current_step = 0;
            }
        else if (!strcmp("next", action)){
            current_step++;
            next_step(cube, current_step);
        }
        else if (!strcmp("quicksolve", action)) {
            cube_counter.n_rotation=0;
            if (solve_cube(cube)){
                printf("\n\n\x1b[1;31mERROR: Cube is not solvable / algorithm error\n\x1b[0m");
                printf("Algorithm errors are rare but do happen occasionnaly, shuffle again and retry\n");
            }
            printf("Cube solved in %d moves\n", cube_counter.n_rotation);
            cube_counter.n_rotation=0;
        }
        else if (!strcmp("turncube", action)) {
            printf("In which direction ? horizontal('h') or vertical('v') ?\n >> ");
            scanf("%s", direction);
            if (!strcmp(direction, "v")){
                printf("up or down ? ('u' or 'd')\n >> ");
                scanf("%s", action);
            }
            if (!strcmp(direction, "h")){
                printf("right or left ? ('r' or 'l')\n >> ");
                scanf("%s", action);
            }
            
            rotate_cube(cube, direction, action);
            current_step = 0;
        }
        else if (!strcmp("rotate", action)){
            printf("Enter face:  'front', 'back', 'up', 'left', 'right', 'down'\n >> ");
            scanf("%s", face);
            printf("Enter dir: 1 for clockwise, -1 for anticlockwise\n >> ");
            scanf("%d", &dir);
            printf("Enter number of quarter rotations\n >> ");
            scanf("%d", &n_rotation);
            rotate(cube, face, dir, n_rotation);
            current_step=0;
        }
        else if (!strcmp("reset", action)){
            free_cube(cube);
            cube = create_rubiks();
            current_step=0;
        }
        else if (!strcmp("grey", action)){
            fill_grey_cube(cube);
            printf("\n\n\x1b[1;31mCUBE MENU\n\n\x1b[0m");
            display_commands("cubemenu");
            printf("\nType in a command or 'help' to get list of commands\n\n");
            }
        else if (!strcmp("return", action)) {
                                            free_cube(cube);
                                            run=0;
                                            return 0;}
        else if (!strcmp("timetest", action)){
            printf("Enter a number of repetitions for your test\n >> ");
            scanf("%d", &n_rotation);
            solve_cube_n_times(cube, n_rotation);
        }
        else if (!strcmp("exit", action)) {
            run = 0; 
            free(cube);
            return 1;
            }
        else printf("Unknown Command\n");
    }
    free_cube(cube);
    return 0;
}

void main_menu(){
    // main menu screen
    char action[20];
    int run=1;
    printf("\n\n\x1b[1;31mMAIN MENU\n\n\x1b[0m");
    display_commands("main");
    printf("\nType in a command or 'help' to get list of commands\n\n");
    while (run){
        
        if (strcmp(action, "exit")){
            printf(" >> ");
            scanf("%s", action);
        } 

        // do action
        if (!strcmp("help", action)) display_commands("main");
        else if (!strcmp("about", action)) {
            printf("This Program was realised in May 2021, by: \n    - Ponsin Arsène\n    - Fournier Cléophas\n    - Zamanian Paul\nfor a school project. This is our first ever C# project, we hope you like it !\n");
        }
        else if (!strcmp("new", action)) {
            if (new_cube())strcpy(action, "exit");
            else {
                printf("\n\n\x1b[1;31mMAIN MENU\x1b[0m");
                printf("\nType in a command or 'help' to get list of commands\n\n");}
            }
        else if (!strcmp("exit", action)) {run = 0; return;}
        else printf("Unknown Command\n");    
    }
}



int main(){
    //MAIN
    main_menu();
}