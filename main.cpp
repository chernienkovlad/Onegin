#include "sources/onegin.h"
#include "sources/my_qsort.h"

int main()
{
    const char filename[] = "files/Pushkin - Eugene Onegin.txt";

    Text_t onegin_poem = {};
    fill_text_struct(&onegin_poem, filename);

    const char result_filename[] = "files/sorted_onegin.txt";
    create_empty_file(result_filename);

    my_qsort(onegin_poem.lines, onegin_poem.lines_count, sizeof(Line_t), lines_comparator);
    write_text_struct_to_file(&onegin_poem, result_filename);

    my_qsort(onegin_poem.lines, onegin_poem.lines_count, sizeof(Line_t), reverse_lines_comparator);
    write_text_struct_to_file(&onegin_poem, result_filename);

    write_buff_to_file(&onegin_poem, result_filename);

    clear_text_struct(&onegin_poem);
    return 0;
}
