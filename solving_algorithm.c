// This file contains functions for solving the cube, it uses the functions from "basic_cube_manipulation.c" to turn the faces

// contents: 

//      - get_adjacent_color_on_bottom()        --> returns the adjacent color between bottom and specified face middle down pos
//      - put_bottom_layer_center_piece_on_top_face()      --> moves a square from the middle of bottom layer to top face
//      - put_bottom_layer_corner_piece_on_top_face()      --> moves a square from the corner of bottom layer to top face
//      - mount_on_to_second_layer()                   --> mounts a piece on second layer algorithm

//      - top_cross()                        --> make a perfect top cross
//      - top_corners()                      --> make a perfect top face and first layer
//      - second_layer()                     --> makes the second layer
//      - down_face()                        --> completes the bottom face of the cube in two steps
//      - down_corners()                     --> orients corners of the side faces to match their centers
//      - bottom_middle_pieces()             --> last step, swap the middle bottom pieces of each face until the cube is solved

//      - solve_cube()                       --> solve the cube using functions above and display cube and step name at each step
//      - solve_cube_time_test()             --> solve the cube without displaying anything (for efficiency)
//      - solve_cube_n_times()               --> solve the cube as much as many times as you want, time it, and display the average speed of algorithm




# include "basic_cube_manipulation.c"



T_COLOR get_adjacent_color_on_bottom(int*** cube, T_SIDE face){
    // this function returns the adjacent color between bottom and specified face middle down pos
    T_SIDE bottom;
    T_COLOR adj;
    bottom = DOWN;
    switch(face){
        case LEFT:
            pivot_face(cube, DOWN, 1);
            adj = *(*(*(cube+bottom))+1);
            pivot_face(cube, DOWN, -1);
            break;
        case FRONT:
            adj = *(*(*(cube+bottom))+1);
            break;
        case RIGHT:
            pivot_face(cube, DOWN, -1);
            adj = *(*(*(cube+bottom))+1);
            pivot_face(cube, DOWN, 1);
            break;
        case BACK:
            pivot_face(cube, DOWN, 1);
            pivot_face(cube, DOWN, 1);
            adj = *(*(*(cube+bottom))+1);
            pivot_face(cube, DOWN, 1);
            pivot_face(cube, DOWN, 1);
            break;
        case UP:;
        case DOWN:;
    }
    return adj;
}

void put_bottom_layer_center_piece_on_top_face(int *** cube, T_SIDE face){
    // This function moves a square from the middle of bottom layer to top face
        int dest, final_dest_face;
        T_COLOR adjcolor;

        // find face just on left of where it's supposed to be
        // get color of adjacent piece
        adjcolor = get_adjacent_color_on_bottom(cube, face);
        final_dest_face=1;
        // find side where the piece should be on = k
        while(adjcolor != *(*(*(cube+final_dest_face)+1)+1)) {
            if (final_dest_face==4) final_dest_face=1; 
            else final_dest_face++;     
        }
        // piece should be above face n°k
        if (final_dest_face==1) dest = 4;
        else dest= final_dest_face-1;
        // put the white center piece on the face just left of face k
        while (face!=dest){
            side_name_rotation(cube, DOWN, 1, -1);
            if (face==1) face=4;
            else face--;}

         // bring up to top face
        side_name_rotation(cube, dest, 1, -1);
        side_name_rotation(cube, final_dest_face, 1, 1);
        side_name_rotation(cube, dest, 1, 1);
        
    }

void put_bottom_layer_corner_piece_on_top_face(int *** cube, T_SIDE face, int corner){
    // This function moves a square from the corners of bottom layer to top face
    // corner = 1 --> right
    // corner = 0 --> left
    int dest, final_dest_face, adjface, facetorotate;
    T_COLOR adjcolor;

    // if square is bottom right
    if (corner == 1){
            // get color of adjacent piece
            adjface  =face+1;
            if (adjface == 5) adjface = 1;
            adjcolor = *(*(*(cube+adjface)+2));
        

            // find face the piece should be on
            final_dest_face = 1;
            while(adjcolor != *(*(*(cube+final_dest_face)+1)+1)) {
                if (final_dest_face==4)final_dest_face=1; 
                else final_dest_face++;   
                
                
            }
            final_dest_face--;
            if (final_dest_face==0) final_dest_face=4; 


            // put the piece on final dest face

            while (face!=final_dest_face){
                side_name_rotation(cube, DOWN, 1, -1);
                if (face==1) face=4;
                else face--;
            }

            // find face just on right, to rotate when bringing piece up
            facetorotate = face+1;
            if (facetorotate == 5) facetorotate = 1;

            // bring up to top face
            side_name_rotation(cube, DOWN, 1, -1);
            side_name_rotation(cube, facetorotate, 1, -1);
            side_name_rotation(cube, DOWN, 1, 1);
            side_name_rotation(cube, facetorotate, 1, 1);
        }
    
    // if square is bottom left
    if (corner == 0){
            // get color of adjacent piece
            adjface = face-1;
            if (adjface == 0) adjface = 4;
            adjcolor = *(*(*(cube+adjface)+2)+2);
        

            // find face the piece should be on
            final_dest_face = 1;
            while(adjcolor != *(*(*(cube+final_dest_face)+1)+1)) {
                if (final_dest_face==4) final_dest_face=1; 
                else final_dest_face++;     
            }
            final_dest_face++;
            if (final_dest_face==5) final_dest_face=1; 


            // put the piece on the face final dest face
            
            while (face!=final_dest_face){
                side_name_rotation(cube, DOWN, 1, -1);
                if (face==1) face=4;
                else face--;

            }

            // find face just on left, to rotate when bringing piece up
            facetorotate = face-1;
            if (facetorotate == 0) facetorotate = 4;

            // bring up to top face
            side_name_rotation(cube, DOWN, 1, 1);
            side_name_rotation(cube, facetorotate, 1, 1);
            side_name_rotation(cube, DOWN, 1, -1);
            side_name_rotation(cube, facetorotate, 1, -1);
        }
        
}

void mount_on_to_second_layer(int***cube, T_SIDE face){
    // mounts a piece onto second layer
    T_COLOR square_color, bottom_color;
    T_SIDE dest_face;

    square_color = *(*(*(cube+face)+2)+1);
    bottom_color = get_adjacent_color_on_bottom(cube, face);

    // put piece correct face
    while (*(*(*(cube+face)+2)+1) != *(*(*(cube+face)+1)+1)){
        face++;
        if (face == 5) face = 1;
        side_name_rotation(cube, DOWN, 1, 1);
    }

    // find if needs to go on left or on right
    dest_face = face+1;
    if (dest_face ==5 ) dest_face =1;
    if (*(*(*(cube+dest_face)+1)+1) == bottom_color){   //needs to go on right
        side_name_rotation(cube, DOWN, 1, -1);
        side_name_rotation(cube, dest_face, 1, -1);
        side_name_rotation(cube, DOWN, 1, 1);
        side_name_rotation(cube, dest_face, 1, 1);
        side_name_rotation(cube, DOWN, 1, 1);
        side_name_rotation(cube, face, 1, 1);
        side_name_rotation(cube, DOWN, 1, -1);
        side_name_rotation(cube, face, 1, -1);
    }

    dest_face = face-1;
    if (dest_face == 0) dest_face =4;
    if (*(*(*(cube+dest_face)+1)+1) == bottom_color){   //needs to go on left
        side_name_rotation(cube, DOWN, 1, 1);
        side_name_rotation(cube, dest_face, 1, 1);
        side_name_rotation(cube, DOWN, 1, -1);
        side_name_rotation(cube, dest_face, 1, -1);
        side_name_rotation(cube, DOWN, 1, -1);
        side_name_rotation(cube, face, 1, -1);
        side_name_rotation(cube, DOWN, 1, 1);
        side_name_rotation(cube, face, 1, 1);
    }
}




int top_cross(int*** cube){
    //perfect top cross
    int face, final_dest_face, cross_completed=0, i, REP=0;
    T_SIDE adjface;
    T_COLOR adjcolor, cross_color;

    cross_color = *(*(*(cube+UP)+1)+1);

    while (!cross_completed){ 
        // turn faces to create cross
        for (face=1; face<5; face++){
              // if center piece is on middle layer (left)
            if (*(*(*(cube+face)+1)) == cross_color){
                // put piece on bottom layer of cube
                side_name_rotation(cube, face, 1, -1);
                side_name_rotation(cube, DOWN, 1, -1);
                side_name_rotation(cube, face, 1, 1);
                side_name_rotation(cube, DOWN, 1, 1);
                put_bottom_layer_center_piece_on_top_face(cube, face);
            }
            // if center piece is on middle layer (right)
            if (*(*(*(cube+face)+1)+2) == cross_color){
                side_name_rotation(cube, face, 1, 1);
                side_name_rotation(cube, DOWN, 1, -1);
                side_name_rotation(cube, face, 1, -1);
                side_name_rotation(cube, DOWN, 1, 1);
                put_bottom_layer_center_piece_on_top_face(cube, face);
            }
            // if center piece is on top layer
            if (*(*(*(cube+face))+1) == cross_color){
                side_name_rotation(cube, face, 2, 1);
                put_bottom_layer_center_piece_on_top_face(cube, face);
            }
            // if center piece is on bottom layer
            if (*(*(*(cube+face)+2)+1) == cross_color) {
                put_bottom_layer_center_piece_on_top_face(cube, face);
                }
            }


        // remove white pieces from bottom face if there are some
        for (i=0; i<3; i++, i++){
            if ( *(*(*(cube+DOWN)+i)+1) == cross_color){   // check vertical line
                if (i==0) side_name_rotation(cube, FRONT, 1, 1);
                if (i==2) side_name_rotation(cube, BACK, 1, 1);
            }
            if ( *(*(*(cube+DOWN)+1)+i) == cross_color){  // check horizontal line
                if (i==0) side_name_rotation(cube, LEFT, 1, 1);
                if (i==2) side_name_rotation(cube, RIGHT, 1, 1);
            }
        }
        
        // check if cross is completed and remove white cross square if they are misplaced
        cross_completed = 1;
        for (i=0; i<3; i++, i++){
            if ( *(*(*(cube+UP)+i)+1) == cross_color){   // check vertical line
                if (i==0)
                    if (*(*(*(cube+BACK))+1) != *(*(*(cube+BACK)+1)+1)){
                        cross_completed = 0;
                        side_name_rotation(cube, BACK, 1, 1);
                    } 
                if (i==2)
                    if (*(*(*(cube+FRONT))+1) != *(*(*(cube+FRONT)+1)+1)){
                    side_name_rotation(cube, FRONT, 1, 1);
                    cross_completed = 0;
                    }
            }else cross_completed = 0;
            if ( *(*(*(cube+UP)+1)+i) == cross_color){  // check horizontal line
                if (i==0)
                    if (*(*(*(cube+LEFT))+1) != *(*(*(cube+LEFT)+1)+1)) {
                        cross_completed = 0;
                        side_name_rotation(cube, LEFT, 1, 1);
                        }
                if (i==2)
                    if (*(*(*(cube+RIGHT))+1) != *(*(*(cube+RIGHT)+1)+1)) {
                        cross_completed = 0;
                        side_name_rotation(cube, RIGHT, 1, 1);
                        }
            }else cross_completed = 0;

        }
    REP++;
    if (REP>30) return 1;

    }
    return 0;
}

int top_corners(int *** cube){
    // This face puts the correct corners on top face and does the first layer
    int white_up_face_finished=0, face, i, cpt, REP=0;
    T_COLOR topcolor;
    T_SIDE adjface;


    topcolor = *(*(*(cube+UP)+1)+1);
    while (!white_up_face_finished){ 
        // turn side faces to mount up pieces onto top face
        for (face=1; face<5; face++){
            for (i=0; i<3; i++, i++){
                // if white square is top line
                if (*(*(*(cube+face))+i) == topcolor){
                     // top left
                    if (i==0){
                        side_name_rotation(cube, face, 1, -1);
                        side_name_rotation(cube, DOWN, 1, -1);
                        side_name_rotation(cube, face, 1, 1);
                        if (face == 1) put_bottom_layer_corner_piece_on_top_face(cube, BACK, 0);
                        else put_bottom_layer_corner_piece_on_top_face(cube, face-1, 0);
                        

                    }
                    // top right
                    if (i==2) {
                        side_name_rotation(cube, face, 1, 1);
                        side_name_rotation(cube, DOWN, 1, 1);
                        side_name_rotation(cube, face, 1, -1);
                        if (face == 4) put_bottom_layer_corner_piece_on_top_face(cube, LEFT, 1);
                        else put_bottom_layer_corner_piece_on_top_face(cube, face+1, 1);
                    }
                    }
                 // if white square is bottom line
                if (*(*(*(cube+face)+2)+i) == topcolor){
                    // bottom left
                    if (i==0) put_bottom_layer_corner_piece_on_top_face(cube, face, 0);
                    // bottom right
                    if (i==2) put_bottom_layer_corner_piece_on_top_face(cube, face, 1);
                }
            }
        }
        
        
        // remove white piece from down
        for (i=0; i<3; i++, i++){

            // if white square is top line
            if (*(*(*(cube+DOWN))+i) == topcolor){
                 // top left
                if (i==0){
                    if (*(*(*(cube)+2)) != topcolor){
                    side_name_rotation(cube, FRONT, 1, -1);
                    side_name_rotation(cube, DOWN, 1, 1);
                    side_name_rotation(cube, FRONT, 1, 1);
                    }
                    else side_name_rotation(cube, DOWN, 1, 1);
                    
                }
                // top right
                if (i==2) {
                    if (*(*(*(cube)+2)+2) != topcolor){
                    side_name_rotation(cube, FRONT, 1, 1);
                    side_name_rotation(cube, DOWN, 1, -1);
                    side_name_rotation(cube, FRONT, 1, -1);
                    }
                    else side_name_rotation(cube, DOWN, 1, 1);
                }
            }
            
            // if white square is bottom line
            if (*(*(*(cube+DOWN)+2)+i) == topcolor){
                // bottom left
                if (i==0) {
                    if (*(*(*(cube))) != topcolor){
                        side_name_rotation(cube, BACK, 1, 1);
                        side_name_rotation(cube, DOWN, 1, 1);
                        side_name_rotation(cube, BACK, 1, -1);
                    }
                    else side_name_rotation(cube, DOWN, 1, 1);
                }
                // bottom right
                if (i==2) {
                    if (*(*(*(cube))+2) != topcolor){
                        side_name_rotation(cube, BACK, 1, -1);
                        side_name_rotation(cube, DOWN, 1, 1);
                        side_name_rotation(cube, BACK, 1, 1);
                    }
                    else side_name_rotation(cube, DOWN, 1, 1);

                }
            }
        }


        // check if face is completed
        white_up_face_finished = 1;
        for (i=0; i<3; i++){
            for (cpt=0; cpt<3; cpt++){
                if (*(*(*(cube+UP)+i)+cpt) != topcolor) white_up_face_finished = 0;
            }
        }

        // check if first row of side faces is complete, and remove missplaced squares
        for (face=1; face<5; face++){
            for (i=0; i<3; i++){
                if (*(*(*(cube+face))+i) != *(*(*(cube+face)+1)+1)) {
                    white_up_face_finished = 0;
                    if (i==0){
                        adjface = face-1;
                        if (face==0) face=4;
                        side_name_rotation(cube, adjface, 1, 1);
                        side_name_rotation(cube, DOWN, 1, -1);
                        side_name_rotation(cube, adjface, 1, -1);
                    }
                    if (i==2){
                        adjface = face+1;
                        if (face==5) face=1;
                        side_name_rotation(cube, adjface, 1, -1);
                        side_name_rotation(cube, DOWN, 1, 1);
                        side_name_rotation(cube, adjface, 1, 1);
                    }
                }
            }
        }
    
    REP++;
    if (REP>30) return 1;
    
    
    }
    return 0;
}

int second_layer(int***cube){
    // makes the second layer
    int done=0, face, REP=0, i;
    T_COLOR adj_color, topcolor, bottomcolor;
    T_SIDE adj_face;

    topcolor = *(*(*(cube+UP)+1)+1);
    bottomcolor = *(*(*(cube+DOWN)+1)+1);
    while (!done){

        for (face=1; face<5; face++){

            // if square belongs to the second layer, mount it to second layer
            if (*(*(*(cube+face)+2)+1) != bottomcolor && get_adjacent_color_on_bottom(cube, face) != bottomcolor){
                mount_on_to_second_layer(cube, face);
            }

             // if square does not belong to second layer remove it from there
            for (i=0; i<3; i++){
                if (*(*(*(cube+face)+1)+i) != bottomcolor){   // if center corner piece is not yellow
                    if (i==0){  // if middle left
                        adj_face = face-1;
                        if (adj_face == 0) adj_face = 4;
                        adj_color = *(*(*(cube+adj_face)+1)+2);
                        if (adj_color != bottomcolor && *(*(*(cube+face)+1)+1) != *(*(*(cube+face)+1)+i) && adj_color != *(*(*(cube+adj_face)+1)+1)){
                            side_name_rotation(cube, adj_face, 1, 1);
                            side_name_rotation(cube, DOWN, 1, -1);
                            side_name_rotation(cube, adj_face, 1, -1);
                            side_name_rotation(cube, DOWN, 1, -1);
                            side_name_rotation(cube, face, 1, -1);
                            side_name_rotation(cube, DOWN, 1, 1);
                            side_name_rotation(cube, face, 1, 1);
                        }
                    }
                    if (i==2){  // if middle right
                        adj_face = face+1;
                        if (adj_face == 5) adj_face = 1;
                        adj_color = *(*(*(cube+adj_face)+1));
                        if (adj_color != bottomcolor && *(*(*(cube+face)+1)+1) != *(*(*(cube+face)+1)+i) && adj_color != *(*(*(cube+adj_face)+1)+1)){
                            side_name_rotation(cube, adj_face, 1, -1);
                            side_name_rotation(cube, DOWN, 1, 1);
                            side_name_rotation(cube, adj_face, 1, 1);
                            side_name_rotation(cube, DOWN, 1, 1);
                            side_name_rotation(cube, face, 1, 1);
                            side_name_rotation(cube, DOWN, 1, -1);
                            side_name_rotation(cube, face, 1, -1);
                        }
                    }

                }
            }
        
        }
        

        // check if done
        done=1;
        for (face=1; face<5; face++){
            for (i=0; i<3; i++, i++){
                if (*(*(*(cube+face)+1)+i) != *(*(*(cube+face)+1)+1)) done = 0;
            }
        }
        
        REP++;
        if (REP>30) return 1;


    }
    return 0;
}

int down_face(int***cube){
    // This function completes the bottom face of the cube in two steps
    // firstly the bottom cross, then the entire bottom face
    int done=0,stage=0, i, k, n_squares=0, REP=0;
    T_COLOR bottomcolor;

    bottomcolor = *(*(*(cube+DOWN)+1)+1);

    // check if cross is not already completed
    done = 1;
    for (k=0; k<3; k++){
        if (*(*(*(cube+DOWN)+k)+1) != bottomcolor) done = 0;
    }
    for (k=0; k<3; k++){
        if (*(*(*(cube+DOWN)+1)+k) != bottomcolor) done = 0;
    }
    
    // complete cross
    while (!done){
        stage = 0;
        
        // if yellow line stage = 1
            if (!stage){
                stage = 1;
            // check if there is a vertical line 
            for (i=0;i<3;i++){
                if (bottomcolor!=*(*(*(cube+DOWN)+i)+1)) stage = 0;
            }
            // check if there is a vertical line 
            if (!stage){
                stage = 1;
                for (i=0;i<3;i++){
                    if (bottomcolor!=*(*(*(cube+DOWN)+1)+i)) stage = 0;
                }
            }
            else side_name_rotation(cube, DOWN, 1, 1);  // rotate to get a horizontal line if it is vertical
            }

        // if angle stage = 2
            if (!stage){
                stage = 2;
                for (i=0; i<4; i++){
                    if (*(*(*(cube+DOWN)+1)+1) != bottomcolor || *(*(*(cube+DOWN)+1)) !=  bottomcolor || *(*(*(cube+DOWN))+1) != bottomcolor) stage = 0; 
                    else {i=6, stage = 2;}
                    if (stage != 2) side_name_rotation(cube, DOWN, 1, 1);  // rotate to check if it forms an angle from other POV
                }
            }

        // if only yellow center stage = 3
            if (!stage)stage =3;
        
        
        // do algorithm corresponding to stage
        switch(stage){
            case 3:
            case 2:{
                side_name_rotation(cube, FRONT, 1, 1);
                side_name_rotation(cube, DOWN, 1, 1);
                side_name_rotation(cube, LEFT, 1, 1);
                side_name_rotation(cube, DOWN, 1, -1);
                side_name_rotation(cube, LEFT, 1, -1);
                side_name_rotation(cube, FRONT, 1, -1);
                break;
            }
            case 1:{
                side_name_rotation(cube, FRONT, 1, 1);
                side_name_rotation(cube, LEFT, 1, 1);
                side_name_rotation(cube, DOWN, 1, 1);
                side_name_rotation(cube, LEFT, 1, -1);
                side_name_rotation(cube, DOWN, 1, -1);
                side_name_rotation(cube, FRONT, 1, -1);
                break;
            }
            
        }

        // check if face is complete
        done = 1;
        for (k=0; k<3; k++){
            if (*(*(*(cube+DOWN)+k)+1) != bottomcolor) done = 0;
        }
        for (k=0; k<3; k++){
            if (*(*(*(cube+DOWN)+1)+k) != bottomcolor) done = 0;
        }


        REP++;
        if (REP>30) return 1;
    }

    // check if face is complete
    done = 1;
    for (i=0; i<3; i++){
        for (k=0; k<3; k++){
            if (*(*(*(cube+DOWN)+i)+k) != bottomcolor) done = 0;
        }
    }

    // complete face
    REP=0;
    while (!done){
        n_squares = 0;
        // count number of yellow squares not belonging to cross
        for (i=0; i<3; i++, i++){
            if (*(*(*(cube+DOWN))+i) == bottomcolor) n_squares++; // top line
            if (*(*(*(cube+DOWN)+2)+i) == bottomcolor) n_squares++; // bottom line
        }

        // position cube correctly for algorithm to work
        if (n_squares==0){
            while (*(*(*(cube+LEFT)+2)) != bottomcolor) side_name_rotation(cube, DOWN, 1, 1);
        }
        if (n_squares==1){
            while (*(*(*(cube+DOWN)+2)) != bottomcolor) side_name_rotation(cube, DOWN, 1, 1);
        }
        if (n_squares>1){
            while (*(*(*(cube+BACK)+2)+2) != bottomcolor) side_name_rotation(cube, DOWN, 1, 1);
        }

        // rotation algo:
        side_name_rotation(cube, RIGHT, 1, 1);
        side_name_rotation(cube, DOWN, 1, 1);
        side_name_rotation(cube, RIGHT, 1, -1);
        side_name_rotation(cube, DOWN, 1, 1);
        side_name_rotation(cube, RIGHT, 1, 1);
        side_name_rotation(cube, DOWN, 1, 1);
        side_name_rotation(cube, DOWN, 1, 1);
        side_name_rotation(cube, RIGHT, 1, -1);

        done = 1;
        for (i=0; i<3; i++){
            for (k=0; k<3; k++){
                if (*(*(*(cube+DOWN)+i)+k) != bottomcolor) done = 0;
            }
        }
        REP++;
        if (REP>30) return 1;
        
    }

    return 0;
}

int down_corners(int***cube){
    // orients corners of the side faces to match their centers
    int done=0, i, k, cpt, face=1, REP=0;

    // check if corners are not already in place

    // find if two corners of one face match and orient in in correct position
        for (face=1; face<5; face++){
            if (*(*(*(cube+face)+2)) == *(*(*(cube+face)+2)+2)){
                break;
            }
        }
        while (*(*(*(cube+face)+2)+2) != *(*(*(cube+face)+1)+1)){
            side_name_rotation(cube, DOWN, 1, 1);
            face++;
            if (face >=5) face=1;
        }
    // Now the down face is correctly positioned and ready to check if corners are in correct place
    done=1;
    for(face=1; face<5; face++){
        if (*(*(*(cube+face)+2)+2) != *(*(*(cube+face)+2))) done=0;
    }

    while (!done){
        // position matching corners on back to perform algo
        for (face=1; face<5; face++){
            if (*(*(*(cube+face)+2)) == *(*(*(cube+face)+2)+2)){
                while (face!=BACK){
                    side_name_rotation(cube, DOWN, 1, 1);
                    face++;
                    if (face>=5) face=1;
                }
                break;
            }
        }
        
        // perform algo
        side_name_rotation(cube, LEFT, 1, -1);
        side_name_rotation(cube, FRONT, 1, 1);
        side_name_rotation(cube, LEFT, 1, -1);
        side_name_rotation(cube, BACK, 2, 1);
        side_name_rotation(cube, LEFT, 1, 1);
        side_name_rotation(cube, FRONT, 1, -1);
        side_name_rotation(cube, LEFT, 1, -1);
        side_name_rotation(cube, BACK, 2, 1);
        side_name_rotation(cube, LEFT, 2, 1);


         // check if corners are in place

        // orient in correct pos
        done=1;
        while (*(*(*(cube+1)+2)+2) != *(*(*(cube+1)+1)+1)){
            side_name_rotation(cube, DOWN, 1, 1);
        }
        
        // Now the down face is correctly positioned and ready to check if corners are in correct place
        for(face=1; face<5; face++){
            if (*(*(*(cube+face)+2)+2) != *(*(*(cube+face)+2))) done=0;
        }
        REP++;
        if (REP>30) return 1;
    }
    return 0;
}

int bottom_middle_pieces(int***cube){
    // last step, swap the middle bottom pieces of each face until the cube is solved
    int done=0, face, REP=0;
    // check if it is not already solved
    done = 1;
    for (face=1; face<5; face++){
        if (*(*(*(cube+face)+1)+1) != *(*(*(cube+face)+2)+1)) done=0;
    }

    while (!done){
        // put solved face on back
        for (face=1; face<5; face++){
            if (*(*(*(cube+face)+2)) == *(*(*(cube+face)+2)+1) && *(*(*(cube+face)+2)+1) == *(*(*(cube+face)+2)+2)){
                while (face!= BACK){
                    side_name_rotation(cube, DOWN, 1, 1);
                    face++;
                    if (face>=5) face=1;
                }
                break;
            }
        }
        

        //algo
        side_name_rotation(cube, FRONT, 2, 1);
        side_name_rotation(cube, DOWN, 1, -1);
        side_name_rotation(cube, LEFT, 1, -1);
        side_name_rotation(cube, RIGHT, 1, 1);
        side_name_rotation(cube, FRONT, 2, 1);
        side_name_rotation(cube, LEFT, 1, 1);
        side_name_rotation(cube, RIGHT, 1, -1);
        side_name_rotation(cube, DOWN, 1, -1);
        side_name_rotation(cube, FRONT, 2, 1);


        // check if done
        // put faces in correct position before checking:
        while (*(*(*(cube+1)+1)+1) != *(*(*(cube+1)+2)+2)) side_name_rotation(cube, DOWN, 1, 1);
        done = 1;
        for (face=1; face<5; face++){
            if (*(*(*(cube+face)+1)+1) != *(*(*(cube+face)+2)+1)) done=0;
        }
        REP++;
        if (REP>30) return 1;
    }
    return 0;
}



int solve_cube(int*** cube){
    // solve the cube using functions above and display cube and step name at each step
    if (top_cross(cube)) return 1;
    printf("\n AFTER CENTER CROSS CUBE : \n");
    display_rubiks(cube);
    if (top_corners(cube)) return 1;
    printf("\n AFTER FIRST LAYER CUBE : \n");
    display_rubiks(cube);
    if (second_layer(cube)) return 1;
    printf("\n AFTER SECOND LAYER CUBE : \n");
    display_rubiks(cube);
    if (down_face(cube)) return 1;
    printf("\n AFTER DOWN FACE CUBE : \n");
    display_rubiks(cube);
    if (down_corners(cube)) return 1;
    printf("\n AFTER DOWN CORNERS CUBE : \n");
    display_rubiks(cube);
    if (bottom_middle_pieces(cube)) return 1;
    return 0;
}

int solve_cube_time_test(int*** cube){
    // solve the cube without displaying anything (for efficiency)
    if (top_cross(cube)) return 1;
    if (top_corners(cube)) return 1;
    if (second_layer(cube)) return 1;
    if (down_face(cube)) return 1;
    if (down_corners(cube)) return 1;
    if (bottom_middle_pieces(cube)) return 1;
    return 0;
}

void solve_cube_n_times(int *** cube, long n){
    // solve the cube as much as many times as you want, time it, and display the average speed of algorithm
   int done=0, rep=0, total_moves = 0;
   clock_t start, finish;
   double  duration;
   n = n-2;


   // Measure the duration
   start = clock();
   while( !done ){
       cube_counter.n_rotation=0;
       shuffle_cube(cube, 50);
       if (solve_cube_time_test(cube) || rep>n) {
           finish = clock();
           shuffle_cube(cube, 50);
           solve_cube(cube);
           done=1;
           }
       rep++;
       total_moves += cube_counter.n_rotation;
   }
      
   
   duration = (double)(finish - start) / CLOCKS_PER_SEC;
   printf("\nCube was solved %d times in %2.3f seconds averaging at %f milli-seconds per solve\nTotal moves: %d     Average moves per solve: %d\n", rep, duration, 1000*(duration/rep), total_moves, total_moves/rep);
}