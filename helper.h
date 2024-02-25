#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

    int i;
    typedef struct{
        int index;
        float distance;
    } indexDistance;

    indexDistance idArray[100];

// Prototype for the bubbleSort function 
void bubbleSort(indexDistance arr[], int n); // showout to : // https://www.geeksforgeeks.org/bubble-sort/

// Prototype for the swap function
void swap(indexDistance* a, indexDistance* b);

size_t digits(int num); // prototype for helper in t3
