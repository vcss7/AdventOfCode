#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LINES       = 1000;
const int MAX_LINE_LENGTH = 64;

const int SAFETY_TOLERANCE = 1;

typedef enum
{
    MONOTONICITY_NONE       = 0,
    MONOTONICITY_INCREASING = 1,
    MONOTONICITY_DECREASING = 2
} Monotonicity;

int main (void)
{
    FILE* fptr;
    char* file_name = "input";

    fptr = fopen (file_name, "r");

    // check for valid file pointer
    if (fptr == NULL)
    {
        fprintf (stderr, "Could not open file: %s\r\n", file_name);
        exit (1);
    }

    char line[MAX_LINE_LENGTH];

    int safe_count = 0;

    while (fgets (line, sizeof (line), fptr))
    {
        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file: %s\r\n",
                     file_name);
            exit (1);
        }

        fprintf (stdout, "line: %s", line);

        char* token = strtok (line, " ");
        int nums[MAX_LINE_LENGTH];

        // load nums to buffer
        int num_count = 0;
        while (token != NULL)
        {
            nums[num_count] = atoi (token);
            num_count++;
            token = strtok (NULL, " ");
        }

        int seq[num_count - 1];

        // every permutation of nums where one number is skipped
        bool safe_seq;
        for (int i = 0; i < num_count; i++)
        {
            safe_seq = true;
            // load nums to seq
            for (int j = 0; j < num_count; j++)
            {
                // skip a num
                if (i == j)
                    continue;
                if (i > j)
                    seq[j] = nums[j];
                else if (i < j)
                    seq[j - 1] = nums[j];
            }

            // for comparison
            int a = seq[0];
            int b = seq[1];

            // find out monotonicity
            Monotonicity mon = MONOTONICITY_NONE;
            if (a > b)
                mon = MONOTONICITY_DECREASING;
            else if (a < b)
                mon = MONOTONICITY_INCREASING;

            // check safety
            bool safe_step = false;
            for (int j = 0; j < num_count - 2; j++)
            {
                a = seq[j];
                b = seq[j + 1];

                int diff = a - b;

                // check monotonicity is respected
                switch (mon)
                {
                    case MONOTONICITY_DECREASING: safe_step = diff > 0; break;
                    case MONOTONICITY_INCREASING: safe_step = diff < 0; break;
                }

                // check seq doesn't increase or decrease more than 3 at a time
                safe_step = safe_step && abs (diff) <= 3;

                if (!safe_step)
                {
                    safe_seq = false;
                }
            }
            fprintf (stdout, "\r\n");

            if (safe_seq)
                break;
        }
        if (safe_seq)
            safe_count++;
        fprintf (stdout, "\r\n");
    }

    fprintf (stdout, "[Part 1] Safe count: %d\r\n", safe_count);

    fclose (fptr);
    return 0;
}
