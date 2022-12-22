/* 
 * Purpose: Solution to Advent of Code Day 3 https://adventofcode.com/2022/day/3
 *
 * Compile: gcc -g -Wall -o rucksack_reorganization.a day03_rucksack_reorganization.c
 * 
 * Input:   File with string delimited by new lines
 *
 * Output:  The sum of the priority points for all "rucksacks" (strings)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void verify_args(int argc, char* argv[]);
void usage(char* prog_name);
char find_matching_char(char* str1, char* str2);
int get_priority_value(char ch);

int main (int argc, char* argv[])
{
    verify_args(argc, argv);

    FILE* file_p = NULL;

    if ((file_p = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Could not open %s", argv[1]);
        exit(1);
    }

    char line[64];
    while (fgets(line, 64, file_p) != NULL)
    {
        if (line[0] == '\n') // skip new lines
            continue;

        // one rucksack here
        fprintf(stdout, "length: %ld\n", strlen(line));
        fputs(line, stdout);

        // split the string in half
        // iterate through each character in string1 to see if it exist in string2
        // if it exists, add appropriate prioty value to sum and continue to next rucksack
    }

    fclose(file_p);

    return 0;
}

char find_matching_char(char* str1, char* str2)
{
    return 0;
}

int get_priority_value(char ch)
{
    return 0;
}

void verify_args(int argc, char* argv[])
{
    if (argc != 2)
    {
        usage(argv[0]);
        exit(1);
    }
}

void usage(char* prog_name)
{
    fprintf(stderr, "Usage is %s <input_file>\n", prog_name);
    fprintf(stderr, "\tinput_file is file with list of numbers\n");
    fprintf(stderr, "\tlist of numbers is delimited by new line\n");
    fprintf(stderr, "\tsee: https://addventofcode.com/2022/day/3\n");
}

