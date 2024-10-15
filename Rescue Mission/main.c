//
//  main.c
//  RescueMission
//
//  Created by Eswanth Sriram Chengalasetty on 1/30/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function prototype
int guess(int average);

// main function
int main(int argc, const char * argv[]) {
    // initialize all variables
    int max_pos;
    int max_speed;
    int time = 1;
    int position = 0;
    int speed = 1;
    int cur_pos = 2;
    int possibility = 3;
    int total = 0;
    
    // scan the max speed and position
    scanf("%d%d", &max_speed, &max_pos);
    
    // declare and initialize the 2D array with values
    int possible_boats[4][(max_pos + 1) * (max_speed + 1)];
    int j = 0;
    
    for (int i = 0; i < max_pos + 1; i++) {
        for (int k = 0; k < max_speed + 1; k++) {
            possible_boats[speed][j + 1] = k;
            possible_boats[position][j + 1] = i;
            possible_boats[possibility][j + 1] = 1;
            possible_boats[cur_pos][j + 1] = possible_boats[position][j + 1] + (time * possible_boats[speed][j + 1]);
            total += possible_boats[cur_pos][j + 1];
            j++;
        }
    }
    
    // count how many possible boats are valid
    j = 0;
    int possible = 0;
    for (int i = 0; i < max_pos + 1; i++) {
        for (int k = 0; k < max_speed + 1; k++) {
            if (possible_boats[possibility][j + 1] == 1) {
                possible++;
                j++;
            }
        }
    }
        
    // find average and call guess function
    int midpoint = total / possible;
    int choice = guess(midpoint);
    int found = 0;
    j = 0;
    
    // binary searchish for first time to eliminate
    if (choice == 1) {
        for (int i = 0; i < max_pos + 1; i++) {
            for (int k = 0; k < max_speed + 1; k++) {
                if (possible_boats[cur_pos][j + 1] <= midpoint) {
                    possible_boats[possibility][j + 1] = 0;
                }
                j++;
            }
        }
    }
    
    else if (choice == 2) {
        for (int i = 0; i < max_pos + 1; i++) {
            for (int k = 0; k < max_speed + 1; k++) {
                if (possible_boats[cur_pos][j + 1] >= midpoint) {
                    possible_boats[possibility][j + 1] = 0;
                }
                j++;
            }
        }
    }
    
    else if (choice == 3) {
        for (int i = 0; i < max_pos + 1; i++) {
            for (int k = 0; k < max_speed + 1; k++) {
                if (possible_boats[cur_pos][j + 1] != midpoint) {
                    possible_boats[possibility][j + 1] = 0;
                }
                j++;
            }
        }
    }

    possible = 0;
    j = 0;
    
    // while loop to execute until boat is found
    while (found != 1) {
        total = 0;
        j = 0;
        possible = 0;
        time++;
        
        // count how many possible boats are valid
        for (int i = 0; i < max_pos + 1; i++) {
            for (int k = 0; k < max_speed + 1; k++) {
                if (possible_boats[possibility][j + 1] == 1) {
                    possible++;
                }
                j++;
            }
        }
        
        // send rescue team if boat is known
        if (possible == 1) {
            j = 0;
            
            for (int i = 0; i < max_pos + 1; i++) {
                for (int k = 0; k < max_speed + 1; k++) {
                    if (possible_boats[possibility][j + 1] == 1) {
                        possible_boats[cur_pos][j + 1] = possible_boats[position][j + 1] + (time * possible_boats[speed][j + 1]);
                        printf("! %d\n", possible_boats[cur_pos][j + 1]);
                        fflush(stdout);
                    }
                    j++;
                }
            }
            found = 1;
            return 0;
        }
        
        j = 0;
        
        // recalculate current position of all valid possible boats
        for (int i = 0; i < max_pos + 1; i++) {
            for (int k = 0; k < max_speed + 1; k++) {
                if (possible_boats[possibility][j + 1] == 1) {
                    possible_boats[cur_pos][j + 1] = possible_boats[position][j + 1] + (time * possible_boats[speed][j + 1]);
                    total += possible_boats[cur_pos][j + 1];
                }
                j++;
            }
        }
        
        // find average and call guess function
        midpoint = total / possible;
        choice = guess(midpoint);
        j = 0;
        
        // binary searchish unitl only one possible boat
        if (choice == 1) {
            for (int i = 0; i < max_pos + 1; i++) {
                for (int k = 0; k < max_speed + 1; k++) {
                    if (possible_boats[cur_pos][j + 1] <= midpoint) {
                        possible_boats[possibility][j + 1] = 0;
                    }
                    j++;
                }
            }
        }
        
        else if (choice == 2) {
            for (int i = 0; i < max_pos + 1; i++) {
                for (int k = 0; k < max_speed + 1; k++) {
                    if (possible_boats[cur_pos][j + 1] >= midpoint) {
                        possible_boats[possibility][j + 1] = 0;
                    }
                    j++;
                }
            }
        }
        
        else if (choice == 3) {
            for (int i = 0; i < max_pos + 1; i++) {
                for (int k = 0; k < max_speed + 1; k++) {
                    if (possible_boats[cur_pos][j + 1] != midpoint) {
                        possible_boats[possibility][j + 1] = 0;
                    }
                    j++;
                }
            }
        }
        
    }
        
    return 0;
}
    

// guess function to print ? _ to the screen and read input
int guess(int average) {
    printf("? %d\n", average);
    fflush(stdout);
    
    char reply[8];
        
    scanf("%s/n", reply);
    
    if (strcmp(reply, "Wake") == 0) {
        return 1;
    }
        
    else if (strcmp(reply, "Boat!") == 0) {
        return 3;
    }
        
    else {
        scanf("%s", reply);
        return 2;
    }
}
