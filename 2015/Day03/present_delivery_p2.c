#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Coordinate
{
    int x;
    int y;
} Coord;

typedef struct House
{
    int visitCount;
    Coord coord;
} House;

House* createHouse (int x, int y);
House* findHouse (House** houses, size_t numHouses, int x, int y);
void freeHouses (House** houses, size_t numHouses);
void printHouse (House house);
void processVisit (Coord loc, House** houses, size_t numHouses);
void updateLoc (Coord* coord, char direction);

int main (void)
{
    FILE* fptr;
    char* input_file = "input.txt";

    fptr = fopen (input_file, "r");

    if (fptr == NULL)
    {
        fprintf (stderr, "Could not open file: %s\r\n", input_file);
        exit (1);
    }
    else
    {
        fprintf (stdout, "Opened %s successfully.\r\n", input_file);
    }

    Coord agentOneLoc = {0, 0};
    Coord agentTwoLoc = {0, 0};

    int totalVisits  = 1;
    int uniqueVisits = 1;

    House** houses;
    size_t numHouses = 0;
    houses           = (House**) malloc (sizeof (House*));
    houses[0]        = createHouse (0, 0);
    numHouses++;

    char nextMove;
    while (true)
    {
        House* currHouse;

        /** Agent one moves */
        nextMove = fgetc (fptr);
        if (nextMove == EOF)
        {
            break;
        }

        totalVisits += 1;

        updateLoc (&agentOneLoc, nextMove);
        currHouse = findHouse (houses, numHouses, agentOneLoc.x, agentOneLoc.y);

        if (currHouse == NULL)
        {
            currHouse = createHouse (agentOneLoc.x, agentOneLoc.y);

            House** temp = NULL;
            temp
                = (House**) realloc (houses, (numHouses + 1) * sizeof (House*));
            if (temp == NULL)
            {
                fprintf (stdout, "Error: Failed to reallocate memory\r\n");
                freeHouses (houses, numHouses);
                return 1;
            }

            houses            = temp;
            houses[numHouses] = currHouse;
            numHouses++;
        }

        currHouse->visitCount++;

        /** Agent two moves */
        nextMove = fgetc (fptr);
        if (nextMove == EOF)
        {
            break;
        }

        totalVisits += 1;

        updateLoc (&agentTwoLoc, nextMove);
        currHouse = findHouse (houses, numHouses, agentTwoLoc.x, agentTwoLoc.y);

        if (currHouse == NULL)
        {
            currHouse = createHouse (agentTwoLoc.x, agentTwoLoc.y);

            House** temp = NULL;
            temp
                = (House**) realloc (houses, (numHouses + 1) * sizeof (House*));
            if (temp == NULL)
            {
                fprintf (stdout, "Error: Failed to reallocate memory\r\n");
                freeHouses (houses, numHouses);
                return 1;
            }

            houses            = temp;
            houses[numHouses] = currHouse;
            numHouses++;
        }

        currHouse->visitCount++;
    }

    fprintf (stdout, "Visited %zu houses\r\n", numHouses);
    fprintf (stdout, "Made %d visits\r\n", totalVisits);

    freeHouses (houses, numHouses);

    fclose (fptr);
    return 0;
}

House* createHouse (int x, int y)
{
    House* newHouse = malloc (sizeof (House));

    newHouse->coord.x    = x;
    newHouse->coord.y    = y;
    newHouse->visitCount = 0;

    return newHouse;
}

House* findHouse (House** houses, size_t numHouses, int x, int y)
{
    for (size_t i = 0; i < numHouses; i++)
    {
        if (houses[i]->coord.x == x && houses[i]->coord.y == y)
        {
            return houses[i];
        }
    }

    return NULL;
}

void freeHouses (House** houses, size_t numHouses)
{
    for (size_t i = 0; i < numHouses; i++)
    {
        free (houses[i]);
    }

    return;
}

void printHouse (House house)
{
    fprintf (stdout, "House location {%d, %d} visited %d time(s)\r\n",
             house.coord.x, house.coord.y, house.visitCount);

    return;
}

void processVisit (Coord loc, House** houses, size_t numHouses)
{
    return;
}

void updateLoc (Coord* coord, char direction)
{
    switch (direction)
    {
        case '^': coord->y++; break;
        case 'v': coord->y--; break;
        case '>': coord->x++; break;
        case '<': coord->x--; break;
        default: break;
    }

    return;
}
