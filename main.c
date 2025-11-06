#include <stdio.h>
#include <stdlib.h>

void part1 (const char* line, size_t len);
void part2 (const char* line, size_t len);

int main (int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf (stdout, "Please provide an input file\r\n");
        exit (1);
    }

    FILE* fptr;
    char* file_name = argv[1]; 

    fptr = fopen (file_name, "r");

    // check for valid file pointer
    if (fptr == NULL)
    {
        fprintf (stderr, "Could not open file: %s\r\n", file_name);
        exit (1);
    }

    // solution for part one here
    char line[64];
    size_t len = sizeof (line);

    while (fgets (line, len, fptr))
    {
        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file\r\n");
            exit (1);
        }

        fprintf (stdout, "%s", line);

        part1 (line, len);
        part2 (line, len);
    }

    fclose (fptr);
    return 0;
}

void part1 (const char* line, size_t len)
{
    // solution for part one here
    return;
}

void part2 (const char* line, size_t len)
{
    // solution for part two here
    return;
}
