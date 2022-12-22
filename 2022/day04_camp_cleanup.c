/*
 * Purpose: Solution to Advent of Code Day 04: https://adventofcode.com/2022/day/4
 *
 * Compile: gcc -g -Wall -o camp_cleanup.a day04_camp_cleanup.c
 *
 * Input:   File with pairs of assignments for elves
 *
 * Output:  The number of elves with assignments fully contained by their pairs
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

    /*** part 1 ***/
    char line1[64];
    char line2[64];

    while ((fgets(line1, 64, file_p)) != NULL)
    {
        if (line1[0] == '\n')
            continue;;

        fgets(line2, 64, file_p);

        fputs(line1, stdout);
        fputs(line2, stdout);
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
    fprintf(stderr, "usage is: %s <input_file>\n", prog_name);
    fprintf(stderr, "\tinput_file is file with pairs of elf assignments\n");
    fprintf(stderr, "\teach line has assignemnts for an elf\n");
    fprintf(stderr, "\tsee: https://adventofcode.com/2022/day/4\n");
}

