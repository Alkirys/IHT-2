#pragma once

#include <pthread.h>
#include "lib_realisation.h"
#ifdef MACOS
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#endif

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12


int parallel_search(vec_sys_struct* vec_sys);
