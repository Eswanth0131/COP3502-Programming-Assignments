//
//  main.c
//  EngineShutDown
//
//  Created by Eswanth Sriram Chengalasetty on 2/8/23.
//
// This program generates all permutations of the values 1 to N

// Include
#include <stdio.h>

// The value in the permutation for values that have not been set yet
#define GARBAGE -1

int ans = 2147483647;

// The brute force permutation generator
void permute(int * used, int * perm, int index, int N, int after[N][N], int * actions, int * bestOrder)
{
    int tempChange = 0;
    
    // Check if the index is invalid
    if (N == index) {
        // for loop to perform each temperatue net change
        for (int i = 0; i < N; i++) {
            if (i == 0) {
                tempChange += actions[perm[i]];
            }
            if (i > 0) {
                tempChange += actions[perm[i]];
                for (int j = 0; j < i; j++) {
                    tempChange += after[perm[i]][perm[j]];
                }
            
            }
            
        }
        // updates ans if tempChange is best
        if (tempChange < ans){
            ans = tempChange;
            for (int i = 0; i < N; i++)
                // updates best order
                bestOrder[i] = perm[i] + 1;
        }
        else {
            return; // prevent calling recursively
        }
    }
    
    // Alternatively loop over index
    for (int curValue = 0;
         curValue < N;
         curValue++)
    {
        // Check if the value is not allowed
        if (used[curValue]) continue; // skip
        
        // Use the value
        used[curValue] = 1;
        perm[index] = curValue;

        // Recurse
        permute(used, perm, index + 1, N, after, actions, bestOrder);
    
        // Unuse the value
        used[curValue] = 0;
        perm[index] = GARBAGE; // not required
    }
}

// The value N


// The main function
int main() {
    int size = 0;
    // creating an array to store best order of actions
    int bestOrder[size];
    // reading in size
    scanf("%d", &size);
    // making an array and 2d array to store changes
    int actions[size];
    int afterActions[size][size];
    
    for (int i = 0; i < size; i++) {
        scanf("%d", &actions[i]);
    }
    
    
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++){
            scanf("%d", &afterActions[i][j]);
        }
    }
    
    int used[size]; // 0 or 1 representing which values have been used
    int perm[size]; // The array to hold the values in the permutation
    
    // Initialize the array
    for (int i = 0; i < size; i++) {
        used[i] = 0;
        perm[i] = GARBAGE; // not necessary
    }
    
    // Recurse through all the permutations
    permute(used, perm, 0, size, afterActions, actions, bestOrder);
    
    for (int i = 0; i < size; i++) {
        printf("%d ", bestOrder[i]);
    }
    printf("\n");
    // Exit
    return 0;
}
