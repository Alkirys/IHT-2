#include "gtest/gtest.h"
#include <chrono>
#include <iostream>
extern "C" {
    #include "../include/lib_sequintally.h"
    #include "../include/lib_parallel.h"
    #include "../include/auxiliary_functions.h"
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

TEST(t1, t1)
{
    bool is_all_right = false;
    int min_ind = -1;
    double norm = -1.0;
    int vec_num = 1000000;

    char* filename = (char*)"../../files/input_temp_vec.txt";
    char* filename2 = (char*)"../../files/big_data_file.txt";
    vec_sys_struct vec_sys;

    create_file(vec_num * VEC_LEN, filename2);

    input_temp_vec_from_file(filename, &vec_sys);
    //input_temp_vec(&vec_sys);
    input_from_file(filename2, &vec_sys);
    //input(&vec_sys_part);
    double sum_seq = .0;
    double sum_par = .0;

    for (int i = 0; i < 10; ++i) {

        auto beg = std::chrono::high_resolution_clock::now();
        sequintally_search(&vec_sys);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_seq = end - beg;
        sum_seq += time_seq.count();
        min_ind = vec_sys.min_index;
        norm = vec_sys.norm_min;


        beg = std::chrono::high_resolution_clock::now();
        parallel_search(&vec_sys);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_par = end - beg;
        sum_par += time_par.count();

        if (min_ind == vec_sys.min_index && norm == vec_sys.norm_min)
            is_all_right = true;
        if (!is_all_right)
            break;
    }

    printf("\nSequintally time: ");
    sum_seq /= 10;
    std::cout << sum_seq << " sec" << std::endl;
    printf("\n");

    printf("\nParralel time: ");
    sum_par /= 10;
    std::cout << sum_par << " sec" << std::endl;
    printf("\n");

    del_vec(vec_sys.temp_vec);
    del_vec_sys(vec_sys.vec_sys, vec_sys.len);

    ASSERT_EQ(is_all_right, true);
}

TEST(t2, t2)
{
    bool is_all_right = false;
    int min_ind = -1;
    double norm = -1.0;
    int vec_num = 10000;

    char* filename = (char*)"../../files/input_temp_vec.txt";
    char* filename2 = (char*)"../../files/average_data_file.txt";
    vec_sys_struct vec_sys;

    create_file(vec_num * VEC_LEN, filename2);

    input_temp_vec_from_file(filename, &vec_sys);
    //input_temp_vec(&vec_sys);
    input_from_file(filename2, &vec_sys);
    //input(&vec_sys_part);
    double sum_seq = .0;
    double sum_par = .0;

    for (int i = 0; i < 10; ++i) {

        auto beg = std::chrono::high_resolution_clock::now();
        sequintally_search(&vec_sys);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_seq = end - beg;
        sum_seq += time_seq.count();
        min_ind = vec_sys.min_index;
        norm = vec_sys.norm_min;


        beg = std::chrono::high_resolution_clock::now();
        parallel_search(&vec_sys);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_par = end - beg;
        sum_par += time_par.count();

        if (min_ind == vec_sys.min_index && norm == vec_sys.norm_min)
            is_all_right = true;
        if (!is_all_right)
            break;
    }

    printf("\nSequintally time: ");
    sum_seq /= 10;
    std::cout << sum_seq << " sec" << std::endl;
    printf("\n");

    printf("\nParralel time: ");
    sum_par /= 10;
    std::cout << sum_par << " sec" << std::endl;
    printf("\n");

    del_vec(vec_sys.temp_vec);
    del_vec_sys(vec_sys.vec_sys, vec_sys.len);

    ASSERT_EQ(is_all_right, true);
}

TEST(t3, t3)
{
    bool is_all_right = false;
    int min_ind = -1;
    double norm = -1.0;
    int vec_num = 100;

    char* filename = (char*)"../../files/input_temp_vec.txt";
    char* filename2 = (char*)"../../files/small_data_file.txt";
    vec_sys_struct vec_sys;

    create_file(vec_num * VEC_LEN, filename2);

    input_temp_vec_from_file(filename, &vec_sys);
    //input_temp_vec(&vec_sys);
    input_from_file(filename2, &vec_sys);
    //input(&vec_sys_part);
    double sum_seq = .0;
    double sum_par = .0;

    for (int i = 0; i < 10; ++i) {

        auto beg = std::chrono::high_resolution_clock::now();
        sequintally_search(&vec_sys);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_seq = end - beg;
        sum_seq += time_seq.count();
        min_ind = vec_sys.min_index;
        norm = vec_sys.norm_min;


        beg = std::chrono::high_resolution_clock::now();
        parallel_search(&vec_sys);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_par = end - beg;
        sum_par += time_par.count();

        if (min_ind == vec_sys.min_index && norm == vec_sys.norm_min)
            is_all_right = true;
        if (!is_all_right)
            break;
    }

    printf("\nSequintally time: ");
    sum_seq /= 10;
    std::cout << sum_seq << " sec" << std::endl;
    printf("\n");

    printf("\nParralel time: ");
    sum_par /= 10;
    std::cout << sum_par << " sec" << std::endl;
    printf("\n");

    del_vec(vec_sys.temp_vec);
    del_vec_sys(vec_sys.vec_sys, vec_sys.len);

    ASSERT_EQ(is_all_right, true);
}
