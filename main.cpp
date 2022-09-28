#include "sources/onegin.h"
#include "sources/my_qsort.h"

int main()
{
    const char filename[] = "files/Pushkin - Eugene Onegin.txt";

    char* onegin_buff = create_buff(filename);

    Poem_t onegin_poem = {};
    fill_poem_struct(&onegin_poem, onegin_buff);

    const char result_filename[] = "files/sorted_onegin.txt";
    create_empty_file(result_filename);

    my_qsort(onegin_poem.lines, onegin_poem.lines_count, sizeof(Line_t), lines_comparator);
    write_poem_to_file(result_filename, &onegin_poem);

    my_qsort(onegin_poem.lines, onegin_poem.lines_count, sizeof(Line_t), reverse_lines_comparator);
    write_poem_to_file(result_filename, &onegin_poem);

    write_buff_to_file(result_filename, onegin_buff);

    clear_buffers(&onegin_poem, onegin_buff);
    return 0;
}
