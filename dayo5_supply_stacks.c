/*
 * Purpose: Solution for Day 5 AdventOfCode https://adventofcode.com/2022/day/5
 *
 * Compile: gcc -g - Wall -o supply_stacks.a day05_supply_stacks.c
 *
 * Input:   File containing stack configurations and movement schemas
 *
 * Output:  Create that ends up at the top of each stack
 */

#include <stdio.h>
#include <stdlib.h>

void usage(char* prog_name);
void verify_args(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    verify_args(argc, argv);

    FILE* file_p = NULL;

    if ((file_p = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        exit(1);
    }

    char line[64];
    while (fgets(line, 64, file_p))
    {
        fputs(line, stdout);
    }

    fclose(file_p);

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
    fprintf(stderr, "usage is %s <input_file>\n", prog_name);
    fprintf(stderr, "\t<input_file> is the file with supply stacks and the rearrangement schema\n");
    fprintf(stderr, "\tsee: https://adventofcode.com/2022/day/5\n");
}

