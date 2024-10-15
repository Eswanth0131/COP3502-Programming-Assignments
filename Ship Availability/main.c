// include libraries
#include <stdio.h>
#include <string.h>

// define constants
#define MAX_LINE_NUMBER 100
#define MAX_NAME_LENGTH 20
#define MAX_SHIP_NUMBER 100

// main function
int main()
{
    // declare necessary variables and 3D array
    int shipLines = 0;
    int customers = 0;
    char names[MAX_LINE_NUMBER][MAX_LINE_NUMBER][MAX_NAME_LENGTH + 1];
    
    // storing number of ship lines from input
    scanf("%d\n", &shipLines);
    
    char line[shipLines * MAX_SHIP_NUMBER * MAX_NAME_LENGTH + (100 * shipLines)];
    
    int numOfShips[shipLines];
    
    int line_ind = 0;
    int char_ind = 0;
    int ship_ind = 0;
    
    // read input from user for ship names in ship lines using a for loop
    for (int i = 0; i < shipLines; i ++){
        
        fgets(line, (shipLines * MAX_SHIP_NUMBER * MAX_NAME_LENGTH + (100 * shipLines)), stdin);
        long lineLength = strlen(line);
        
        for (int j = 0; j < lineLength; j++) {
            if (line[j] == ' ') {
                // end the current ship name
                names[line_ind][ship_ind][char_ind] = '\0';
                
                // move to the start of the next ship name
                ship_ind++;
                char_ind = 0;
            }
            else if (line[j] == '\n') {
                // end of current ship name
                names[line_ind][ship_ind][char_ind] = '\0';
                
                // store number of ships in current line in numOfShips int array
                ship_ind++;
                numOfShips[i] = ship_ind;
                //printf("I got here %d %d\n", numOfShips[i], i);
                
                // move to the start of the next ship line
                line_ind++;
                char_ind = 0;
                ship_ind = 0;
            }
            else {
                // valid character of a ship name
                names[line_ind][ship_ind][char_ind] = line[j];
                
                //move to the next charcater of the current ship name
                char_ind++;
            }
        }
    }
    
    line_ind = 0;
    
    // storing number of customers from input
    scanf("%d", &customers);
    int week = 0;
    int weeksShip = 0;
    
    // read input from user and print the desired week's available ships using a loop with method calls
    for (int i = 0; i < customers; i++) {
        scanf("%d", &week);
        week--;
        for (int j = 0; j < shipLines; j++) {
            weeksShip = week % numOfShips[j];
            //printf("%d %d %d\n", weeksShip, numOfShips[j], j);
            
            printf("%s ", names[line_ind][weeksShip]);
            line_ind++;
        }
        printf("\n");
        line_ind = 0;
    }
    
    return 0;
}
