#include <vector>
#include <iostream>
#include "Fractal.h"

void printFractals(std::string &path)
{
    FractalFactory::parseCsv(path);
    std::vector<Fractal *> &v = FractalFactory::fractals;
    for (int i = (int) v.size() - 1; i > -1; --i)
    {
        v[i]->populate();
        v[i]->print();
        if (i != -1) { // todo change it or now?
            std::cout << std::endl << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
    FractalFactory::deleteFractals();
}

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
}