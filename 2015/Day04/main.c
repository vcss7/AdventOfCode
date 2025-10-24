#include <openssl/md5.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPENSSL_SUPRESS_DEPRECATED 1

void part1 (FILE* fptr);
void part2 (FILE* fptr);

bool checkMD5_pt1 (const unsigned char* md5);
bool checkMD5_pt2 (const unsigned char* md5);

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
    char line[9];

    int i = 0;
    while (true)
    {
        char ch;
        ch = fgetc (fptr);

        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file\r\n");
            exit (1);
        }

        if (ch == EOF || i >= sizeof (line) - 1 || ch == '\n')
        {
            break;
        }

        line[i++] = ch;
    }
    line[i] = '\0';

    fprintf (stdout, "Extracted: \"");
    for (size_t i = 0; i < sizeof (line); i++)
    {
        if (line[i] == '\n')
        {
            fprintf (stdout, "\\n");
            continue;
        }

        if (line[i] == '\0')
        {
            fprintf (stdout, "\\0");
            continue;
        }

        fprintf (stdout, "%c", line[i]);
    }
    fprintf (stdout, "\"\r\n");

    fflush (stdout);

    char* buf         = malloc (32);
    int ans           = 0;
    int limit         = 20000000;
    unsigned char* md = malloc (MD5_DIGEST_LENGTH);

    do
    {
        if (ans >= limit)
        {
            fprintf (stderr, "Error: Reached limit\r\n");
            break;
        }

        // fprintf (stdout, "Combing %s and %d\r\n", line, ans);
        snprintf (buf, 32, "%s%d", line, ans++);
        // fprintf (stdout, "%s\r\n", buf);

        MD5_CTX c;
        MD5_Init (&c);
        MD5_Update (&c, buf, strlen (buf));
        MD5_Final (md, &c);

    } while (!checkMD5_pt1 (md));

    fprintf (stdout, "String %s generated MD5-hash:", buf);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        fprintf (stdout, "%02X", md[i]);
    }
    fprintf (stdout, "\r\n");

    free (md);

    return;
}

void part2 (FILE* fptr)
{
    // solution for part two here
    char line[9];

    int i = 0;
    while (true)
    {
        char ch;
        ch = fgetc (fptr);

        if (ferror (fptr))
        {
            fprintf (stderr, "Error occured while reading file\r\n");
            exit (1);
        }

        if (ch == EOF || i >= sizeof (line) - 1 || ch == '\n')
        {
            break;
        }

        line[i++] = ch;
    }
    line[i] = '\0';

    fprintf (stdout, "Extracted: \"");
    for (size_t i = 0; i < sizeof (line); i++)
    {
        if (line[i] == '\n')
        {
            fprintf (stdout, "\\n");
            continue;
        }

        if (line[i] == '\0')
        {
            fprintf (stdout, "\\0");
            continue;
        }

        fprintf (stdout, "%c", line[i]);
    }
    fprintf (stdout, "\"\r\n");

    fflush (stdout);

    char* buf         = malloc (32);
    int ans           = 0;
    int limit         = 20000000;
    unsigned char* md = malloc (MD5_DIGEST_LENGTH);

    do
    {
        if (ans >= limit)
        {
            fprintf (stderr, "Error: Reached limit\r\n");
            break;
        }

        // fprintf (stdout, "Combing %s and %d\r\n", line, ans);
        snprintf (buf, 32, "%s%d", line, ans++);
        // fprintf (stdout, "%s\r\n", buf);

        MD5_CTX c;
        MD5_Init (&c);
        MD5_Update (&c, buf, strlen (buf));
        MD5_Final (md, &c);

    } while (!checkMD5_pt2 (md));

    fprintf (stdout, "String %s generated MD5-hash:", buf);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        fprintf (stdout, "%02X", md[i]);
    }
    fprintf (stdout, "\r\n");

    free (md);

    return;
}

bool checkMD5_pt1 (const unsigned char* md5)
{
    if (md5[0] == 0x00 && md5[1] == 0x00 && md5[2] < 0x10)
    {
        return true;
    }

    return false;
}

bool checkMD5_pt2 (const unsigned char* md5)
{
    if (md5[0] == 0x00 && md5[1] == 0x00 && md5[2] == 0x00)
    {
        return true;
    }

    return false;
}
