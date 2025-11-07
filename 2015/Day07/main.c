#include <ctype.h>
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

bool isWirePort (const char* str);
int negateVal (int val);
void printWireStates ();

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

    // printWireStates ();

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
        val = negateVal (isWirePort (in1) ? wireState[in1[0]][in1[1]] : atoi (in1));
    }
    else if (strstr(inst, "OR"))
    {
        if (sscanf(inst, "%2s OR %2s", in1, in2) != 2)
        {
            fprintf(stderr, "Failed to extract wire in from OR operation\r\n");
            exit (3);
        }
        val = isWirePort (in1) ? wireState[in1[0]][in1[1]] : atoi (in1);
        val |= isWirePort (in2) ? wireState[in2[0]][in2[1]] : atoi (in2);
    }
    else if (strstr(inst, "AND"))
    {
        if (sscanf(inst, "%2s AND %2s", in1, in2) != 2)
        {
            fprintf(stderr, "Failed to extract wire in from AND operation\r\n");
            exit (3);
        }
        val = isWirePort (in1) ? wireState[in1[0]][in1[1]] : atoi (in1);
        val &= isWirePort (in2) ? wireState[in2[0]][in2[1]] : atoi (in2);
    }
    else if (strstr(inst, "LSHIFT"))
    {
        if (sscanf(inst, "%2s LSHIFT %2s", in1, in2) != 2)
        {
            fprintf(stderr, "Failed to extract wire in from LSHIFT operation\r\n");
            exit (3);
        }
        val = isWirePort (in1) ? wireState[in1[0]][in1[1]] : atoi (in1);
        val <<= atoi (in2);
    }
    else if (strstr(inst, "RSHIFT"))
    {
        if (sscanf(inst, "%2s RSHIFT %2s", in1, in2) != 2)
        {
            fprintf(stderr, "Failed to extract wire in from RSHIFT operation\r\n");
            exit (3);
        }
        val = isWirePort (in1) ? wireState[in1[0]][in1[1]] : atoi (in1);
        val >>= atoi (in2);
    }
    else
    {
        val = atoi(inst);
    }

    wireState[out[0]][out[1]] = val;
    fprintf (stdout, "\tWriting %i to wire %i, %i\r\n", val, out[0], out[1]);
    
    return;
}

void part2 (const char* line, size_t len)
{
    // solution for part two here
    return;
}

int negateVal (int val)
{
    return ~val;
}

bool isWirePort (const char* str)
{
    const char* numSet = "1234567890";
    return strspn(str, numSet) != strlen(str);
}

void printWireStates ()
{
    fprintf (stdout, "Wire States\r\n");
    for (int i = 0; i < 0xFF; i++)
    {
        for (int j = 0; j < 0xFF; j++)
        {
            if (wireState[i][j] != 0)
            {
                fprintf (stdout, "%c%c: %i\r\n", i, j, wireState[i][j]);
            }
        }
    }
}
