#include <stdio.h>
#include <stdlib.h>

const char ASCEND = '(';
const char DESCEND = ')';

int main(int argc, char* argv[])
{
    FILE* file_ptr;

    file_ptr = fopen("input_not_quite_lisp.txt", "r");

    if(file_ptr == NULL)
    {
        perror("Unable to open file.");
        exit(1);
    }

    char ch;
    int count = 0;
    int pos = 0;
    bool enter_base = false;

    do
    {
        if(count >= 0 && !enter_base)
        {
            pos++;
        }
        else
        {
            enter_base = true;
        }

        ch = fgetc(file_ptr);
        switch (ch)
        {
            case ASCEND:
                count++;
                break;
            case DESCEND:
                count--;
                break;
        }

    } while (ch != EOF);

    printf("%d\n", count);
    printf("%d\n", pos);

    fclose(file_ptr);
    return 0;
}

