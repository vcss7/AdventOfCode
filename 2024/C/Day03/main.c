#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int MAX_LINE_LENGTH = 4 * 4096;

int main(void)
{
    FILE* fptr;
    //char* file_name = "simple_input";
    //char* file_name = "sample_input";
    //char* file_name = "input1";
    //char* file_name = "input2";
    //char* file_name = "input3";
    //char* file_name = "input4";
    //char* file_name = "input5";
    char* file_name = "input";

    fptr = fopen(file_name, "r");

    // check for valid file pointer
    if(fptr == NULL)
    {
        fprintf(stderr, "Could not open file: %s\r\n", file_name);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];

    long long sum = 0;
    while(fgets(line, sizeof(line), fptr))
    {
        if(ferror(fptr))
        {
            fprintf(stderr, "Error occured while reading file: %s\r\n", file_name);
            exit(1);
        }

        unsigned int line_length = strlen(line);

        // iterate through line looking for instances of `mul(a,b)` where a and
        // b are valid numbers
        bool multiply = true;
        for (unsigned int i = 0; i < line_length - 7; i++)
        {
            //fprintf(stdout, "%s", line + i);

            // enable or disable multiplication
            if (strncmp(line + i, "do()", 4) == 0)
            {
                fprintf(stdout, "Enabling multiplication..\r\n");
                multiply = true;
                sleep(5);
            }
            else if (strncmp(line + i, "don't()", 7) == 0)
            {
                fprintf(stdout, "Disabling multiplication..\r\n");
                multiply = false;
                sleep(5);
            }

            // skip if last instructions is `don't()`
            if (!multiply) continue;

            // skip if not at an index with starting string `mul(`
            if (strncmp(line + i, "mul(", 4) != 0) continue;

            fprintf(stdout, "Found an instance of mul(!!\r\n");
            fprintf(stdout, "%.30s\r\n", line + i);

            // skip
            i += 4;

            // storage variables and flags
            int a, b = 0;
            bool valid = false;

            // load first digit
            a = 0;
            while (line[i] >= '0' && line[i] <= '9')
            {
                a = a * 10 + line[i] - '0';
                i++;
            }

            // check valid format
            if (line[i] == ',')
            {
                i++;

                // load second digit
                b = 0;
                while (line[i] >= '0' && line[i] <= '9')
                {
                    b = b * 10 + line[i] - '0';
                    i++;
                }

                // check valid format
                if (line[i] == ')')
                {
                    fprintf(stdout, "a=%d b=%d\r\n", a, b);
                    sum += (a * b);
                }
            }

            fprintf(stdout, "Adding %d..\r\n", (a * b));
            fprintf(stdout, "Running sum: %d\r\n", sum);

            sleep(5);
        }
    }

    // part 1
    //172402183 too high
    
    // part 2
    // 93994894 too high

    fprintf(stdout, "[Part 01] Sum: %d\r\n", sum);

    fclose(fptr);
    return 0;
}

