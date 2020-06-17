#include <stdio.h>
// CMPE 312 FINAL PROJECT
// BANKER'S ALGORITHM
// BURAK GULER, 11575012
// RASIT DENIZ CANSEVER, 112200022

/*
1st Question:

The Banker algorithm, sometimes referred to as the detection algorithm, is a resource allocation and deadlock avoidance algorithm 
developed by Edsger Dijkstra that tests for safety by simulating the allocation of predetermined maximum possible amounts of all resources,
and then makes an "s-state" check to test for possible deadlock conditions for all other pending activities, before deciding whether allocation
should be allowed to continue. 

It is modeled on the way a small town banker might deal with customers' lines of credit. 
In the course of conducting business, our banker would naturally observe that customers rarely draw their credit lines to their limits.
This, of course, suggests the idea of extending more credit than the amount the banker actually has in her coffers.
*/
 
int main() 
{ 
    
    int n = 5; // Number of processes named P0, P1, P2, P3, P4
    int m = 3; // Number of resources that respectively have 16, 17 and 15 instances.
    
    int alloc[5][3] = { { 1, 2, 1 }, // P0     Allocation Matrix for Banker algorithm:
                        { 5, 4, 5 }, // P1      2d array of size n*m for defining the number of resources
                        { 2, 0, 6 }, // P2      of each type currently allocated to each process
                        { 5, 4, 2 }, // P3      Ex: alloc[1][0] means P1 is allocated 0 instances of resource1 currently.
                        { 1, 3, 0 } }; // P4 
  
    int max[5][3] = { { 7, 5, 2 }, // P0     Max Matrix for Banker algorithm: 
                      { 8, 5, 6 }, // P1      2d array of size n*m for defining the maximum request of
                      { 4, 1, 6 }, // P2      each process.
                      { 6, 9, 8 }, // P3      Ex: max[0][3] means P0 is able to request at most 3 instances of resource3.
                      { 5, 3, 4 } }; // P4 
  
    int avail[3] = { 2, 4, 1}; // Available Resources: 1d array of size m declaring the number of available resources of each one.
                                // Ex: avail[1] means that there are 3 instances available for resource2.

    int f[n], ans[n], ind = 0; // f[n] declares the status of processes if they're done or not.
                               // ans[n] declares process n is ready to enter into the sequence (i.e need[i][j] < avail[j])
                                // ind means index, to call the processes in the loop.
                                
    for (int k = 0; k < n; k++) { 
        f[k] = 0; // all processes need to be executed, the status is false for all of them.
    } 
    
    int need[n][m]; // 2d array of size n*m that indicates the remaining resource need of each process.
                    //Ex: need[5][2] means P4 needs 1 instance of resource3.
                    // Because need[i][j] = max[i][j] - alloc[i][j]
    
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) 
            need[i][j] = max[i][j] - alloc[i][j]; // initializing need matrix
    } 
    
    int y = 0; 
    for (int k = 0; k < 5; k++) { 
        for (int i = 0; i < n; i++) { 
            if (f[i] == 0) { // if the process i is not finished.
  
                int flag = 0; // variable to decide if process will be enter to sequence or not.
                for (int j = 0; j < m; j++) { // loop to compare the needs of each processes and the availability of resources
                    if (need[i][j] > avail[j]){ // if need > available the process cannot enter to the Sequence
                                                // because there is no instance enough to satisfy its needs. It waits for now.
                        flag = 1; // prevents the process to enter the sequence and complete it.
                         break; 
                    } 
                } 
  
                if (flag == 0) { // if this satisfies, the process can complete its needs and enter to the sequence.
                    ans[ind++] = i; // means this process is in sequence in safe state.
                    for (y = 0; y < m; y++) 
                        avail[y] += alloc[i][y]; // since the process i is done, its allocation gets free and there are
                    f[i] = 1;       // more instances of resources available. This helps waiting processes to satisfy their needs.
                } 
            } 
        } 
    } 
  
    printf("Here is the safe sequence with Banker's Algorithm\n"); // all process are complete in order.
    for (int i = 0; i < n - 1; i++) // prints the processes with respect to their order in the Sequence.
        printf(" P%d ->", ans[i]);  // i.e the completion order of the processes
    printf(" P%d", ans[n - 1]);
    printf(" \n");
    for(int i = 0; i<m; i++){
        printf(" R%d",i);
        printf(": %d instances",avail[i]); //it proves that our program runs correct.
        printf(" \n"); // i.e total instances are equal to available instances in the end.
    }
  
    return (0); 

// BURAK GULER, 11575012
// RASIT DENIZ CANSEVER, 112200022
} 