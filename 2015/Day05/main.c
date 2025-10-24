#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1 (FILE* fptr);
void part2 (FILE* fptr);

// part 1 functions
bool hasVowels (const char* string, const int numVowels);
bool hasNaughtyWords (const char* string);
bool hasCharPair (const char* string);

// part 2 functions
bool hasPairOfCharPairs (const char* string);
bool hasCharSandwich (const char* string);

const char naughtyStrings[4][3] = {"ab", "cd", "pq", "xy"};
const char vowels[5]            = {'a', 'e', 'i', 'o', 'u'};

int main (void)
{
    FILE* fptr;
    char* file_name = "input";

    fptr = fopen (file_name, "r");

    // check for valid file pointer
    if (fptr == NULL)
    {
        fprintf (stderr, "Could not open file: %s\r\n", file_name);
        exit (1);
    }

    part1 (fptr);

    rewind (fptr);

    part2 (fptr);

    fclose (fptr);
    return 0;
}

void part1 (FILE* fptr)
{
    // solution for part one here
    const int LINE_LEN = 17;
    char line[LINE_LEN];

    int niceStringCount = 0;

    while (fgets (line, sizeof (line), fptr))
    {
        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file\r\n");
            exit (1);
        }

        if (!hasNaughtyWords (line) && hasVowels (line, 3)
            && hasCharPair (line))
        {
            niceStringCount++;
        }
    }

    fprintf (stdout, "Part 1: There are %d nice strings\r\n", niceStringCount);

    return;
}

void part2 (FILE* fptr)
{
    // solution for part two here
    const int LINE_LEN = 17;
    char line[LINE_LEN];

    int niceStringCount = 0;
    while (fgets (line, sizeof (line), fptr))
    {
        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file\r\n");
            exit (1);
        }

        if (line[0] == '\n')
        {
            continue;
        }

        if (hasPairOfCharPairs (line) && hasCharSandwich (line))
        {
            niceStringCount++;
        }
    }

    fprintf (stdout, "Part 2: There are %d nice strings\r\n", niceStringCount);

    return;
}

bool hasVowels (const char* string, const int numVowels)
{
    int len        = strlen (string);
    int vowelCount = 0;
    for (int i = 0; i < len; i++)
    {
        switch (string[i])
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u': vowelCount++; break;
            default: break;
        }
    }

    return vowelCount >= numVowels;
}

bool hasNaughtyWords (const char* string)
{
    int numNaughtyWords = sizeof (naughtyStrings) / sizeof (naughtyStrings[0]);

    // check if a "naughty" word exists in the string
    bool hasNaughtyWord = false;
    for (int i = 0; i < numNaughtyWords; i++)
    {
        if (strstr (string, naughtyStrings[i]))
        {
            return true;
        }
    }

    return false;
}

bool hasCharPair (const char* string)
{
    int len = strlen (string);
    for (int i = 1; i < len; i++)
    {
        if (string[i] == string[i - 1])
        {
            return true;
        }
    }

    return false;
}

bool hasPairOfCharPairs (const char* string)
{
    int len = strlen (string);
    char charPair[3];
    charPair[2] = '\0';

    for (int i = 0; i < len - 1; i++)
    {
        char charPair[2];
        charPair[0] = string[i];
        charPair[1] = string[i + 1];
        if (strstr (string + i + 2, charPair))
        {
            return true;
        }
    }

    return false;
}

// char sandwich = (char1)(char2)(char1)
bool hasCharSandwich (const char* string)
{
    int len = strlen (string);
    char ch;
    for (int i = 1; i < len - 1; i++)
    {
        ch = string[i - 1];
        if (ch == string[i + 1])
        {
            return true;
        }
    }

    return false;
}
