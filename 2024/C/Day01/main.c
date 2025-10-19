#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constants for parsing files
const int MAX_LINES      = 1000;
const int MAX_LINE_CHARS = 64;

int compare_ints (const void *a, const void *b);

int main (void)
{
    FILE *fptr;
    char *file_name = "input";

    fptr = fopen (file_name, "r");

    // check for valid file pointer
    if (fptr == NULL)
    {
        fprintf (stderr, "Could not open file: %s\r\n", file_name);
        exit (EXIT_FAILURE);
    }

    int a[MAX_LINES];
    int b[MAX_LINES];
    int c[MAX_LINES];

    char line[MAX_LINE_CHARS];
    int i = 0;
    while (fgets (line, sizeof (line), fptr))
    {
        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file: %s\r\n",
                     file_name);
            exit (1);
        }

        char *token = strtok (line, " ");
        if (token != NULL)
            a[i] = atoi (token);

        token = strtok (NULL, " ");
        if (token != NULL)
            b[i] = atoi (token);

        // fprintf(stdout, "a=%d\tb=%d\r\n", a[i], b[i]);

        i++;
    }

    fclose (fptr);

    qsort (a, MAX_LINES, sizeof (int), compare_ints);
    qsort (b, MAX_LINES, sizeof (int), compare_ints);

    long long sum       = 0;
    long long sim_score = 0;
    for (int i = 0; i < MAX_LINES; i++)
    {
        // fprintf(stdout, "%d \t%d\r\n", a[i], b[i]);

        // find sum of the differences of each index of the lists
        sum += abs (a[i] - b[i]);

        // count the number of times a[i] occurs in b
        c[i] = 0;
        for (int j = 0; j < MAX_LINES; j++)
        {
            if (a[i] == b[j])
                c[i]++;
        }
        sim_score += a[i] * c[i];
    }

    fprintf (stdout, "[Part 1 Solution] Sum of differences: %d\r\n", sum);
    fprintf (stdout, "[Part 2 Solution] Similarity Score: %d\r\n", sim_score);

    return 0;
}

int compare_ints (const void *a, const void *b)
{
    int c = *((int *) a);
    int d = *((int *) b);

    if (c > d)
        return 1;
    else if (c == d)
        return 0;
    else if (c < d)
        return -1;
}
