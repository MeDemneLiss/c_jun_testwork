#include <stdio.h>

int main(int argc, char *argv[])
{
    char *line = NULL;
    size_t len = 0;
    FILE *file_r = fopen(argv[1], "r");
    if (file_r != NULL)
    {
        int complex_com = 0;
        int num_com = 0;
        char last_ch;
        char ch;
        int simple_com = 0;
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
                if (last_ch != '\\')
                {
                    simple_com = 0;
                }
                fprintf(stdout, "\n");
            }
            last_ch = ch;
        }
    }
    else
    {
        printf("ERROR:\nFile not found\n");
    }
    fclose(file_r);
}