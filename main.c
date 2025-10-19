#include <stdio.h>
#include <stdlib.h>

void part1 (FILE *fptr);
void part2 (FILE *fptr);

int main (void)
{
    FILE *fptr;
    char *file_name = "input";

    fptr = fopen (file_name, "r");

    // check for valid file pointer
    if (fptr == NULL)
    {
        fprintf (stderr, "Could not open file: %s\r\n", file_name);
        exit (1);
    }

    part1 (fptr);

    rewind (fptr);

    part2 (fptr);

    fclose (fptr);
    return 0;
}

void part1 (FILE *fptr)
{
    // solution for part one here
    char ch;

    while ((ch = fgetc (fptr)) != EOF)
    {
        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file\r\n");
            exit (1);
        }

        fprintf (stdout, "%c", ch);
    }

    return;
}

void part2 (FILE *fptr)
{
    // solution for part two here
    char ch;

    while ((ch = fgetc (fptr)) != EOF)
    {
        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file\r\n");
            exit (1);
        }

        fprintf (stdout, "%c", ch);
    }

    return;
}
