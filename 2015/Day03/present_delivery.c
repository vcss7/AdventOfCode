#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Coordinate
{
    int x;
    int y;
};

struct House
{
    int visited_count;
    struct Coordinate coord;
};

struct House find_house(struct House* houses, struct Coordinate house_coord);

int main(void)
{
    FILE* fptr;
    char* input_file = "test_input1.txt";

    fptr = fopen(input_file, "r");

    if(fptr == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", input_file);
        exit(1);
    }
    else
    {
        fprintf(stdout, "Opened %s successfully.\n", input_file);
    }

    struct House houses[10][12];
    int row_length = sizeof(houses[0])/sizeof(houses[0][0]);
    int end_i = row_length / 2;
    int begin_i = end_i - row_length;
    int col_length = sizeof(houses)/sizeof(houses[0]);
    int end_j = col_length / 2;
    int begin_j = end_j - col_length;

    for(int i = begin_i; i < end_i; i++)
    {
        for(int j = begin_j; j < end_j; j++)
        {
            houses[i][j].visited_count = 0;
            houses[i][j].coord.x = i;
            houses[i][j].coord.y = j;
        }
    }

    struct Coordinate curr_coord = {0, 0};
    find_house(houses, curr_coord);

    exit(0);

    char direction;
    do
    {
        direction = fgetc(fptr);
        switch (direction)
        {
            case '^':
                curr_coord.x++;
                break;
            case 'v':
                curr_coord.x--;
                break;
            case '<':
                curr_coord.y--;
                break;
            case '>':
                curr_coord.y++;
                break;
        }
        houses[curr_coord.x][curr_coord.y].visited_count++;

        fprintf(stdout, "Visited house at: [%i, %i]\n", curr_coord.x, curr_coord.y);
        fprintf(stdout, "Visited count: %i\n", houses[curr_coord.x][curr_coord.y]);
    } while(direction != EOF);

    fprintf(stdout, "Current X: %i\nCurrent Y: %i\n", curr_coord.x, curr_coord.y);

    fclose(fptr);
    return 0;
}

struct House find_house(struct House* houses, struct Coordinate house_coord)
{
    fprintf(stdout, "Successfully entered the \"find_house\" function.\n");
    return houses[0][0];
}
