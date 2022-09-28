#ifndef SRC_ONEGIN_H_
#define SRC_ONEGIN_H_

#include <stdio.h>

struct Line_t
{
    char* ptr;
    size_t length;
};

struct Poem_t
{
    Line_t* lines;
    size_t lines_count;
};

enum ShiftIndex
{
    STRAIGHT_SORT = 1,
    REVERSE_SORT = -1
};

int lines_comparator(const void* lineVoidPtr1, const void* lineVoidPtr2);
int reverse_lines_comparator(const void* lineVoidPtr1, const void* lineVoidPtr2);
void create_empty_file(const char filename[]);
char* create_buff(const char filename[]);
void fill_poem_struct(Poem_t* poem, char* buf);
void write_poem_to_file(const char filename[], Poem_t* poem);
void write_buff_to_file(const char filename[], char* buff);
void clear_buffers(Poem_t* poem, char* buff);

#endif  // SRC_ONEGIN_H_
