#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vec_sys_struct.h"

#define SUCCESS 0


double norm_from_vec_dif(const double* vec1, const double* vec2);/// Используется Эвклидова норма вектора
void* min_norm(void* args);
