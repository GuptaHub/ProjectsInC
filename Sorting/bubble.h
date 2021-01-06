//
//  bubble.h
//  Assignment5
//
//  Created by Sahil Gupta on 11/12/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#ifndef bubble_h
#define bubble_h

#include <stdio.h>
#include <stdlib.h>
typedef struct BubbleSort{
    int moves;
    int comparisons;
    int arr_size;
} BubbleSort;

BubbleSort *bubble_create(int size);

void bubble_sort(int * numbers, BubbleSort *bs);

#endif /* bubble_h */
