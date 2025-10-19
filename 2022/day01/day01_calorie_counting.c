/*
 * File:	day01_counting_calories.c
 *
 * Compile:	gcc -g -Wall -o day01_counting_calories.a day01_counting_calories.c
 *
 * Purpose:	Take a file as input and find the largest sum from collection of
 * 		numbers
 *
 * Input:	File with numbers delimited by new lines and sections of
 * 		numbers delimited by blank lines
 *
 * Output:	Largest sum of separated numbers
 */

#include <stdio.h>
#include <stdlib.h>

void usage (char* prog_name);
void verify_args (int argc, char* argv[]);
void bubblesort_insert (int int_arr[], size_t arr_size, int new_val);
int sum_arr (int int_arr[], size_t size);

int main (int argc, char* argv[])
{
    verify_args (argc, argv);

    FILE* file_p;

    if ((file_p = fopen (argv[1], "r")) == NULL)
    {
        printf ("Can't open %s\n", argv[1]);
        exit (1);
    }

    int top_total_cal[3] = {0, 0, 0};
    int arr_size         = sizeof (top_total_cal) / sizeof (top_total_cal[0]);

    int total_cal = 0;
    char ch[20];

    // while not end of file
    while ((fgets (ch, 20, file_p)) != NULL)
    {
        total_cal = strtol (ch, NULL, 10);

        // parse file using empty line as elf inventory delimiter
        while ((fgets (ch, 20, file_p)) != NULL && *ch != '\n')
        {
            total_cal += strtol (ch, NULL, 10);
        }

        if (total_cal > top_total_cal[arr_size - 1])
        {
            bubblesort_insert (top_total_cal, arr_size, total_cal);
            // highest_value = total_cal;
        }
    }

    fclose (file_p);

    // print results
    fprintf (stdout, "Top Elf Calorie Counts\n");
    for (int i = 0; i < arr_size; i++)
    {
        fprintf (stdout, "\t%d > %d\n", i, top_total_cal[i]);
    }
    fprintf (stdout, "Total = %d\n", sum_arr (top_total_cal, arr_size));

    return 0;
}

/* sums the integers in an array */
int sum_arr (int int_arr[], size_t size)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += int_arr[i];
    }

    return sum;
}

/* inserts a value to an already sorted array in its correct place */
void bubblesort_insert (int int_arr[], size_t arr_size, int new_val)
{
    int temp_val;

    int_arr[arr_size - 1] = new_val;

    for (int i = arr_size - 2; i >= 0; i--)
    {
        if (new_val > int_arr[i])
        {
            temp_val       = int_arr[i];
            int_arr[i]     = new_val;
            int_arr[i + 1] = temp_val;
        }
    }
}

void verify_args (int argc, char* argv[])
{
    // check for arg vector length
    if (argc != 2)
    {
        usage (argv[0]);
        exit (1);
    }
}

void usage (char* prog_name)
{
    fprintf (stderr, "usage is %s <input_file>\n", prog_name);
    fprintf (stderr, "  input_file is file with list of numbers\n");
    fprintf (stderr, "  list of numbers should be delimited with new lines\n");
    fprintf (stderr, "  see: https://adventofcode.com/2022/day/1\n");
}
