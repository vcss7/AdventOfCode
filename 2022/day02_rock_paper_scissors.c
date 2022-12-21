/*
 * File:    day02_rock_paper_scissors.c
 *
 * Compile: gcc -g -Wall -o day02_rock_paper_scissors.a day02_rock_paper_scissors.c
 *
 * Purpose: Solution to AdventOfCode Problem https://adventofcode.com/2022/day/2
 *
 * Input:   File with A B or C in first column representing opponents move and X
 *          Y or Z in second column representing our move. Each line is a game.
 *
 * Output:  Final score for all games.
 */

#include <stdio.h>
#include <stdlib.h>

void usage(char* prog_name);
void verify_args(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    verify_args(argc, argv);

    return 0;
}

void verify_args(int argc, char* argv[])
{
    if (argc != 2)
    {
        usage(argv[1]);
        exit(1);
    }
}

void usage(char* prog_name)
{
    fprintf(stderr, "usage is %s <input file>\n", prog_name);
    fprintf(stderr, "\tinput file is file with predicted games\n");
    fprintf(stderr, "\teach game is delimited by new lines\n");
    fprintf(stderr, "\teach line contains A B or C in files column\n"};
    fprintf(stderr, "\t                   X Y or Z in second column\n");
}

