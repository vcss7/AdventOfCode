#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_BUFF_LENGTH = 256;

void part1 (FILE* fptr);
bool is_digit (char num);
bool is_next_to_symbol (char* prev_line, char* curr_line, char* next_line,
                        int i);
bool is_symbol (char ch);

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf (stderr, "No file given\n");
        exit (1);
    }

    FILE* fptr = fopen (argv[1], "r");

    if (fptr == NULL)
    {
        fprintf (stderr, "Could not open file: %s\n", argv[1]);
        exit (1);
    }

    part1 (fptr);

    fclose (fptr);
    return 0;
}

void part1 (FILE* fptr)
{
    char prev_line[MAX_BUFF_LENGTH];
    char curr_line[MAX_BUFF_LENGTH];
    char next_line[MAX_BUFF_LENGTH];

    memset (prev_line, 0, MAX_BUFF_LENGTH);
    memset (curr_line, 0, MAX_BUFF_LENGTH);
    memset (next_line, 0, MAX_BUFF_LENGTH);

    int sum = 0;

    while (!feof (fptr))
    {
        // Update lines
        strcpy (prev_line, curr_line);
        strcpy (curr_line, next_line);
        fgets (next_line, MAX_BUFF_LENGTH, fptr);

        bool prev_char_is_digit    = false;
        bool num_is_next_to_symbol = false;
        int num                    = 0;

        for (int i = 0; i < strlen (curr_line); i++)
        {
            if (is_digit (curr_line[i]))
            {
                // Keep track of numbers with more than one digit
                num = num * 10 + curr_line[i] - '0';

                if (is_next_to_symbol (prev_line, curr_line, next_line, i))
                {
                    num_is_next_to_symbol = true;
                }

                if (i < strlen (curr_line) && !is_digit (curr_line[i + 1])
                    && num_is_next_to_symbol)
                {
                    sum += num;
                }

                prev_char_is_digit = true;
            }
            else
            {
                prev_char_is_digit    = false;
                num_is_next_to_symbol = false;
                num                   = 0;
            }
        }
    }

    fprintf (stdout, "Sum %i\n", sum);
}

bool is_digit (char ch)
{
    return (ch >= '0' && ch <= '9');
}

bool is_next_to_symbol (char* prev_line, char* curr_line, char* next_line,
                        int i)
{
    if (i > 0 && i < strlen (curr_line) - 1)
    {
        for (int j = i - 1; j <= i + 1; j++)
        {
            if (is_symbol (prev_line[j]) || is_symbol (curr_line[j])
                || is_symbol (next_line[j]))
                return true;
        }
    }
    return false;
}

bool is_symbol (char ch)
{
    // return ch == '*' || ch == '#' || ch == '+' || ch == '$';
    return (ch == '*' || ch == '@' || ch == '#' || ch == '+' || ch == '$'
            || ch == '%' || ch == '=' || ch == '&' || ch == '/');
}
