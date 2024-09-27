/*
 * Purpose: Solution to Advent of Code Day 04: https://adventofcode.com/2022/day/4
 *
 * Compile: gcc -g -Wall -o camp_cleanup.a day04_camp_cleanup.c
 *
 * Input:   File with pairs of assignments for elves
 *
 * Output:  The number of elves with assignments fully contained by their pairs
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elf
{
    int lower;
    int upper;
};

void usage(char* prog_name);
void verify_args(int argc, char* argv[]);
bool is_enclosed(int lower1, int upper1, int lower2, int upper2);
bool overlaps(int lower1, int upper1, int lower2, int upper2);

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
    char line1[32];
    char line2[32];
    struct Elf elf1;
    struct Elf elf2;

    int enclosed_sum = 0;
    int overlap_sum = 0;
    while ((fgets(line1, 32, file_p)) != NULL)
    {
        if (line1[0] == '\n')
            continue;;

        fputs(line1, stdout);

        strcpy(line1, strtok(line1, ","));
        strcpy(line2, strtok(NULL, ","));

        elf1.lower = atoi(strtok(line1, "-"));
        elf1.upper = atoi(strtok(NULL, "-"));
        fprintf(stdout, "elf1.lower > %d\n", elf1.lower);
        fprintf(stdout, "elf1.upper > %d\n", elf1.upper);

        elf2.lower = atoi(strtok(line2, "-"));
        elf2.upper = atoi(strtok(NULL, "-"));
        fprintf(stdout, "elf2.lower > %d\n", elf2.lower);
        fprintf(stdout, "elf2.upper > %d\n", elf2.upper);

        if (is_enclosed(elf1.lower, elf1.upper, elf2.lower, elf2.upper) ||
            is_enclosed(elf2.lower, elf2.upper, elf1.lower, elf1.upper))
        {
            enclosed_sum++;
        }
        if (overlaps(elf1.lower, elf1.upper, elf2.lower, elf2.upper) ||
            overlaps(elf2.lower, elf2.upper, elf1.lower, elf1.upper))
        {
            overlap_sum++;
        }
    }

    fclose(file_p);

    fprintf(stdout, "Total Enclosed > %d\n", enclosed_sum);
    fprintf(stdout, "Total Overlapping > %d\n", overlap_sum);

    return 0;
}

bool overlaps(int lower1, int upper1, int lower2, int upper2)
{
    return ((lower1 <= lower2 && lower2 <= upper1)
            || (lower1 <= upper2 && upper2 <= upper1));
}

bool is_enclosed(int lower1, int upper1, int lower2, int upper2)
{
    // test if bounds 2 is in bounds 1
    return (lower1 <= lower2 && upper2<= upper1);
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
    fprintf(stderr, "\teach line1 has assignemnts for an elf\n");
    fprintf(stderr, "\tsee: https://adventofcode.com/2022/day/4\n");
}

