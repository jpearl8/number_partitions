#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


long flip();
long hillClimber(long A[], int max_iter);
long hillClimberPartKarp(long A[], int max_iter);
long karp(long arr[], long sArr[], bool p);
void randMemParts(int A_p_dest[], long A_pre[], long A_post[]);
void merge(long arr[], int l, int m, int r);
void mergeSort(long arr[], int l, int r);
long min (long A, long B);
double Tprob(int iter, long sum, long sum2);
void randNeighborParts(int A_p_dest[], long A_pre[], long A_post[]);
long randSol(long A[], bool abs);
void randSolPart(long A_pre[], long A_post[]);
long repeatedRandom(long A[], int max_iter);
long repeatedRandomPartKarp(long A[], int max_iter);
long repeatedRandomPartnoKarp(long A[], int max_iter);
long simAnneal(long A[], int max_iter);
long simAnnealPartKarp(long A[], int max_iter);
long sum (long A[]);

int size = 100;
int sArray = 98;
int max_iteration_val = 250000;

int main(int argc, char** argv) {
    srand(time(NULL));
    if (argc != 4) {
        printf("Usage: ./ee flag alg inputfile \n");
        return 1;
    }
    int flag = atoi(argv[1]);
    int alg = atoi(argv[2]);
    if (flag == 1 || flag == 2){
        //testing mode, rewrite input file
        for (int ttt = 0; ttt < 10; ttt++){ 
            // rewrite input file
            FILE *fptr;
            fptr = fopen("test.txt", "w");
            if (fptr == NULL) {
                printf("Error!");
                exit(1);
            }
            int a;
            for (int i = 0; i < 100; i++){
                a = rand() % 100000;
                fprintf(fptr, "%d\n", a);
            }  
            fclose(fptr);
        
            // read input file    
            FILE *input_file;
            long A[size];
            long sA[(size - 1)];
            input_file = fopen(argv[3], "r");
            if (input_file == 0)
            {
                perror("Canot open input file\n");
                exit(-1);
            }
            else
            {
                int counter = 0;
                char buf[20];
                int i = 0; 
                while (fgets(buf, sizeof buf, input_file)) {
                    char *p = buf;
                    char *q;
                    for (; i < size; i++) {
                        A[i] = strtol(p, &q, 0);
                        if (q == p) {
                            /* no more numbers */
                            break;
                        }
                        p = q;
                    }
                }
                if (i != size) {
                    perror("File too small");
                    exit(-1);
                }
            }
            fclose(input_file);
            // Sort A
            mergeSort(A, 0, (size - 1));
            // Print A
            // for (int j = 0; j < size; j++) {
            //     printf("%ld ", A[j]);
            // }
            // printf("\n");
            // Run all algorithms
            long A_1[size];
            long A_2[size];
            long A_3[size];
            long A_4[size];
            long A_5[size];
            long A_6[size];
            long A_7[size];
            memcpy(A_1, A, sizeof(A));
            memcpy(A_2, A, sizeof(A));
            memcpy(A_3, A, sizeof(A));
            memcpy(A_4, A, sizeof(A));
            memcpy(A_5, A, sizeof(A));
            memcpy(A_6, A, sizeof(A));
            memcpy(A_7, A, sizeof(A));
            
            if (flag == 2){
                clock_t start, end;
                double cpu_time_used;
                start = clock();
                karp(A_1, sA, true);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("%f \n", cpu_time_used);
                start = clock();
                repeatedRandom(A_2, max_iteration_val);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("%f \n", cpu_time_used);
                start = clock();
                hillClimber(A_3, max_iteration_val);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("%f \n", cpu_time_used);
                start = clock();
                simAnneal(A_4, max_iteration_val);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("%f \n", cpu_time_used);
                start = clock();
                repeatedRandomPartKarp(A_5, max_iteration_val);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("%f \n", cpu_time_used);
                start = clock();
                hillClimberPartKarp(A_6, max_iteration_val);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("%f \n", cpu_time_used);
                start = clock();
                simAnnealPartKarp(A_7, max_iteration_val);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("%f \n", cpu_time_used);
                printf("NEW\n");
            } else {
                printf("%ld \n", karp(A_1, sA, true));
                printf("%ld \n", repeatedRandom(A_2, max_iteration_val)); 
                printf("%ld \n", hillClimber(A_3, max_iteration_val));
                printf("%ld \n", simAnneal(A_4, max_iteration_val));
                printf("%ld \n", repeatedRandomPartKarp(A_5, max_iteration_val)); 
                printf("%ld \n", hillClimberPartKarp(A_6, max_iteration_val));
                printf("%ld \n", simAnnealPartKarp(A_7, max_iteration_val));
                printf("NEW\n");
            }

        }
    } else if (flag == 0){
        // read input file    
        FILE *input_file;
        long A[size];
        long sA[(size - 1)];
        input_file = fopen(argv[3], "r");
        if (input_file == 0)
        {
            perror("Canot open input file\n");
            exit(-1);
        }
        else
        {
            int counter = 0;
            char buf[20];
            int i = 0; 
            while (fgets(buf, sizeof buf, input_file)) {
                char *p = buf;
                char *q;
                for (; i < size; i++) {
                    A[i] = strtol(p, &q, 0);
                    if (q == p) {
                        /* no more numbers */
                        break;
                    }
                    p = q;
                }
            }
            if (i != size) {
                perror("File too small");
                exit(-1);
            }
        }
        fclose(input_file);
        // Sort A
        mergeSort(A, 0, (size - 1));
        switch(alg) {

            case 0:
                printf("%ld \n", karp(A, sA, true));
                break; 
                
            case 1:
                printf("%ld \n", repeatedRandom(A, max_iteration_val)); 
                break; 
            
            case 2:
                printf("%ld \n", hillClimber(A, max_iteration_val));
                break; 
                
            case 3:
                printf("%ld \n", simAnneal(A, max_iteration_val));
                break; 
            
            case 11:
                printf("%ld \n", repeatedRandomPartKarp(A, max_iteration_val));
                break;

            case 12:
                printf("%ld \n", hillClimberPartKarp(A, max_iteration_val));
                break;

            case 13:
                printf("%ld \n", simAnnealPartKarp(A, max_iteration_val));
                break;
            
            /* you can have any number of case statements */
            default :
                printf("Please enter valid algorithm code\n"); 
                break;
        }   
    }
    return 0;
}

/*
Simmulated Annealing (PARTITIONED):
Takes in parameters A and max iteration.
Start with a random partition (randMemParts helper function) and run through Karmarkar-Karp
and checks neighbors of partitioned random solution (randNeighborsParts helper function)
Proceeds to check neighbor's neighbors if neighbor has lower residue OR or if we roll a heads from our Tprob function (helper Tprob).
Returns the lowest residue it encounters
*/
long simAnnealPartKarp(long A[], int max_iter) {
    bool testing = false;
    long A_post[size];
    long A_post_2[size];
    int A_p_dest[size];
    int A_p_dest_2[size];
    memset(A_post, 0, size * sizeof(long));
    // Random Partition
    randMemParts(A_p_dest, A, A_post);
    memcpy(A_post_2, A_post, sizeof(A_post));
    memcpy(A_p_dest_2, A_p_dest, sizeof(A_p_dest));
    long sA[(size - 1)];
    memset(sA, 0, (size - 1) * sizeof(long));
    // Running Random partition through Karmarker Karp
    long low = karp(A_post, sA, testing);
    long lowest = low;
    long low2 = low;
    for (int i = 0; i < max_iter; i++) {
        // If we've found a low of 0, stop looking
        if (low != 0) {
            // Get a random neighbor of solution & run karmarker karp
            randNeighborParts(A_p_dest_2, A, A_post_2);
            memset(sA, 0, (size - 1) * sizeof(long));
            low2 = karp(A_post_2, sA, testing);
            double j = ((double) rand() / (RAND_MAX));
            double tprob = Tprob(i, labs(low), labs(low2));
            // If we've found lower residue or we've rolled a heads from our Tprob function, pursue neighbor
            if (low2 < low || j < tprob){
                low = low2;
                // copy A_post 2 into A post 1 and A dest 2 into A dest 1
                memcpy(A_post, A_post_2, sizeof(A_post_2));
                memcpy(A_p_dest, A_p_dest_2, sizeof(A_p_dest_2));
                
            } else {
                low2 = low;
                // copy A_post 1 into A post 2 and A dest 1 into A dest 2
                memcpy(A_post_2, A_post, sizeof(A_post));
                memcpy(A_p_dest_2, A_p_dest, sizeof(A_p_dest));
            } 
            // Record lowest residue we've encountered
            if (low < lowest){
                lowest = low;
            }

        } else {
            break;
        }
    }
    // printf("%ld\n", lowest);
    // printf("Sim anneal: (part): %ld\n", lowest);
    return lowest;
}

/*
Hill Climber (PARTITIONED):
Takes in parameters A and max iteration.
Start with a random partition (randMemParts helper function) and run through Karmarkar-Karp
and checks neighbors of partitioned random solution (randNeighborsParts helper function)
Proceeds to check neighbor's neighbors if neighbor has lower residue.
Returns the lowest residue it encounters
*/
long hillClimberPartKarp(long A[], int max_iter) {
    bool testing = false;
    long A_post[size];
    long A_post_2[size];
    // Destination array to hold specific partitions
    int A_p_dest[size];
    int A_p_dest_2[size];
    memset(A_post, 0, size * sizeof(long));
    // Random partitions assigned and saved
    randMemParts(A_p_dest, A, A_post);
    long sA[(size - 1)];
    memset(sA, 0, (size - 1) * sizeof(long));
    // Run Karp to calculate residue
    long low = karp(A_post, sA, testing);
    long low2 = low;
    memcpy(A_post_2, A_post, sizeof(A_post));
    memcpy(A_p_dest_2, A_p_dest, sizeof(A_p_dest));
    for (int i = 0; i < max_iter; i++) {
        // If we've encountered a low of 0, stop
        if (low != 0) {
            // Check neighbors of lowest partitions
            randNeighborParts(A_p_dest_2, A, A_post_2);
            memset(sA, 0, (size - 1) * sizeof(long));
            low2 = karp(A_post_2, sA, testing);
            // If neighbor is lower, find neighbor's neighbors
            if (low2 < low){
                memcpy(A_post, A_post_2, sizeof(A_post_2));
                memcpy(A_p_dest, A_p_dest_2, sizeof(A_p_dest_2));
                low = low2;
            } else {
                low2 = low;
                memcpy(A_post_2, A_post, sizeof(A_post));
                memcpy(A_p_dest_2, A_p_dest, sizeof(A_p_dest));
            }
        } else {
            break;
        }
    }
    // printf("Hill climber: (part): %ld\n", low);
    return low;
}

/*
Rand Neighbor Partitions
Finds neighbors of partitioned random solution 
Takes in partition array, pre partitioned array, and post partitioned array
Picks a random index in partition array,
picks a value of a partition not stored at that index,
subtracts pre partitioned value from old post partitioned index, 
and adds the pre partitioned value to a new partitioned index.
*/
void randNeighborParts(int A_p_dest[], long A_pre[], long A_post[]) {
    // Pick random index
    int i = rand() % 100;
    // Pick random partition value, make sure it's not the value already stored at that index
    int j = A_p_dest[i];
    while (A_p_dest[i] == j){
        j = rand() % 100;
    }
    // Subtract value from old partition
    A_post[A_p_dest[i]] -= A_pre[i];
    // Add value to new partition
    A_post[j] += A_pre[i];
    // Update partition
    A_p_dest[i] = j;

}

/*
Random Memorized Partitions
Generate random partitions, 
Stored pre values in post partitions.
Update partitions and post partitioned array.
*/
void randMemParts(int A_p_dest[], long A_pre[], long A_post[]){
    for (int i = 0; i < size; i++){
        A_p_dest[i] = rand() % 100;
    }
    for (int i = 0; i < size; i++){
        A_post[A_p_dest[i]] += A_pre[i];
    }
}

/* Repeated Random (PARTITIONED):
    Creates random partitions (randSolPart helper function) and runs through Karmarkar-Karp
    Returns lowest residual found
*/
long repeatedRandomPartKarp(long A[], int max_iter) {
    bool testing = false;
    long A_post[size];
    memset(A_post, 0, size * sizeof(long));
    // Creates empty array A_post and puts partitioned A into A_post 
    randSolPart(A, A_post);
    long sA[(size - 1)];
    memset(sA, 0, (size - 1) * sizeof(long));
    // Run Karmarker Karp on partitioned A (A_post)
    long low = karp(A_post, sA, testing);
    long low2 = low;
    for (int i = 0; i < max_iter; i++) {
        // If we've found a low of 0, stop
        if (low != 0) {
            // Clear partitioned array and find new random partitioning
            memset(A_post, 0, size * sizeof(long));
            randSolPart(A, A_post);
            memset(sA, 0, (size - 1) * sizeof(long));
            // Runs Karmarker Karp on partitioned A (A_post)
            low2 = karp(A_post, sA, testing);
            // Save lowest value we've found
            low = min(low, low2);
        } else {
            break;
        }
    }
    // printf("Repeated Random (part): %ld\n", low);
    return low;
}


/*
random partitioned solution:
Place elements from A into random indices in A_post
(only used for Partitioned Repeated Random)
*/
void randSolPart(long A_pre[], long A_post[]){
    int r;
    for (int i = 0; i < size; i++){
        r = rand() % 100;
        A_post[r] += A_pre[i];
    }
}

/* Simulated Annealing (Unpartitioned):
Take in A and max iterations as parameters.
Starts with a random solution (helper function randSol) 
and checks neighbors of random solution
If the neighbor has a lower residue or if we roll a heads from our Tprob function (helper Tprob), we save the neighbor. 
Returns the lowest residue it encounters
*/
long simAnneal(long A[], int max_iter) {
    long low = randSol(A, false);
    long lowest = low;
    long low2 = low;
    int a, b;
    for (int i = 0; i < max_iter; i++) {
        // If we've found a low of 0, stop
        if (lowest != 0){
            // Find a random neighbor
            a = rand() % size;
            b = a;
            while (a == b) {
                b = rand() % size;
            }
            // 1 or 2 elements switched with 1/2 probability
            low2 += A[a]*-2;
            int f = flip();
            if (f == -1){
                low2 += A[b]*-2;
            }
            //Generate a random number 0-1 and check if it's less than Tprob
            double j = ((double) rand() / (RAND_MAX));
            double tprob = Tprob(i, labs(low), labs(low2));
            // Save neighbor's value and prepare to look at neighbor's neighbors
            if (labs(low2) < labs(low) || j < tprob){
                A[a] = -1*A[a];
                A[b] = f*A[b];
                low = low2;
            } else {
                low2 = low;
            }
            // If we encounter the lowest residue we've seen, save it
            if (labs(low) < labs(lowest)){
                lowest = low;
            }
        } else {
            break;
        }
        
    }
    //return the lowest residue we've seen
    lowest = labs(lowest);
    // printf("sim Anneal (unp): %ld\n", lowest);
    return lowest;
}

/* Tprob function
T(iter) = 10^10 * (0.8)^(floor(iter / 300))
solution = exp(residue of 1 - residue of 2)/T(iter)
return solution
*/
double Tprob(int iter, long sum, long sum2) {
    double val = (floor((double)iter/300));
    double t = pow(10, 10) * pow(0.8, val);
    double sol = exp(((double)sum - sum2)/t);
    return sol;
}


/* 
Hill Climber (Unpartitioned):
Takes in array A and max iteration as parameters
Starts with a random solution (helper function randSol) 
and checks neighbors of random solution.
Proceeds to check neighbor's neighbors if neighbor has lower residue.
Returns the lowest residue it encounters
*/
long hillClimber(long A[], int max_iter) {
    long low = randSol(A, false);
    long low2 = low;
    int a, b;
    for (int i = 0; i < max_iter; i++) {
        // If we've found a low of 0, stop
        if (low != 0) {
            // Picks random (unequal) a and b values
            a = rand() % size;
            b = a;
            while (a == b) {
                b = rand() % size;
            }
            // Changes set (+1, -1) of index a
            low2 += A[a]*-2;
            // Changes set (+1, -1) of index b with probability 1/2
            int f = flip();
            if (f == -1){
                low2 += A[b]*-2;
            }
            // If the neighbor is lowest, save neighbor's value and prepare to look at neighbor's neighbors
            if (labs(low2) < labs(low)){
                A[a] = -1*A[a];
                A[b] = f*A[b];
                low = low2;
            } else {
                low2 = low;
            }
        } else {
            break;
        }
    }
    low = labs(low);
    // printf("Hill Climber (unp): %ld\n", low);
    return low;
}

/*
Repeated Random (Unpartitioned):
Takes in A and max iteration as parameters
Checks residue of random solutions (calculated in randSol)
Returns smallest
*/

long repeatedRandom(long A[], int max_iter) {
    long low = labs(sum(A));
    for (int i = 0; i < max_iter; i++) {
        // If we've found a low of 0, stop
        if (low != 0) {
            //Compare new random to old random, and save the smallest residue
            long b = randSol(A, true);
            low = min(low, b);
        } else {
            break;
        }
    }
    // printf("Repeated Random (unp): %ld\n", low);
    return low;
}

/*
Random Solution (Unpartitioned):
For each element, multiplies by 1 or -1 with 1/2 probability (helper function flip)
Returns residue of solution aka the SUM (helper function sum)
If abs it true, return the absolute value of the residue
*/
long randSol(long A[], bool abs) {
    for (int i = 0; i < size; i++) {
        A[i] = flip()*A[i];      
    }
    if (abs) {
        return labs((sum(A)));
    } else {
        return (sum(A));
    }   
}

/*Karmarker Karp
Takes in sorted array A and empty array for subtraction
Takes in boolean for print statement
*/
long karp(long arr[], long sArr[], bool p) {
    int i = 0;
    int si = 0;
    int insert = 0;
    // inserts difference between A's elements in subtraction array
    while (i < size) {
            sArr[insert] = labs(arr[i] - arr[i + 1]);
            insert++;
            i += 2;
    }
    // inserts difference between subtraction's elements into end of subtraction array
    while (si < 98) {
        sArr[insert] = labs(sArr[si] - sArr[si + 1]);
        insert++;
        si += 2;
    }
    if (p) {
        // printf("%ld \n", sArr[98]);  
        // printf("karpy: %ld \n", sArr[98]);  
    }
    return sArr[98];

}

/*
Sums an entire array, returns solution
*/
long sum (long A[]) {
    long s = 0;
    for (int i = 0; i < size; i++) {
        s += A[i];
    }
    return s;
}

/*
Returns min of 2 longs
*/
long min (long A, long B) {
    if (A > B) {
        return B;
    } else {
        return A;
    }
}

/*
Returns 1 or -1 with 1/2 probability
*/
long flip() {
    int f = rand() % 2;
    if (f == 0) {
        f = -1;
    } else { 
        f = 1;
    }
    return f;
}

/* MergeSort
Performs mergesort on an array with left index l and right index r
Uses Merge as helper function
*/
void mergeSort(long arr[], int l, int r) { 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
        merge(arr, l, m, r); 
    } 
} 

void merge(long arr[], int l, int m, int r) { 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    long L[n1], R[n2]; 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0;  
    j = 0; 
    k = l;  
    while (i < n1 && j < n2) 
    { 
        if (L[i] >= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
