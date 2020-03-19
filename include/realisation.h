#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <pthread.h>

#define VEC_LEN 100
#define FILENAME "../input.txt"
#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS 0

typedef struct vec_sys_struct
{
    size_t len;
    double norm_min;
    double** vec_sys;
    double* temp_vec;
    int min_index;
    int counter;
} vec_sys_struct;

void input_from_file(char* str, vec_sys_struct* vec_sys_part);
void input(vec_sys_struct* vec_sys_part);
double** grow(double** str_vec, size_t* len);
double norm_from_vec_dif(const double* vec1, const double* vec2);/// Используется Эвклидова норма вектора
void* min_norm(void* args);
void input_temp_vec(vec_sys_struct* vec_sys_part);
void input_temp_vec_from_file(char* str, vec_sys_struct* vec_sys_part);
void del_vec(double* vec);
void del_vec_sys(double** vec_sys, size_t sys_len);
int take_min(vec_sys_struct* vec_sys, vec_sys_struct* block, int len);
