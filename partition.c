#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

long flip();
long hillClimber(long A[], int max_iter);
int karp(long arr[], long sArr[]);
void merge(long arr[], int l, int m, int r);
void mergeSort(long arr[], int l, int r);
long min (long A, long B);
double Tprob(int iter, long sum, long sum2);
long randSol(long A[], bool abs);
void randSolPart(long A_pre[], long A_post[]);
long repeatedRandom(long A[], int max_iter);
long repeatedRandomPart(long A[], int max_iter);
long simAnneal(long A[], int max_iter);
long sum (long A[]);

int size = 100;

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Usage: ./ee flag alg inputfile \n");
        return 1;
    }
    int flag = atoi(argv[1]);
    int alg = atoi(argv[2]);

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
    srand(time(NULL));
    mergeSort(A, 0, (size - 1));
    for (int j = 0; j < size; j++) {
        printf("%ld ", A[j]);
    }
    printf("\n");
    long A_1[size];
    long A_2[size];
    long A_3[size];
    long A_4[size];
    long A_5[size];
    memcpy(A_1, A, sizeof(A));
    memcpy(A_2, A, sizeof(A));
    memcpy(A_3, A, sizeof(A));
    memcpy(A_4, A, sizeof(A));
    memcpy(A_5, A, sizeof(A));
    karp(A_1, sA);
    repeatedRandom(A_2, 25000); 
    hillClimber(A_3, 25000);
    simAnneal(A_4, 25000);
    repeatedRandomPart(A_5, 25000); 
    return 0;
}

int karp(long arr[], long sArr[]) {
    int i = 0;
    int si = 0;
    int insert = 0;
    while (i < size) {
            sArr[insert] = labs(arr[i] - arr[i + 1]);
            insert++;
            i += 2;
    }
    while (si < 98) {
        sArr[insert] = labs(sArr[si] - sArr[si + 1]);
        insert++;
        si += 2;
    }
    printf("karpy: %ld \n", sArr[98]);
    return 0;

}

long simAnneal(long A[], int max_iter) {
    srand(time(NULL));
    long low = randSol(A, false);
    long lowest = low;
    // printf("starting: %ld\n", low);
    long low2 = low;
    int a, b;
    for (int i = 0; i < max_iter; i++) {
        a = rand() % size;
        b = a;
        while (a == b) {
            b = rand() % size;
        }
        int f = flip();
        low2 += A[a]*-2;
        if (f == -1){
            low2 += A[b]*-2;
        }
        // printf("changing %d and %d change %d to result in new sum %lu \n", a, b, f, labs(low2));
        // printf("comparing %lu and %lu \n", labs(low2), labs(low));

        double j = ((double) rand() / (RAND_MAX));
        double tprob = Tprob(i, labs(low), labs(low2));
        // if (i % 100 == 0){
        //     printf("j is %f and tprob is %f \n", j, tprob);
        // }
        
        if (labs(low2) < labs(low) || j < tprob){
            A[a] = -1*A[a];
            A[b] = f*A[b];
            low = low2;
        } else {
            low2 = low;
        }
        if (labs(low) < labs(lowest)){
            lowest = low;
        }
    }
    lowest = labs(lowest);
    printf("sim Anneal (unp): %ld\n", lowest);
    return lowest;
}

double Tprob(int iter, long sum, long sum2) {
    double val = (floor((double)iter/300));
    double t = pow(10, 10) * pow(0.8, val);
    double sol = exp(((double)sum - sum2)/t);
    return sol;
}

long hillClimber(long A[], int max_iter) {
    srand(time(NULL));
    long low = randSol(A, false);
    // printf("starting: %ld\n", low);
    long low2 = low;
    int a, b;
    for (int i = 0; i < max_iter; i++) {
        a = rand() % size;
        b = a;
        while (a == b) {
            b = rand() % size;
        }
        int f = flip();
        low2 += A[a]*-2;
        if (f == -1){
            low2 += A[b]*-2;
        }
        // printf("changing %d and %d change %d to result in new sum %lu \n", a, b, f, labs(low2));
        // printf("comparing %lu and %lu \n", labs(low2), labs(low));
        if (labs(low2) < labs(low)){
            A[a] = -1*A[a];
            A[b] = f*A[b];
            low = low2;
        } else {
            low2 = low;
        }
    }
    low = labs(low);
    printf("Hill Climber (unp): %ld\n", low);
    return low;
}

long repeatedRandomPart(long A[], int max_iter) {
    long A_post[size];
    memset(A_post, 0, size * sizeof(long));
    printf("\n");
    randSolPart(A, A_post);
    return repeatedRandom(A_post, max_iter);
}

long repeatedRandom(long A[], int max_iter) {
    long low = labs(sum(A));
    for (int i = 0; i < max_iter; i++) {
        long b = randSol(A, true);
        low = min(low, b);
    }
    printf("Repeated Random (unp): %ld\n", low);
    return low;
}

void randSolPart(long A_pre[], long A_post[]){
    int r;
    for (int i = 0; i < size; i++){
        r = rand() % 100;
        A_post[r] += A_pre[i];
    }
}

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

long sum (long A[]) {
    long s = 0;
    for (int i = 0; i < size; i++) {
        s += A[i];
    }
    return s;
}

long min (long A, long B) {
    if (A > B) {
        return B;
    } else {
        return A;
    }
}

long flip() {
    int f = rand() % 2;
    if (f == 0) {
        f = -1;
    } else { 
        f = 1;
    }
    return f;
}

void mergeSort(long arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
        merge(arr, l, m, r); 
    } 
} 

void merge(long arr[], int l, int m, int r) 
{ 
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
