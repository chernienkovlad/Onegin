#ifndef SRC_MY_QSORT_H_
#define SRC_MY_QSORT_H_

#define NDEBUG

#include <stdlib.h>
#include <string.h>
#include <assert.h>

void my_qsort(void* data, size_t elem_count, size_t elem_size, int (*comparator)(const void* a, const void* b));

#endif  // SRC_MY_QSORT_H_
