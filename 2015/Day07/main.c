#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum BitwiseOp : char {
    OP_NOT      = 'N',
    OP_OR       = 'O',
    OP_AND      = 'A',
    OP_RSHIFT   = 'R',
    OP_LSHIFT   = 'L',
    OP_NONE     = '\0',
} BitwiseOp;

void part1 (const char* line, size_t len);
void part2 (const char* line, size_t len);

enum BitwiseOp parseForBitwiseOp (const char* line);

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

// examples:
// 123 -> x
// 456 -> y
// x AND y -> d
// x OR y -> e
// x LSHIFT 2 -> f
// y RSHIFT 2 -> g
// NOT x -> h
// NOT y -> i
BitwiseOp parseForBitwiseOp (const char* line)
{
    char ch = '\0';

    // bitwise ops start with capital letters
    // sometimes there isn't an op to ID
    //  in this case the left hand side will have either a variable or value
    
    // if NOT op exists, it will be at the beginning
    if (line[0] == OP_NOT)
    {
        return OP_NOT;
    }

    for (int i = 0; i < strlen (line); i++)
    {

    }

    return OP_NONE;
}

