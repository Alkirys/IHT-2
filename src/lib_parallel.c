#include "../include/lib_parallel.h"
#include "../include/realisation.h"


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
