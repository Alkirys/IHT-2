#include "lib_realisation.h"
#include "vec_sys_struct.h"


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

        free(res_vec);
    }
    else{
        printf("\nError, vec is nullprt");
    }

    return norm;
}

void* min_norm(void* args)
{
    vec_sys_struct* vec_sys_part = (vec_sys_struct*) args;

    if (vec_sys_part != NULL) {

        double norm_min = norm_from_vec_dif(vec_sys_part->vec_sys[0], vec_sys_part->temp_vec);
        int index_min = 0;

        for (int i = 0; i < vec_sys_part->len; ++i) {
            double temp_norm = norm_from_vec_dif(vec_sys_part->vec_sys[i], vec_sys_part->temp_vec);
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
