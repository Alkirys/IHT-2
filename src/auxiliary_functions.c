#include "../include/auxiliary_functions.h"


double** grow(double** str_vec, size_t* len)
{
    double** temp = NULL;
    if (*len != 0){
        temp = (double**)realloc(str_vec, ((*len)*2)* sizeof(double*));
        if (temp != NULL){
            str_vec = temp;
        }
        *len *= 2;
    }
    else {
        temp = (double**)malloc(sizeof(double*));
        if (temp != NULL){
            str_vec = temp;
        }
        *len = 1;
    }

    return str_vec;
}

void input_temp_vec(vec_sys_struct* vec_sys_part)
{
    double comp = 0;
    double* vec = (double*)malloc(VEC_LEN * sizeof(double));

    if (vec != NULL){
        for (int i = 0; i < VEC_LEN; ++i){
            if (0 != scanf("%15lf", &comp))
                vec[i] = comp;
        }
    }

    vec_sys_part->temp_vec = vec;
}

void input_temp_vec_from_file(const char* str, vec_sys_struct* vec_sys_part)
{
    FILE* file = fopen(str, "r");
    double comp = 0;
    double* vec = (double*)malloc(VEC_LEN * sizeof(double));

    if (vec != NULL){
        for (int i = 0; i < VEC_LEN; ++i){
            if(0 != fscanf(file, "%15lf", &comp))
                vec[i] = comp;
        }
    }

    vec_sys_part->temp_vec = vec;

    fclose(file);
}

void input_from_file(const char* str, vec_sys_struct* vec_sys_part)
{
    FILE* file = fopen(str, "r");
    double comp = 0;
    int counter = 0;
    int iter = 0;
    if (vec_sys_part == NULL){
        fclose(file);
        return;
    }

    vec_sys_part->len = 0;
    vec_sys_part->counter = 0;

    while (EOF != fscanf(file, "%15lf", &comp)) {
        if (vec_sys_part->len == iter){
            vec_sys_part->vec_sys = grow(vec_sys_part->vec_sys, &vec_sys_part->len);
        }
        if (counter == 0) {
            double *temp = NULL;
            temp = (double *) malloc(VEC_LEN * sizeof(double));
            if (temp != NULL) {
                vec_sys_part->vec_sys[iter] = temp;
            }
        }

        vec_sys_part->vec_sys[iter][counter] = comp;

        if (counter == (VEC_LEN - 1)){
            ++iter;
            counter = -1;
        }

        ++counter;
    }

    vec_sys_part->len = iter;

    fclose(file);
}

void input(vec_sys_struct* vec_sys_part)
{
    double comp = 0;
    int counter = 0;
    int iter = 0;

    if (vec_sys_part == NULL){
        return;
    }

    vec_sys_part->len = 0;
    vec_sys_part->counter = 0;

    while (scanf("%15lf", &comp)) {
        if (vec_sys_part->len == iter){
            vec_sys_part->vec_sys = grow(vec_sys_part->vec_sys, &vec_sys_part->len);
        }
        if (counter == 0) {
            double *temp = NULL;
            temp = (double *) malloc(VEC_LEN * sizeof(double));
            if (temp != NULL) {
                vec_sys_part->vec_sys[iter] = temp;
            }
        }

        vec_sys_part->vec_sys[iter][counter] = comp;

        if (counter == (VEC_LEN - 1)){
            ++iter;
            counter = -1;
        }

        ++counter;
    }

    vec_sys_part->len = iter;
}

void del_vec(double* vec)
{
    if (vec != NULL)
        free(vec);
}

void del_vec_sys(double** vec_sys, size_t sys_len)
{
    if (vec_sys != NULL){
        for (int i = 0; i < sys_len; ++i) {
            if (vec_sys[i] != NULL)
                free(vec_sys[i]);
        }
        free(vec_sys);
    }
}
