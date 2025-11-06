#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint16_t wireState[0xFF][0xFF] = { {0, 0}, {0, 0} };

// gate, another wire, or value provide signals to wires
// one signal source per wire
// signals can go to multiple destinations
// gates provide no signal until all inputs have a signal

void part1 (const char* line, size_t len);
void part2 (const char* line, size_t len);

int negateVal (int val);

int main (int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf (stderr, "Please provide an input file \r\n");
        exit (1);
    }

    FILE* fptr;
    char* file_name = argv[1];

    fptr = fopen (file_name, "r");

    // check for valid file pointer
    if (fptr == NULL)
    {
        fprintf (stderr, "Could not open file: %s\r\n", file_name);
        exit (2);
    }

    // solution for part one here
    char line[64];
    size_t len = sizeof (line);

    while (fgets (line, len, fptr))
    {
        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file\r\n");
            exit (2);
        }

        fprintf (stdout, "%s", line);

        /**
         * [value] -> [port]
         * [port] [operation] [port] -> [port]
         * NOT [port] -> [port]
         *
         * Operations:
         *  - AND
         *  - OR
         *  - LSHIFT
         *  - RSHIFT
         */

        part1 (line, len);
        part2 (line, len);
    }

    fclose (fptr);
    return 0;
}

void part1 (const char* line, size_t len)
{
    // solution for part one here
    
    char inst[16];
    char out[8];
    if (sscanf(line, "%15[^-] -> %7s", inst, out) != 2)
    {
        fprintf (stderr, "Failed to extract instruction and/or port\r\n");
        exit (3);
    }

    int val = 0;
    char in1[3] = { '\0' };
    char op[6] = { '\0' };
    char in2[3] = { '\0' };

    const char* numSet = "0123456789";

    if (strstr(inst, "NOT"))
    {
        if (sscanf(inst, "NOT %2s", in1) != 1)
        {
            fprintf(stderr, "Failed to extract wire in from NOT operation\r\n");
            exit (3);
        }
        fprintf (stdout, "Assigning NOT %s to wire %s\r\n", in1, out);
        
        if (strspn (in1, numSet) == strlen(in1))
        {
            val = negateVal(atoi(in1));
        }
        else
        {
            val = negateVal(wireState[in1[0]][in1[1]]);
        }

        fprintf (stdout, "Writing %i to wire %i, %i\r\n", val, out[0], out[1]);
        wireState[out[0]][out[1]] = val;
    }
    else if (strstr(inst, "OR"))
    {
        if (sscanf(inst, "%2s OR %2s", in1, in2) != 2)
        {
            fprintf(stderr, "Failed to extract wire in from OR operation\r\n");
            exit (3);
        }
        // fprintf (stdout, "Assigning %s OR %s to wire %s\r\n", in1, in2, out);
    }
    else if (strstr(inst, "AND"))
    {
        if (sscanf(inst, "%2s AND %2s", in1, in2) != 2)
        {
            fprintf(stderr, "Failed to extract wire in from AND operation\r\n");
            exit (3);
        }
        // fprintf (stdout, "Assigning %s AND %s to wire %s\r\n", in1, in2, out);
    }
    else if (strstr(inst, "LSHIFT"))
    {
        if (sscanf(inst, "%2s LSHIFT %2s", in1, in2) != 2)
        {
            fprintf(stderr, "Failed to extract wire in from LSHIFT operation\r\n");
            exit (3);
        }
        // fprintf (stdout, "Assigning %s LSHIFT %s to wire %s\r\n", in1, in2, out);
    }
    else if (strstr(inst, "RSHIFT"))
    {
        if (sscanf(inst, "%2s RSHIFT %2s", in1, in2) != 2)
        {
            fprintf(stderr, "Failed to extract wire in from RSHIFT operation\r\n");
            exit (3);
        }
        // fprintf (stdout, "Assigning %s RSHIFT %s to wire %s\r\n", in1, in2, out);
    }
    else
    {
        val = atoi(inst);
        wireState[out[0]][out[1]] = val;
        fprintf (stdout, "Assinging value %i to wire %i, %i\r\n", val, out[0], out[1]);
    }
    
    return;
}

void part2 (const char* line, size_t len)
{
    // solution for part two here
    return;
}

int negateVal (int val)
{
    return ~val + 1;
}
