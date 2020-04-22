#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>



int main(int argc, char** argv) {
    srand(time(NULL));
    int a;
    for (int i = 0; i < 50; i++){
        a = rand() % 100;
        // a = ((double) rand() / (RAND_MAX));
        printf("%d\n", a);
    }
}