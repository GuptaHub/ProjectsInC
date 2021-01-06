//
//  shell.h
//  Assignment5
//
//  Created by Sahil Gupta on 11/12/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#ifndef shell_h
#define shell_h
#include <stdlib.h>
#include <stdio.h>

typedef struct ShellSort{
    int moves;
    int comparisons;
    int arr_size;
    int *gap_sequence;
    int gap_size;
}ShellSort;

ShellSort *shell_create(int size);
void gap_generate(ShellSort *shs);
void shell_sort(int * numbers, ShellSort *shs);

#endif /* shell_h */
