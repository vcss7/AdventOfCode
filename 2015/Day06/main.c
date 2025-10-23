#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
int lights[1000][1000];
void part1 (FILE* fptr);
void part2 (FILE* fptr);

void initLights ();

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

    initLights();
    part1 (fptr);

    rewind (fptr);

    initLights();
    part2 (fptr);

    fclose (fptr);
    return 0;
}

void initLights ()
{
    for (int x = 0; x < 1000; x++)
    {
        for (int y = 0; y < 1000; y++)
        {
            lights[x][y] = 0;
        }
    }

    return;
}

void part1 (FILE* fptr)
{
    // solution for part one here
    char line[64];
    size_t len = sizeof(line);

    while (fgets(line, len, fptr))
    {
        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file\r\n");
            exit (1);
        }

        // fprintf (stdout, "%s", line);

        int x1, y1;
        int x2, y2;
        if (sscanf (line, "turn on %d,%d through %d,%d\n", &x1, &y1, &x2, &y2) == 4)
        {
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    lights[x][y] = true;
                }
            }
        }
        else if (sscanf (line, "turn off %d,%d through %d,%d\n", &x1, &y1, &x2, &y2) == 4)
        {
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    lights[x][y] = false;
                }
            }
        }
        else if (sscanf (line, "toggle %d,%d through %d,%d\n", &x1, &y1, &x2, &y2) == 4)
        {
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    lights[x][y] = !lights[x][y];
                }
            }
        }

        // part1 (line, len);
        // part2 (line, len);
    }

    int lightsOnCount = 0;
    for (int x = 0; x < 1000; x++)
    {
        for (int y = 0; y < 1000; y++)
        {
            if (lights[x][y] == true)
            {
                lightsOnCount++;
            }
        }
    }

    fprintf (stdout, "Part 1: There are %d lights on\r\n", lightsOnCount);

    return;
}

void part2 (FILE* fptr)
{
    // solution for part two here
    return;
}
