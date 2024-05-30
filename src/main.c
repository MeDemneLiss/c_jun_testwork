#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *file_r;
    if (argc == 1) // проверяем передан ли путь до файла
    {
        printf("Please enter file path\nExampl: ./a.out name.txt\n");
    }
    else if (file_r = fopen(argv[1], "r"))
    {
        char complex_com = 0; // флаг длинного комментария
        char simple_com = 0;  // флаг простого комментария
        int num_com = 0;
        char last_ch, ch;
        while ((ch = getc(file_r)) != EOF)
        {
            if (last_ch == '/' && ch == '/' && !complex_com && !simple_com)
            {
                printf("[%d]:\t", num_com);
                simple_com = 1;
                num_com++;
                ch = 0;
            }
            else if (last_ch == '/' && ch == '*' && !complex_com && !simple_com)
            {
                printf("[%d]:\t", num_com);
                complex_com = 1;
                num_com++;
                ch = 0;
            }
            else if (last_ch == '*' && ch == '/' && complex_com)
            {
                complex_com = 0;
                fprintf(stdout, "\n");
            }
            else if (complex_com || simple_com)
            {
                fprintf(stdout, "%c", last_ch);
            }
            if (ch == '\n' && simple_com)
            {
                if (last_ch != '\\') // обработка продления комментария
                {
                    simple_com = 0;
                }
                fprintf(stdout, "\n");
            }
            last_ch = ch;
        }
        fclose(file_r);
    }
    else
    {
        printf("ERROR:\nFile not found\n");
    }
}