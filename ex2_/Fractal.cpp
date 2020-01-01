//
// Created by Ishay Hil on 30/12/2019.
//

#include "Fractal.h"
#include <cmath>

// ********************** Fractal ********************** //
Fractal::Fractal(int dim)
    : dim(dim)
{}

void Fractal::print()
{
//    _populateFractalLines();
    for (int i = 0; i < pow(_getTemplateSize(), dim); ++i)
    {
        std::cout << fractalLines.at(i) << std::endl;
    }
    std::cout << std::endl;
}

void Fractal::populate()
{
    if (dim == 1)
    {
        this->fractalLines = _getTemplate();
        return;
    }

    int len = pow(_getTemplateSize(), dim - 1);
    Fractal *prev = PrevDim();
    prev->populate();

    std::string space;
    for (int i = 0; i < len; ++i)
    {
        space += EMPTY_SPACE;
    }

    std::vector<std::string> fTemplate = _getTemplate();

    for (int j = 0; j < _getTemplateSize(); ++j)
    {
        _generateRow(prev, len, j, space);
    }
}

/**
 * Generates a new row (old times templateSize)
 * @param prev fractal for last dim
 * @param len last dim fractal matrix rank
 * @param row which row to generate
 * @param space string of spaces to add
 */
void Fractal::_generateRow(Fractal *prev, int len, int row, std::string &space)
{
    std::vector<std::string> fTemplate = _getTemplate();
    std::string str;
    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < _getTemplateSize(); ++j)
        {
            if (fTemplate[row][j] == BASE_CHAR)
            {
                str += prev->fractalLines.at(i);
            }
            else
            {
                str += space;
            }
        }
        fractalLines.push_back(str);
        str = "";
    }
}

// ********************** SierpinskiCarpet ********************** //

SierpinskiCarpet::SierpinskiCarpet(int dim)
    : Fractal(dim)
{}

int SierpinskiCarpet::_getTemplateSize() const
{
    return 3;
}

std::vector<std::string> SierpinskiCarpet::_getTemplate() const
{
    return std::vector<std::string>{
        "###",
        "# #",
        "###"
    };
}

Fractal *SierpinskiCarpet::PrevDim()
{
    return new SierpinskiCarpet(dim - 1);
}

// ********************** SierpinskiTriangle ********************** //

SierpinskiTriangle::SierpinskiTriangle(int dim)
    : Fractal(dim)
{}

int SierpinskiTriangle::_getTemplateSize() const
{
    return 2;
}

std::vector<std::string> SierpinskiTriangle::_getTemplate() const
{
    return std::vector<std::string>{
        "##",
        "# ",
    };
}

Fractal *SierpinskiTriangle::PrevDim()
{
    return new SierpinskiTriangle(dim - 1);
}

// ********************** Vicsek ********************** //
Vicsek::Vicsek(int dim)
    : Fractal(dim)
{}

int Vicsek::_getTemplateSize() const
{
    return 3;
}

std::vector<std::string> Vicsek::_getTemplate() const
{
    return std::vector<std::string>{
        "# #",
        " # ",
        "# #",
    };
}

Fractal *Vicsek::PrevDim()
{
    return new Vicsek(dim - 1);
}