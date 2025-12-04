#include <iostream>
#include <fstream>
#include <string>

void part1 (std::string& line);
void part2 (std::string& line);

int main (int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Please provide an input file" << std::endl;
        return 1;
    }

    std::string filename = argv[1]; 
    std::ifstream fstm(filename, std::ios::in);

    // check for valid file
    if (!fstm.is_open())
    {
        std::cerr << "Could not open file: " << filename << std::endl;
        return 1;
    }

    // solution for part one here
    std::string line;
    size_t len = sizeof (line);

    while (std::getline(fstm, line))
    {
        std::cout << line << std::endl;

        part1 (line);
        part2 (line);
    }

    fstm.close();
    return 0;
}

void part1 (std::string& line)
{
    // solution for part one here
    return;
}
void part2 (std::string& line)
{
    // solution for part two here
    return;
}
