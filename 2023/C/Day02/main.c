#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int LINE_LIMIT             = 256;
const int RED_CUBE_COUNT_LIMIT   = 12;
const int GREEN_CUBE_COUNT_LIMIT = 13;
const int BLUE_CUBE_COUNT_LIMIT  = 14;

int get_game_id (const char* line);
bool is_valid_dice_count (int dice_count, char color);
bool is_valid_game (const char* line);
int* get_min_color_counts_rbg (const char* line);
void update_color_counts_rgb (const char* line, int* min_color_counts_rgb);
void update_count_for_color (int* color_count_arr, int dice_count, char color);

int main (void)
{
    FILE* fptr;
    char* file_name = "input.txt";

    fptr = fopen (file_name, "r");

    if (fptr == NULL)
    {
        fprintf (stdout, "Could not open file: %s", file_name);
        exit (0);
    }

    char line[LINE_LIMIT];
    int id_sum       = 0;
    int powerset_sum = 0;

    while (fgets (line, LINE_LIMIT, fptr) != NULL)
    {
        if (ferror (fptr))
        {
            fprintf (stdout, "Error occured while reading file: %s", file_name);
            exit (1);
        }

        // comment out part 2 to see part 1 result
        // part 1
        // if(is_valid_game(line))
        //{
        //    int game_id = get_game_id(line);
        //    id_sum += game_id;
        //}

        // part 2
        int min_color_counts_rgb[3] = {0, 0, 0};
        update_color_counts_rgb (line, min_color_counts_rgb);
        int powerset = 1;
        for (int i = 0; i < 3; i++)
        {
            powerset *= min_color_counts_rgb[i];
        }
        powerset_sum += powerset;
    }

    // fprintf(stdout, "\nSum of ID's of valid game: %i\n", id_sum);
    fprintf (stdout, "Power of the minimum set of cubes in all games: %i",
             powerset_sum);

    fclose (fptr);
    return 0;
}

int get_game_id (const char* line)
{
    int game_id = 0;
    int i       = 0;

    // We know the game id will start on the 5th index of the char array
    while (line[5 + i] >= '0' && line[5 + i] <= '9')
    {
        int next_digit = line[5 + i] - '0';
        game_id        = game_id * 10 + next_digit;
        i++;
    }

    return game_id;
}

bool is_valid_dice_count (int dice_count, char color)
{
    switch (color)
    {
        case 'r':
            if (dice_count <= RED_CUBE_COUNT_LIMIT)
            {
                return true;
            }
            break;
        case 'g':
            if (dice_count <= GREEN_CUBE_COUNT_LIMIT)
            {
                return true;
            }
            break;
        case 'b':
            if (dice_count <= BLUE_CUBE_COUNT_LIMIT)
            {
                return true;
            }
            break;
    }

    return false;
}

bool is_valid_game (const char* line)
{
    char* game_start_ptr = strchr (line, ':');
    char* token          = strtok (&game_start_ptr[1], ";");

    while (token != NULL)
    {
        size_t tok_len          = strlen (token);
        int dice_count          = 0;
        bool prev_char_is_digit = false;

        for (size_t i = 0; i < tok_len; i++)
        {
            if (token[i] >= '0' && token[i] <= '9')
            {
                dice_count         = (dice_count * 10) + token[i] - '0';
                prev_char_is_digit = true;
                continue;
            }
            else if (prev_char_is_digit)
            {
                char color = token[i + 1];
                if (!is_valid_dice_count (dice_count, color))
                {
                    return false;
                }
            }

            dice_count         = 0;
            prev_char_is_digit = false;
        }

        token = strtok (NULL, ";");
    }

    return true;
}

void update_color_counts_rgb (const char* line, int* min_color_counts_rgb)
{
    char* game_start_ptr = strchr (line, ':');
    char* token          = strtok (&game_start_ptr[1], ";");

    while (token != NULL)
    {
        size_t tok_len          = strlen (token);
        int dice_count          = 0;
        bool prev_char_is_digit = false;

        for (size_t i = 0; i < tok_len; i++)
        {
            if (token[i] >= '0' && token[i] <= '9')
            {
                dice_count         = dice_count * 10 + token[i] - '0';
                prev_char_is_digit = true;
                continue;
            }
            else if (prev_char_is_digit)
            {
                char color = token[i + 1];
                update_count_for_color (min_color_counts_rgb, dice_count,
                                        color);
            }

            dice_count         = 0;
            prev_char_is_digit = false;
        }

        token = strtok (NULL, ";");
    }
}

void update_count_for_color (int* color_count_arr, int dice_count, char color)
{
    switch (color)
    {
        case 'r':
            if (color_count_arr[0] < dice_count)
                color_count_arr[0] = dice_count;
            break;
        case 'g':
            if (color_count_arr[1] < dice_count)
                color_count_arr[1] = dice_count;
            break;
        case 'b':
            if (color_count_arr[2] < dice_count)
                color_count_arr[2] = dice_count;
            break;
    }
}
