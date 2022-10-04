#include "onegin.h"

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

    char symbol1 = (char)tolower(*str1);
    char symbol2 = (char)tolower(*str2);

    if ((symbol1 == symbol2) && ((symbol1 != '\n' && symbol1 != '\0') && (symbol2 != '\n' && symbol2 != '\0')))
    {
        return my_strcmp(str1 += shift_id, str2 += shift_id, shift_id);
    }

    return (symbol1 - symbol2);
}

int lines_comparator(const void* lineVoidPtr1, const void* lineVoidPtr2)
{
    assert(lineVoidPtr1 != NULL);
    assert(lineVoidPtr2 != NULL);

    const Line_t* linePtr1 = (const Line_t*)lineVoidPtr1;
    const Line_t* linePtr2 = (const Line_t*)lineVoidPtr2;

    const char* symbolPtr1 = linePtr1->ptr;
    const char* symbolPtr2 = linePtr2->ptr;

    return my_strcmp(symbolPtr1, symbolPtr2, STRAIGHT_SORT);
}

int reverse_lines_comparator(const void* lineVoidPtr1, const void* lineVoidPtr2)
{
    assert(lineVoidPtr1 != NULL);
    assert(lineVoidPtr2 != NULL);

    const Line_t* linePtr1 = (const Line_t*)lineVoidPtr1;
    const Line_t* linePtr2 = (const Line_t*)lineVoidPtr2;

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

size_t get_lines_count(char* buff)
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
    assert(empty_file != NULL);

    fclose(empty_file);
}

char* create_buff(const char filename[])
{
    struct stat file_stat = {};

    #ifdef NDEBUG
    stat(filename, &file_stat);
    #endif

    assert(stat(filename, &file_stat) != -1);

    char* tmp_buff = (char*)calloc((size_t)file_stat.st_size + 2, sizeof(char));
    assert(tmp_buff != NULL);

    FILE* file_to_read = fopen(filename, "rb");
    assert(file_to_read != NULL);

    fread(tmp_buff + 1, sizeof(char), (size_t)file_stat.st_size, file_to_read);
    fclose(file_to_read);

    tmp_buff[0] = '\0';
    tmp_buff[file_stat.st_size] = '\0';

    return (tmp_buff + 1);
}

void fill_text_struct(Text_t* text, const char filename[])
{
    assert(text != NULL);

    text->buff = create_buff(filename);

    text->lines_count = get_lines_count(text->buff);
    text->symbols_count = strlen(text->buff);

    text->lines = (Line_t*)calloc(text->lines_count, sizeof(Line_t));
    assert(text->lines != NULL);

    char* symbol_ptr = text->buff;

    for (unsigned int i = 0; i < text->lines_count; i++)
    {
        text->lines[i].ptr = symbol_ptr;

        while (*symbol_ptr != '\n' && *symbol_ptr != '\0')
        {
            symbol_ptr++;
        }
        text->lines[i].length = (size_t)(symbol_ptr - text->lines[i].ptr);

        if (i != text->lines_count - 1)
        {
            symbol_ptr++;
        }
    }
}

void write_text_struct_to_file(Text_t* text, const char filename[])
{
    assert(text != NULL);
    assert(text->lines != NULL);

    FILE* file_to_write = fopen(filename, "a");

    for (unsigned int i = 0; i < text->lines_count; i++)
    {
        fwrite(text->lines[i].ptr, sizeof(char), text->lines[i].length, file_to_write);
        fprintf(file_to_write, "%c", '\n');
    }
    fprintf(file_to_write, "%s", "\n\n====================================================================================================\n\n\n");

    fclose(file_to_write);
}

void write_buff_to_file(Text_t* text, const char filename[])
{
    assert(text != NULL);
    assert(text->buff != NULL);

    FILE* file_to_write = fopen(filename, "a");
    fwrite(text->buff, sizeof(char), strlen(text->buff), file_to_write);
    fclose(file_to_write);
}

void clear_text_struct(Text_t* text)
{
    assert(text != NULL);

    free(text->lines);
    free(text->buff - 1);

    text->lines = NULL;
    text->lines_count = 0;
    text->buff = NULL;
    text->symbols_count = 0;
}
