//
// Created by Ishay Hil on 30/12/2019.
//

#include "Fractal.h"
#include <cmath>


Fractal::Fractal(int dim)
    : dim(dim)
{}

Sierpinski::Sierpinski(int dim)
    : Fractal(dim)
{
}

void Fractal::print()
{
    _populateFractalLines();
    for (int i = 0; i < pow(_getTemplateSize(), dim); ++i)
    {
        std::cout << fractalLines[i] << std::endl;
    }
    std::cout << std::endl;
}

bool Sierpinski::_canPutSymbol(int row, int col) const
{
    int templateSize = _getTemplateSize();
    while (true)
    {
        if (row == 0 || col == 0)
        {
            return true;
        }
        else if (row % templateSize == 1 && col % templateSize == 1) // must be ' '
        {
            return false;
        }
        // since fractal is a square, dividing with col and row with templateSize will be getting fractal back to dim-1
        row /= templateSize;
        col /= templateSize;
    }
}

void Sierpinski::_populateFractalLines()
{
    int matDim = pow(_getTemplateSize(), dim);
    for (int row = 0; row < matDim; ++row)
    {
        std::string line;
        for (int col = 0; col < matDim; ++col)
        {
            if (_canPutSymbol(row, col))
            {
                line += BASE_CHAR;
            }
            else
            {
                line += " ";
            }
        }
        fractalLines.push_back(line);
        line = "";
    }
}

SierpinskiCarpet::SierpinskiCarpet(int dim)
    : Sierpinski(dim)
{}

int SierpinskiCarpet::_getTemplateSize() const
{
    return 3;
}

SierpinskiTriangle::SierpinskiTriangle(int dim)
    : Sierpinski(dim)
{}

int SierpinskiTriangle::_getTemplateSize() const
{
    return 2;
}