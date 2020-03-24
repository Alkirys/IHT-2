#include "../include/lib_parallel.h"


static int take_min(vec_sys_struct* vec_sys, const vec_sys_struct* block, const int len)
{
    int ans = 0;
    double min = 0;
    if (block != NULL){
        int min_index = 0;
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
    if (block != NULL)
        for (int i = 0; i < len; i++) {
            sum += block[i].counter;
        }
    vec_sys->counter = sum;
    vec_sys->min_index = ans;
    vec_sys->norm_min = min;

    return ans;
}

static int get_num_cores() {
#ifdef MACOS
    int nm[2];
    size_t len = 4;
    uint32_t count;

    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);

    if(count < 1) {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if(count < 1) { count = 1; }
    }
    return count;
#else
    return (int)sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

static double norm_from_vec_dif(const double* vec1, const double* vec2)/// Используется Эвклидова норма вектора
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

static void* min_norm(void* args)
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

int parallel_search(vec_sys_struct* vec_sys)
{
    int num_threads = get_num_cores();

    pthread_t threads[num_threads];
    int status;
    int i;
    int* status_addr = NULL;

    vec_sys_struct vec_sys_part[num_threads];


    for (i = 0; i < num_threads; i++) {
        if (i != (num_threads - 1)) {
            vec_sys_part[i].len = vec_sys->len / num_threads;
            vec_sys_part[i].temp_vec = vec_sys->temp_vec;
            vec_sys_part[i].vec_sys = vec_sys->vec_sys + (vec_sys->len / num_threads * i);
            vec_sys_part[i].counter = 0;
        }
        else{
            vec_sys_part[i].len = vec_sys->len / num_threads + vec_sys->len % num_threads;
            vec_sys_part[i].temp_vec = vec_sys->temp_vec;
            vec_sys_part[i].vec_sys = vec_sys->vec_sys+(vec_sys->len / num_threads * i);
            vec_sys_part[i].counter = 0;
        }
    }

    for (i = 0; i < num_threads; i++) {
        status = pthread_create(&threads[i], NULL, min_norm, (void*) &vec_sys_part[i]);
        if (status != 0) {
            printf("main error: can't create thread, status = %d\n", status);
            exit(ERROR_CREATE_THREAD);
        }
    }

    for (i = 0; i < num_threads; i++) {
        status = pthread_join(threads[i], (void**)&status_addr);
        if (status != SUCCESS) {
            printf("main error: can't join thread, status = %d\n", status);
            exit(ERROR_JOIN_THREAD);
        }
    }

    take_min(&(*vec_sys), vec_sys_part, num_threads);

    return vec_sys->min_index;
}
