#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LINE_LENGTH = 60;

int main(void)
{
    FILE* fptr;
    char* file_name = "input";

    fptr = fopen(file_name, "r");

    // check for valid file pointer
    if(fptr == NULL)
    {
        fprintf(stderr, "Could not open file: %s\r\n", file_name);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];

    while(fgets(line, sizeof(line), fptr))
    {
        if(ferror(fptr))
        {
            fprintf(stderr, "Error occured while reading file: %s\r\n", file_name);
            exit(1);
        }

        fprintf(stdout, "%s", line);
    }

    fclose(fptr);
    return 0;
}

