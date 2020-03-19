#include "../include/realisation.h"


void input_temp_vec(vec_sys_struct* vec_sys_part)
{
    double comp = 0;
    double* vec = (double*)malloc(VEC_LEN * sizeof(double));

    if (vec != NULL){
        for (int i = 0; i < VEC_LEN; ++i){
            if (0 != scanf("%lf", &comp))
                vec[i] = comp;
        }
    }

    vec_sys_part->temp_vec = vec;
}

double** grow(double** str_vec, size_t* len)
{
    double** temp = NULL;
    if (*len != 0){
        temp = (double**)realloc(str_vec, ((*len)*2)* sizeof(double*));
        *len *= 2;
    }
    else {
        temp = (double**)malloc(sizeof(double*));
        *len = 1;
    }

    return temp;
}


void input_temp_vec_from_file(char* str, vec_sys_struct* vec_sys_part)
{
    FILE* file = fopen(str, "r");
    double comp = 0;
    double* vec = (double*)malloc(VEC_LEN * sizeof(double));

    if (vec != NULL){
        for (int i = 0; i < VEC_LEN; ++i){
            if(0 != fscanf(file, "%lf", &comp))
                vec[i] = comp;
        }
    }

    vec_sys_part->temp_vec = vec;

    fclose(file);
}

void input_from_file(char* str, vec_sys_struct* vec_sys_part)
{
    FILE* file = fopen(str, "r");
    double comp = 0;
    int counter = 0;
    int iter = 0;
    if (vec_sys_part == NULL){
        return;
    }

    vec_sys_part->len = 0;
    vec_sys_part->counter = 0;

    while (EOF != fscanf(file, "%lf", &comp)) {
        if (vec_sys_part->len == iter){
            double** temp_p = NULL;
            temp_p = grow(vec_sys_part->vec_sys, &vec_sys_part->len);
            if (temp_p != NULL){
                vec_sys_part->vec_sys = temp_p;
            }
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

    while (scanf("%lf", &comp)) {
        if (vec_sys_part->len == iter){
            double** temp_p = NULL;
            temp_p = grow(vec_sys_part->vec_sys, &vec_sys_part->len);
            if (temp_p != NULL){
                vec_sys_part->vec_sys = temp_p;
            }
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

double norm_from_vec_dif(const double* vec1, const double* vec2)
{
    double* res_vec = NULL;
    double norm = 0;
    res_vec = (double*)malloc(VEC_LEN * sizeof(double));

    if (res_vec != NULL){

        for(int i = 0; i < VEC_LEN; ++i){
            res_vec[i] = vec1[i] - vec2[i];
        }

        double sum = 0;

        for(int i = 0; i < VEC_LEN; ++i){
            sum += (res_vec[i] * res_vec[i]);
        }

        norm = sqrt(sum);
    }
    else{
        printf("\nError, vec is nullprt");
    }

    del_vec(res_vec);

    return norm;
}

void* min_norm(void* args)
{
    vec_sys_struct* vec_sys_part = (vec_sys_struct*) args;

    int index_min = 0;
    double norm_min;

    if (vec_sys_part != NULL) {

        norm_min = norm_from_vec_dif(vec_sys_part->vec_sys[0], vec_sys_part->temp_vec);
        double temp_norm = 0;

        for (int i = 0; i < vec_sys_part->len; ++i) {
            temp_norm = norm_from_vec_dif(vec_sys_part->vec_sys[i], vec_sys_part->temp_vec);
            if (norm_min < 0) {
                norm_min = temp_norm;
            }
            if (temp_norm < norm_min) {
                norm_min = temp_norm;
                index_min = i;
            }
            ++vec_sys_part->counter;
        }

        vec_sys_part->min_index = index_min;
        vec_sys_part->norm_min = norm_min;
    }
    return SUCCESS;
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

int take_min(vec_sys_struct* vec_sys, vec_sys_struct* block, int len)
{
    int ans = 0;
    int min_index = 0;
    double min = 0;
    if (block != NULL){
        min = block[0].norm_min;

        for (int i = 0; i < len; ++i) {
            if (min > block[i].norm_min && block[i].norm_min >= 0) {
                min_index = i;
                min = block[i].norm_min;
            }
        }

        ans = min_index * (int)block[0].len + block[min_index].min_index;
    }

    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (block != NULL)
            sum += block[i].counter;
    }
    vec_sys->counter = sum;
    vec_sys->min_index = ans;
    vec_sys->norm_min = min;

    return ans;
}
