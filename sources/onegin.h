#ifndef SRC_ONEGIN_H_
#define SRC_ONEGIN_H_

#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <assert.h>

struct Line_t
{
    char* ptr = NULL;
    size_t length = 0;
};

struct Text_t
{
    Line_t* lines = NULL;
    size_t lines_count = 0;
    char* buff = NULL;
    size_t symbols_count = 0;
};

enum ShiftIndex
{
    STRAIGHT_SORT = 1,
    REVERSE_SORT = -1
};

int lines_comparator(const void* lineVoidPtr1, const void* lineVoidPtr2);
int reverse_lines_comparator(const void* lineVoidPtr1, const void* lineVoidPtr2);
size_t get_lines_count(char* buff);
void create_empty_file(const char filename[]);
char* create_buff(const char filename[]);
void fill_text_struct(Text_t* text, const char filename[]);
void write_text_struct_to_file(Text_t* text, const char filename[]);
void write_buff_to_file(Text_t* text, const char filename[]);
void clear_text_struct(Text_t* text);

#endif  // SRC_ONEGIN_H_
