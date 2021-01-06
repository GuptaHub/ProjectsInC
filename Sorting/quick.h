//
//  quick.h
//  Assignment5
//
//  Created by Sahil Gupta on 11/12/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#ifndef quick_h
#define quick_h

#include <stdio.h>
#include <stdlib.h>
typedef struct QuickSort{
    int moves;
    int comparisons;
    int arr_size;
}QuickSort;

QuickSort *qs_create(int size);
int Partition(int right, int left, int*numbers, QuickSort *qs);
void Quick_sort(int * numbers, int size, int right, int left, QuickSort *qs);
#endif /* quick_h */
