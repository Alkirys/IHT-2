#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vec_sys_struct.h"


double** grow(double** str_vec, size_t* len);
void input_from_file(const char* str, vec_sys_struct* vec_sys_part);
void input(vec_sys_struct* vec_sys_part);
void input_temp_vec(vec_sys_struct* vec_sys_part);
void input_temp_vec_from_file(const char* str, vec_sys_struct* vec_sys_part);
void del_vec(double* vec);
void del_vec_sys(double** vec_sys, size_t sys_len);
