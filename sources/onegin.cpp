#include "onegin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <assert.h>

static int my_isalpha(const char symbol)
{
    return (isalpha(symbol) || symbol == '\n' || symbol == '\0');
}

static int my_strcmp(const char* str1, const char* str2, ShiftIndex shift_id)
{
    if (!my_isalpha(*str1) && !my_isalpha(*str2))
    {
        return my_strcmp(str1 += shift_id, str2 += shift_id, shift_id);
    }
    else if (!my_isalpha(*str1))
    {
        return my_strcmp(str1 += shift_id, str2, shift_id);
    }
    else if (!my_isalpha(*str2))
    {
        return my_strcmp(str1, str2 += shift_id, shift_id);
    }

    char symbol1 = tolower(*str1);
    char symbol2 = tolower(*str2);

    if ((symbol1 == symbol2) && ((symbol1 != '\n' && symbol1 != '\0') && (symbol2 != '\n' && symbol2 != '\0')))
    {
        return my_strcmp(str1 += shift_id, str2 += shift_id, shift_id);
    }

    return (symbol1 - symbol2);
}

int lines_comparator(const void* lineVoidPtr1, const void* lineVoidPtr2)
{
    Line_t* linePtr1 = (Line_t*)lineVoidPtr1;
    Line_t* linePtr2 = (Line_t*)lineVoidPtr2;

    const char* symbolPtr1 = linePtr1->ptr;
    const char* symbolPtr2 = linePtr2->ptr;

    return my_strcmp(symbolPtr1, symbolPtr2, STRAIGHT_SORT);
}

int reverse_lines_comparator(const void* lineVoidPtr1, const void* lineVoidPtr2)
{
    Line_t* linePtr1 = (Line_t*)lineVoidPtr1;
    Line_t* linePtr2 = (Line_t*)lineVoidPtr2;

    if (linePtr1->length == 0)
    {
        return -1;
    }
    if (linePtr2->length == 0)
    {
        return 1;
    }

    const char* lastSymbolPtr1 = linePtr1->ptr + linePtr1->length - 1;
    const char* lastSymbolPtr2 = linePtr2->ptr + linePtr2->length - 1;

    return my_strcmp(lastSymbolPtr1, lastSymbolPtr2, REVERSE_SORT);
}

static size_t get_lines_count(char* buff)
{
    size_t nLines = 0;

    for (unsigned int i = 0; buff[i] != '\0'; i++)
        if (buff[i] == '\n')
            nLines++;

    return ++nLines;
}

void create_empty_file(const char filename[])
{
    FILE* empty_file = fopen(filename, "w");

    #ifdef DEBUG
    assert(empty_file != NULL);
    #endif

    fclose(empty_file);
}

char* create_buff(const char filename[])
{
    struct stat file_stat = {};

    #ifndef DEBUG
    stat(filename, &file_stat);
    #endif

    #ifdef DEBUG
    assert(stat(filename, &file_stat) != -1);
    #endif

    char* tmp_buff = (char*)calloc(file_stat.st_size + 1, sizeof(char));

    #ifdef DEBUG
    assert(tmp_buff != NULL);
    #endif

    FILE* file_to_read = fopen(filename, "rb");

    #ifdef DEBUG
    assert(file_to_read != NULL);
    #endif

    fread(tmp_buff, sizeof(char), file_stat.st_size, file_to_read);
    fclose(file_to_read);

    tmp_buff[file_stat.st_size] = '\0';

    return tmp_buff;
}

void fill_poem_struct(Poem_t* poem, char* buff)
{
    #ifdef DEBUG
    assert(poem != NULL);
    assert(buff != NULL);
    #endif

    poem->lines_count = get_lines_count(buff);
    poem->lines = (Line_t*)calloc(poem->lines_count, sizeof(Line_t));

    #ifdef DEBUG
    assert(poem->lines != NULL);
    #endif

    char* symbol_ptr = buff;

    for (unsigned int i = 0; i < poem->lines_count; i++)
    {
        poem->lines[i].ptr = symbol_ptr;

        while (*symbol_ptr != '\n' && *symbol_ptr != '\0')
        {
            symbol_ptr++;
        }
        poem->lines[i].length = symbol_ptr - poem->lines[i].ptr;

        if (i != poem->lines_count - 1)
        {
            symbol_ptr++;
        }
    }
}

void write_poem_to_file(const char filename[], Poem_t* poem)
{
    #ifdef DEBUG
    assert(poem != NULL);
    assert(poem->lines != NULL);
    #endif

    FILE* file_to_write = fopen(filename, "a");

    for (unsigned int i = 0; i < poem->lines_count; i++)
    {
        fwrite(poem->lines[i].ptr, sizeof(char), poem->lines[i].length, file_to_write);
        fprintf(file_to_write, "%c", '\n');
    }
    fprintf(file_to_write, "%s", "\n\n====================================================================================================\n\n\n");

    fclose(file_to_write);
}

void write_buff_to_file(const char filename[], char* buff)
{
    #ifdef DEBUG
    assert(buff != NULL);
    #endif

    FILE* file_to_write = fopen(filename, "a");
    fwrite(buff, sizeof(char), strlen(buff), file_to_write);
    fclose(file_to_write);
}

void clear_buffers(Poem_t* poem, char* buff)
{
    free(poem->lines);
    free(buff);

    poem->lines = NULL;
    buff = NULL;
}
