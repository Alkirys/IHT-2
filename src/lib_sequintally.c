#include "../include/lib_sequintally.h"


int sequintally_search(vec_sys_struct* vec_sys)
{
    if (vec_sys != NULL){
        min_norm(&(*vec_sys));
        return vec_sys->min_index;
    }
    else{
        return -1;
    };
}
