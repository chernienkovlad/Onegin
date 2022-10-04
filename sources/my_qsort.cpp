#include "my_qsort.h"

static void swap(void* data, size_t elem_size, int i, int j)
{
    void* tmp = (char*)calloc(1, elem_size);

    memcpy(tmp, ((char*)data + (int)elem_size * i), elem_size);
    memcpy(((char*)data + (int)elem_size * i), ((char*)data + (int)elem_size * j), elem_size);
    memcpy(((char*)data + (int)elem_size * j), tmp, elem_size);

    free(tmp);
}

void my_qsort(void* data, size_t elem_count, size_t elem_size, int (*comparator)(const void* a, const void* b))
{
    assert(data != NULL);
    assert(comparator != NULL);

    int left = 0, right = (int)elem_count - 1, last = 0, i = 0;

    if (left >= right)
    {
        return;
    }

    swap(data, elem_size, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
    {
        if (comparator(((char*)data + (int)elem_size * i), ((char*)data + (int)elem_size * left)) < 0)
        {
            swap(data, elem_size, ++last, i);
        }
    }

    swap(data, elem_size, left, last);

    my_qsort(((char*)data + (int)elem_size * left), (size_t)(last - left), elem_size, comparator);
    my_qsort(((char*)data + (int)elem_size * (last + 1)), (size_t)(right - last), elem_size, comparator);
}
