//
// Created by Ishay Hil on 01/01/2020.
//

#include <vector>
#include <iostream>
#include <fstream>
#include "Fractal.h"


std::vector<Fractal *> FractalFactory::fractals;

void printFractals(std::string &path)
{
    FractalFactory::parseCsv(path);
    std::vector<Fractal *> v = FractalFactory::fractals;
    for (int i = v.size(); i > -1; --i)
    {
        v[i]->print();
    }
}

int main(int argc, char **args)
{
    if (argc != 2)
    {
        std::cout << INVALID_USAGE << std::endl;
    }
    std::string path;
    for (size_t i = 0; i < strlen(args[1]); ++i)
    {
        path += args[1][i];
    }
    printFractals(path);
}