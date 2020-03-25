#pragma once

#include <stdio.h>

#define VEC_LEN 100


typedef struct vec_sys_struct
{
    size_t len;
    double norm_min;
    double** vec_sys;
    double* temp_vec;
    int min_index;
    int counter;
} vec_sys_struct;
