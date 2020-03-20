#include "../include/lib_parallel.h"
#include "../include/lib_sequintally.h"
#include "../include/realisation.h"
#include <time.h>

void create_file(int num_vec, char* filename);
int test1();
int test2();
int test3();
int test4();
int test5();


int main()
{
    int arr[5];
    arr[0] = test1();
    arr[1] = test2();
    arr[2] = test3();
    arr[3] = test4();
    arr[4] = test5();


    for (int i = 0; i < 5; ++i){
        if (arr[i] != 1){
            printf("\nNO");
            return 0;
        }
    }
    printf("\nYES");


    //char* filename = "../files/input_temp_vec.txt";
    //create_file(1000000 * VEC_LEN, "../files/test_file3.txt");
    //vec_sys_struct vec_sys;
    //input_temp_vec_from_file(filename, &vec_sys);
    ////input_temp_vec(&vec_sys);
    //input_from_file("../files/test_file3.txt", &vec_sys);
    ////input(&vec_sys_part);
    //clock_t beg = clock();
    //sequintally_search(&vec_sys);
    //clock_t end = clock();
    //double time =(double)(end - beg);
    //printf("\nSequintally time: ");
    //printf("%lf", time);
    //printf("\n");
    //printf("\nVectors processed: ");
    //printf("%d", vec_sys.counter);
    //printf("\n");
    //printf("\nMinimal norm: ");
    //printf("%lf", vec_sys.norm_min);
    //printf("\n");
    //printf("\nIndex of the vector with the minimum norm: ");
    //printf("%d", vec_sys.min_index);
    //printf("\n\n");
    //printf("///////////////////////////////");
    //
    //beg = clock();
    //parallel_search(&vec_sys);
    //end = clock();
    //time =(double)(end - beg);
    //printf("\nParallel time: ");
    //printf("%lf", time);
    //printf("\n");
    //printf("\nVectors processed: ");
    //printf("%d", vec_sys.counter);
    //printf("\n");
    //printf("\nMinimal norm: ");
    //printf("%lf", vec_sys.norm_min);
    //printf("\n");
    //printf("\nIndex of the vector with the minimum norm: ");
    //printf("%d", vec_sys.min_index);
    //printf("\n\n");
    //printf("///////////////////////////////");
    //
    //del_vec(vec_sys.temp_vec);
    //del_vec_sys(vec_sys.vec_sys, vec_sys.len);

    return 0;
}


void create_file(int num_vec, char* filename)
{
    srand(time(NULL));
    FILE* file;
    file = fopen(filename, "w");
    int counter = 1;
    for (int i = 0; i < num_vec; ++i) {
        int rand_num = rand();
        int rand_den = rand();
        double num = (double)rand_num/rand_den;
        fprintf(file ,"%lf", num);
        fprintf(file ,"%c", ' ');
        if (counter == VEC_LEN){
            counter = 0;
            fprintf(file ,"\n");
        }
        ++counter;
    }

    fclose(file);
}

int test1()
{
    int is_all_right_seq = 0;
    int is_all_right_par = 0;
    int vec_num = 8;

    char* filename = "../files/input_temp_vec.txt";
    vec_sys_struct vec_sys;
    create_file(vec_num * VEC_LEN, "../files/test_file2.txt");
    input_temp_vec_from_file(filename, &vec_sys);
    //input_temp_vec(&vec_sys);
    input_from_file("../files/test_file2.txt", &vec_sys);
    //input(&vec_sys_part);
    clock_t beg = clock();
    sequintally_search(&vec_sys);
    clock_t end = clock();
    double time =(double)(end - beg);
    printf("\nSequintally time: ");
    printf("%lf", time);
    printf("\n");

    if (vec_num == vec_sys.counter){
        is_all_right_seq = 1;
    }

    printf("\nMinimal norm: ");
    printf("%lf", vec_sys.norm_min);
    printf("\n");
    printf("\nIndex of the vector with the minimum norm: ");
    printf("%d", vec_sys.min_index);
    printf("\n\n");

    beg = clock();
    parallel_search(&vec_sys);
    end = clock();
    time =(double)(end - beg);
    printf("\nParallel time: ");
    printf("%lf", time);
    printf("\n");

    if (vec_num == vec_sys.counter){
        is_all_right_par = 1;
    }

    printf("\nMinimal norm: ");
    printf("%lf", vec_sys.norm_min);
    printf("\n");
    printf("\nIndex of the vector with the minimum norm: ");
    printf("%d", vec_sys.min_index);
    printf("\n\n");
    printf("///////////////////////////////");

    del_vec(vec_sys.temp_vec);
    del_vec_sys(vec_sys.vec_sys, vec_sys.len);

    if (is_all_right_par && is_all_right_seq){
        return 1;
    }
    else{
        return 0;
    }
}

int test2()
{
    int is_all_right_seq = 0;
    int is_all_right_par = 0;
    int vec_num = 101;

    char* filename = "../files/input_temp_vec.txt";
    vec_sys_struct vec_sys;
    input_temp_vec_from_file(filename, &vec_sys);
    //input_temp_vec(&vec_sys);
    input_from_file("../files/test_file1.txt", &vec_sys);
    //input(&vec_sys_part);
    clock_t beg = clock();
    sequintally_search(&vec_sys);
    clock_t end = clock();
    double time =(double)(end - beg);
    printf("\nSequintally time: ");
    printf("%lf", time);
    printf("\n");

    if (vec_num == vec_sys.counter && vec_sys.min_index == 100 && vec_sys.norm_min == 0.0){
        is_all_right_seq = 1;
    }

    beg = clock();
    parallel_search(&vec_sys);
    end = clock();
    time =(double)(end - beg);
    printf("\nParallel time: ");
    printf("%lf", time);
    printf("\n");
    printf("///////////////////////////////");

    if (vec_num == vec_sys.counter && vec_sys.min_index == 100 && vec_sys.norm_min == 0.0){
        is_all_right_par = 1;
    }


    del_vec(vec_sys.temp_vec);
    del_vec_sys(vec_sys.vec_sys, vec_sys.len);

    if (is_all_right_par && is_all_right_seq){
        return 1;
    }
    else{
        return 0;
    }
}

int test3()
{
    int is_all_right_seq = 0;
    int is_all_right_par = 0;
    int vec_num = 3;

    char* filename = "../files/input_temp_vec.txt";
    vec_sys_struct vec_sys;
    create_file(vec_num * VEC_LEN, "../files/test_file2.txt");
    input_temp_vec_from_file(filename, &vec_sys);
    //input_temp_vec(&vec_sys);
    input_from_file("../files/test_file2.txt", &vec_sys);
    //input(&vec_sys_part);
    clock_t beg = clock();
    sequintally_search(&vec_sys);
    clock_t end = clock();
    double time =(double)(end - beg);
    printf("\nSequintally time: ");
    printf("%lf", time);
    printf("\n");

    if (vec_num == vec_sys.counter){
        is_all_right_seq = 1;
    }

    printf("\nMinimal norm: ");
    printf("%lf", vec_sys.norm_min);
    printf("\n");
    printf("\nIndex of the vector with the minimum norm: ");
    printf("%d", vec_sys.min_index);
    printf("\n\n");

    beg = clock();
    parallel_search(&vec_sys);
    end = clock();
    time =(double)(end - beg);
    printf("\nParallel time: ");
    printf("%lf", time);
    printf("\n");

    if (vec_num == vec_sys.counter){
        is_all_right_par = 1;
    }

    printf("\nMinimal norm: ");
    printf("%lf", vec_sys.norm_min);
    printf("\n");
    printf("\nIndex of the vector with the minimum norm: ");
    printf("%d", vec_sys.min_index);
    printf("\n\n");
    printf("///////////////////////////////");

    del_vec(vec_sys.temp_vec);
    del_vec_sys(vec_sys.vec_sys, vec_sys.len);

    if (is_all_right_par && is_all_right_seq){
        return 1;
    }
    else{
        return 0;
    }
}

int test4()
{
    int is_all_right_seq = 0;
    int is_all_right_par = 0;
    int vec_num = 102;

    char* filename = "../files/input_temp_vec.txt";
    //create_file(vec_num * VEC_LEN, "../files/test_file4.txt");

    vec_sys_struct vec_sys;
    input_temp_vec_from_file(filename, &vec_sys);
    //input_temp_vec(&vec_sys);
    input_from_file("../files/test_file3.txt", &vec_sys);
    //input(&vec_sys_part);
    clock_t beg = clock();
    sequintally_search(&vec_sys);
    clock_t end = clock();
    double time =(double)(end - beg);
    printf("\nSequintally time: ");
    printf("%lf", time);
    printf("\n");


    if (vec_num == vec_sys.counter && vec_sys.min_index == 8){
        is_all_right_seq = 1;
    }

    beg = clock();
    parallel_search(&vec_sys);
    end = clock();
    time =(double)(end - beg);
    printf("\nParallel time: ");
    printf("%lf", time);
    printf("\n");
    printf("///////////////////////////////");

    if (vec_num == vec_sys.counter && vec_sys.min_index == 8){
        is_all_right_par = 1;
    }


    del_vec(vec_sys.temp_vec);
    del_vec_sys(vec_sys.vec_sys, vec_sys.len);

    if (is_all_right_par && is_all_right_seq){
        return 1;
    }
    else{
        return 0;
    }
}

int test5()
{
    int is_all_right_seq = 0;
    int is_all_right_par = 0;
    int vec_num = 101;

    char* filename = "../files/input_temp_vec.txt";
    //create_file(vec_num * VEC_LEN, "../files/test_file4.txt");

    vec_sys_struct vec_sys;
    input_temp_vec_from_file(filename, &vec_sys);
    //input_temp_vec(&vec_sys);
    input_from_file("../files/test_file4.txt", &vec_sys);
    //input(&vec_sys_part);
    clock_t beg = clock();
    sequintally_search(&vec_sys);
    clock_t end = clock();
    double time =(double)(end - beg);
    printf("\nSequintally time: ");
    printf("%lf", time);
    printf("\n");

    if (vec_num == vec_sys.counter && vec_sys.min_index == 55 && vec_sys.norm_min == 0.0){
        is_all_right_seq = 1;
    }

    beg = clock();
    parallel_search(&vec_sys);
    end = clock();
    time =(double)(end - beg);
    printf("\nParallel time: ");
    printf("%lf", time);
    printf("\n");
    printf("///////////////////////////////");

    if (vec_num == vec_sys.counter && vec_sys.min_index == 55 && vec_sys.norm_min == 0.0){
        is_all_right_par = 1;
    }


    del_vec(vec_sys.temp_vec);
    del_vec_sys(vec_sys.vec_sys, vec_sys.len);

    if (is_all_right_par && is_all_right_seq){
        return 1;
    }
    else{
        return 0;
    }
}

