/*
 * Purpose: Solution to Advent of Code Day 3 https://adventofcode.com/2022/day/3
 *
 * Compile: gcc -g -Wall -o rucksack_reorganization.a
 * day03_rucksack_reorganization.c
 *
 * Input:   File with string delimited by new lines
 *
 * Output:  The sum of the priority points for all "rucksacks" (strings)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void verify_args (int argc, char* argv[]);
void usage (char* prog_name);
char find_matching_char_in_halves (char* line);
int get_priority_value (char ch);
char find_matching_char_in_set (char* line1, char* line2, char* line3);

int main (int argc, char* argv[])
{
    verify_args (argc, argv);

    FILE* file_p = NULL;

    if ((file_p = fopen (argv[1], "r")) == NULL)
    {
        fprintf (stderr, "Could not open %s", argv[1]);
        exit (1);
    }

    char line1[64];
    char line2[64];
    char line3[64];
    char comm_ch;
    int sum = 0;
    while (fgets (line1, 64, file_p) != NULL)
    {
        if (line1[0] == '\n')  // skip new lines
            continue;

        fgets (line2, 64, file_p);
        fgets (line3, 64, file_p);

        // one rucksack here
        // comm_ch = find_matching_char_in_halves(line);
        comm_ch = find_matching_char_in_set (line1, line2, line3);

        // assign priority value to char
        sum += get_priority_value (comm_ch);
    }

    fclose (file_p);

    fprintf (stdout, "Sum of priority values: %d\n", sum);

    return 0;
}

char find_matching_char_in_set (char* line1, char* line2, char* line3)
{
    char ch;

    for (int i = 0; i < strlen (line1); i++)
    {
        ch = line1[i];

        if (strchr (line2, ch) != NULL && strchr (line3, ch) != NULL)
        {
            return ch;
        }
    }

    return 0;
}

char find_matching_char_in_halves (char* line)
{
    char ch1;
    char ch2;
    size_t substr_size = strlen (line) / 2;

    for (int i = 0; i < substr_size; i++)
    {
        ch1 = line[i];
        for (int j = 0; j < substr_size; j++)
        {
            ch2 = line[j + substr_size];
            if (ch1 == ch2)
            {
                return ch1;
            }
        }
    }

    return 0;
}

int get_priority_value (char ch)
{
    if (ch >= 'a')
    {
        return (ch - 'a' + 1);
    }
    else
    {
        return (ch - 'A' + 26 + 1);
    }
}

void verify_args (int argc, char* argv[])
{
    if (argc != 2)
    {
        usage (argv[0]);
        exit (1);
    }
}

void usage (char* prog_name)
{
    fprintf (stderr, "Usage is %s <input_file>\n", prog_name);
    fprintf (stderr, "\tinput_file is file with list of numbers\n");
    fprintf (stderr, "\tlist of numbers is delimited by new line\n");
    fprintf (stderr, "\tsee: https://addventofcode.com/2022/day/3\n");
}
