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

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char* prog_name);
void verify_args(int argc, char* argv[]);

int main (int argc, char* argv[])
{
    verify_args(argc, argv);

    FILE *file_p;

    if ((file_p = fopen(argv[1], "r")) == NULL)
    {
        printf("Can't open %s\n", argv[1]);
	exit(1);
    }

    uint64_t total_calories = 0; 
    uint64_t highest_value = 0;

    char ch[20];

    while ( (fgets(ch, 20, file_p)) != NULL)
    {
        total_calories = strtol(ch, NULL, 10);

	while ( (fgets(ch, 20, file_p)) != NULL && *ch != '\n')
	{
	    total_calories += strtol(ch, NULL, 10);
	}

	if (total_calories > highest_value)
	{
	    highest_value = total_calories;
	}
    }

    fclose(file_p);

    fprintf(stdout, "Highest Calories : %ld\n", highest_value);

    return 0;
}

void verify_args(int argc, char* argv[])
{
    // check for arg vector length
    if (argc != 2)
    {
        usage(argv[0]);
	exit(1);
    }
}

void usage(char* prog_name)
{
    fprintf(stderr, "usage is %s <input_file>\n", prog_name);
    fprintf(stderr, "  input_file is file with list of numbers\n");
    fprintf(stderr, "  list of numbers should be delimited with new lines\n");
    fprintf(stderr, "  see: https://adventofcode.com/2022/day/1\n");
}


