/*
 * File:    day02_rock_paper_scissors.c
 *
 * Compile: gcc -g -Wall -o day02_rock_paper_scissors.a day02_rock_paper_scissors.c
 *
 * Purpose: Solution to AdventOfCode Problem https://adventofcode.com/2022/day/2
 *
 * Input:   File with A B or C in first column representing opponents shape and X
 *          Y or Z in second column representing our shape. Each line is a game.
 *
 * Output:  Final score for all games.
 */

#include <stdio.h>
#include <stdlib.h>

void usage(char* prog_name);
void verify_args(int argc, char* argv[]);
int score_match_p1(char opp_shape, char my_shape);
int score_match_p2(char opp_shape, char outcome);
void convert_to_rps(char *shape);
int points_from_shape(char shape);
int points_from_match_p1(char opp_shape, char my_shape);
int points_from_match_p2(char outcome);
char pick_shape_from_outcome(char opp_shape, char outcome);

int main(int argc, char* argv[])
{
    verify_args(argc, argv);

    FILE* file_p = NULL;

    if ((file_p = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Could not open: %s\n", argv[1]);
        exit(1);
    }

    int total_score = 0;
    char line[4];
    while (fgets(line, 4, file_p) != NULL)
    {
        // skip end of line new line characters
        if (line[0] == '\n')
        {
            continue;
        }

        // line[0] is opp shape: A B or C
        // line[2] is your shape: X Y or Z

        //total_score += score_match_p1(line[0], line[2]);
        total_score += score_match_p2(line[0], line[2]);
    }

    fclose(file_p);

    fprintf(stdout, "Total score: %d\n", total_score);

    return 0;
}

int score_match_p1(char opp_shape, char my_shape)
{
    convert_to_rps(&opp_shape);
    convert_to_rps(&my_shape);

    fprintf(stdout, "Game ===\n");
    fprintf(stdout, "Opp shape: %c\n", opp_shape);
    fprintf(stdout, "My shape:  %c\n", my_shape);

    int score = 0;
    score += points_from_shape(my_shape);
    score += points_from_match_p1(opp_shape, my_shape);

    fprintf(stdout, "Score: %d\n\n", score);

    return score;
}

int score_match_p2(char opp_shape, char outcome)
{
    convert_to_rps(&opp_shape);
    char my_shape = pick_shape_from_outcome(opp_shape, outcome);

    fprintf(stdout, "Game ===\n");
    fprintf(stdout, "Opp shape: %c\n", opp_shape);
    fprintf(stdout, "My shape:  %c\n", my_shape);

    int score = 0;
    score += points_from_shape(my_shape);
    score += points_from_match_p2(outcome);

    fprintf(stdout, "Score: %d\n\n", score);

    return score;
}

char pick_shape_from_outcome(char opp_shape, char outcome)
{
    switch(outcome)
    {
        case 'X' : // return loss
            switch(opp_shape)
            {
                case 'R' : return 'S';
                case 'P' : return 'R';
                case 'S' : return 'P';
            }
        case 'Y' : // return draw
            switch(opp_shape)
            {
                case 'R' : return 'R';
                case 'P' : return 'P';
                case 'S' : return 'S';
            }
        case 'Z' : // return win
            switch(opp_shape)
            {
                case 'R' : return 'P';
                case 'P' : return 'S';
                case 'S' : return 'R';
            }
    }

    return '0';
}

int points_from_match_p2(char outcome)
{
    switch(outcome)
    {
        case 'X' : return 0;
        case 'Y' : return 3;
        case 'Z' : return 6;
    }

    return 0;
}

int points_from_match_p1(char opp_shape, char my_shape)
{
    switch(opp_shape)
    {
        case 'R':
            fprintf(stdout, "Scoring for opp played: R\n");
            switch(my_shape)
            {
                case 'R' : return 3;
                case 'P' : return 6;
            }
            break;
        case 'P':
            fprintf(stdout, "Scoring for opp played: P\n");
            switch(my_shape)
            {
                case 'P' : return 3;
                case 'S' : return 6;
            }
            break;
        case 'S':
            fprintf(stdout, "Scoring for opp played: S\n");
            switch(my_shape)
            {
                case 'S' : return 3;
                case 'R' : return 6;
            }
            break;
    }

    return 0;
}

int points_from_shape(char shape)
{
    switch(shape)
    {
        case 'R' : return 1;
        case 'P' : return 2;
        case 'S' : return 3;
    }

    return 0;
}

void convert_to_rps(char* shape)
{
    // convert either A B C system or X Y Z system to R P S system
    switch(*shape)
    {
        case 'A' :
        case 'X' :
              *shape = 'R';
              break;
        case 'B' :
        case 'Y' :
              *shape = 'P';
              break;
        case 'C' :
        case 'Z' :
              *shape = 'S';
              break;
    }
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
    fprintf(stderr, "\teach line contains A B or C in files column\n");
    fprintf(stderr, "\t                   X Y or Z in second column\n");
}

