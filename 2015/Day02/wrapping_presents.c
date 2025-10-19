#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LINE_LENGTH = 20;
const char DELIMITER[]    = "x";

int calculate_slack (int faceAreaA, int faceAreaB, int faceAreaC);
int calculate_wrapping_paper (int width, int height, int length);
int calculate_ribbon (int width, int height, int length);
int calculate_bow (int width, int height, int length);

struct RectanglePrism
{
    int width;
    int height;
    int length;
};

int main (void)
{
    FILE* fptr;

    fptr = fopen ("input.txt", "r");

    if (fptr == NULL)
    {
        perror ("Could not open file.\n");
        exit (1);
    }

    int total_wrapping_paper = 0;
    int total_ribbon         = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets (line, sizeof (line), fptr) != NULL)
    {
        struct RectanglePrism rp = (struct RectanglePrism) {0};

        rp.width  = atoi (strtok (line, DELIMITER));
        rp.height = atoi (strtok (NULL, DELIMITER));
        rp.length = atoi (strtok (NULL, DELIMITER));

        total_wrapping_paper
            += calculate_wrapping_paper (rp.width, rp.height, rp.length);
        total_ribbon += calculate_ribbon (rp.width, rp.height, rp.length);
        total_ribbon += calculate_bow (rp.width, rp.height, rp.length);
    }

    printf ("Total wrapping paper needed: %i\n", total_wrapping_paper);
    printf ("Total ribbon needed: %i\n", total_ribbon);

    fclose (fptr);
    return 0;
}

int calculate_slack (int faceAreaA, int faceAreaB, int faceAreaC)
{
    int slack;

    if (faceAreaA <= faceAreaB && faceAreaA <= faceAreaC)
        slack = faceAreaA;
    else if (faceAreaB <= faceAreaC)
        slack = faceAreaB;
    else
        slack = faceAreaC;

    return slack;
}

int calculate_wrapping_paper (int width, int height, int length)
{
    int faceAreaA = length * width;
    int faceAreaB = width * height;
    int faceAreaC = length * height;

    int slack = calculate_slack (faceAreaA, faceAreaB, faceAreaC);

    return 2 * faceAreaA + 2 * faceAreaB + 2 * faceAreaC + slack;
}

int calculate_ribbon (int width, int height, int length)
{
    int ribbon_length = width + height + length;

    if (width > height && width > length)
        ribbon_length -= width;
    else if (height > length)
        ribbon_length -= height;
    else
        ribbon_length -= length;

    return 2 * ribbon_length;
}

int calculate_bow (int width, int height, int length)
{
    return width * height * length;
}
