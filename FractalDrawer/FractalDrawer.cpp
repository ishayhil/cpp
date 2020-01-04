#include <vector>
#include <iostream>
#include "Fractal.h"

/**
 * prints the fractals by the definition in the given path
 * @param path the given csv path
 */
void printFractals(std::string &path)
{
    FractalFactory::parseCsv(path);
    std::vector<Fractal *> &v = FractalFactory::fractals;
    for (int i = (int) v.size() - 1; i > -1; --i)
    {
        v.at(i)->populate();
        v.at(i)->print();
        if (i != -1)
        {
            std::cout << std::endl << std::endl;
        }
        else
        {
            std::cout << std::endl;
        }
    }
    FractalFactory::deleteFractals();
}

/**
 * the main function. prints the fractals by the definition in the given path
 * @param argc number of args (min = 1)
 * @param args the program args
 * @return EXIT_SUCCESS if success, EXIT_FAILURE otherwise.
 */
int main(int argc, char **args)
{
    if (argc != 2)
    {
        std::cout << INVALID_USAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string path;
    for (size_t i = 0; i < strlen(args[1]); ++i)
    {
        path += args[1][i];
    }
    printFractals(path);
    return EXIT_SUCCESS;
}