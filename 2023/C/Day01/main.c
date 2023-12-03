#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LINE_LENGTH = 60;

int get_digit_from_word_form(char* string);

int main(void)
{
    FILE* fptr;
    char* file_name = "input.txt";

    fptr = fopen(file_name, "r");

    if(fptr == NULL)
    {
        fprintf(stderr, "Could not open file: %s", file_name);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int total = 0;

    while(fgets(line, sizeof(line), fptr))
    {
        if(ferror(fptr))
        {
            fprintf(stderr, "Error occured while reading file: %s\n", file_name);
            exit(1);
        }

        size_t line_len = strlen(line);
        bool got_first_digit = false;
        int first_digit;
        int last_digit;

        fprintf(stdout, "Line: %s", line);

        for(int i = 0; i < line_len; i++)
        {
            int digit_from_string = get_digit_from_word_form(&line[i]);
            if(digit_from_string != -1)
            {
                if(!got_first_digit)
                {
                    first_digit = digit_from_string;
                    got_first_digit = true;
                }
                last_digit = digit_from_string;
            }

            if(line[i] >= '0' && line[i] <= '9')
            {
                if(!got_first_digit)
                {
                    first_digit = line[i] - '0';
                    got_first_digit = true;
                }
                last_digit = line[i] - '0';
            }
        }
        //fprintf(stdout, "F: %i\tL: %i\n", first_digit, last_digit);

        total += first_digit * 10 + last_digit;
    }
    fprintf(stdout, "Total calibration values: %i\n", total);

    fclose(fptr);
    return 0;
}

int get_digit_from_word_form(char* string)
{
    // check all digit word forms with length 5
    if(strncmp("three", string, 5) == 0)
        return 3;
    if(strncmp("seven", string, 5) == 0)
        return 7;
    if(strncmp("eight", string, 5) == 0)
        return 8;

    // check all digit word forms with length 4
    if(strncmp("four", string, 4) == 0)
        return 4;
    if(strncmp("five", string, 4) == 0)
        return 5;
    if(strncmp("nine", string, 4) == 0)
        return 9;

    // check all digit word forms with length 3
    if(strncmp("one", string, 3) == 0)
        return 1;
    if(strncmp("two", string, 3) == 0)
        return 2;
    if(strncmp("six", string, 3) == 0)
        return 6;
    return -1;
}

