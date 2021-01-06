//
//  binary.h
//  Assignment5
//
//  Created by Sahil Gupta on 11/12/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#ifndef binary_h
#define binary_h

#include <stdio.h>
#include <stdlib.h>
typedef struct BinaryInsertion{
    int moves;
    int comparisons;
    int arr_size;
}BinaryInsertion;

BinaryInsertion *bI_create(int size);
void Binary_insertion(int * numbers, BinaryInsertion *bI);
#endif /* binary_h */
