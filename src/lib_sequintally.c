#include "../include/lib_sequintally.h"


int sequintally_search(vec_sys_struct* vec_sys)
{
    min_norm(&(*vec_sys));

    return vec_sys->min_index;
}
