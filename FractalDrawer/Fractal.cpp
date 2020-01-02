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
    int len = pow(_getTemplateSize(), dim);
    for (int i = 0; i < len; ++i)
    {
        if (i != len - 1) {
            std::cout << fractalLines.at(i) << std::endl;
        } else {
            std::cout << fractalLines.at(i);
        }
    }
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
    delete prev;
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

// ********************** FractalFactory ********************** //
std::vector<Fractal *> FractalFactory::fractals;

void FractalFactory::parseCsv(std::string &path)
{
    if (!boost::filesystem::exists(path))
    {
        invalidInput();
    }
    std::ifstream ifstream(path);
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep{COMMA_STR};
    std::string currentLine;
    if (ifstream.peek() == std::ifstream::traits_type::eof())
    { // empty file
        ifstream.close();
        return;
    }
    while (getline(ifstream, currentLine))
    { // in line
        tokenizer tok{currentLine, sep};
        if (currentLine.empty() || !checkNotDupComma(currentLine)) {
            deleteFractals();
            ifstream.close();
            invalidInput();
        }
        std::vector<std::string> tokens;
        for (const auto &t: tok)
        {
            tokens.push_back(t);
        }
        generateFractals(tokens, ifstream);
    }
    ifstream.close();
}

void FractalFactory::invalidInput()
{
    std::cerr << INVALID_INPUT << std::endl;
    exit(EXIT_FAILURE);
}

void FractalFactory::generateFractals(std::vector<std::string> &fractalsVector, std::ifstream &ifstream)
{
    if (fractalsVector.size() != 2 || !isValidVector(fractalsVector)) // if csv structure is invalid
    {
        deleteFractals();
        ifstream.close();
        invalidInput();
    }
    int fractalNum = std::stoi(fractalsVector[0]);
    int dim = std::stoi(fractalsVector[1]);
    if (fractalNum < 1 || fractalNum > 3 || dim < 1 || dim > 6) // if values are invalid
    {
        deleteFractals();
        ifstream.close();
        invalidInput();
    }

    switch (fractalNum)
    {
    case 1: FractalFactory::fractals.push_back(new SierpinskiCarpet(dim));
        break;
    case 2: FractalFactory::fractals.push_back(new SierpinskiTriangle(dim));
        break;
    default: FractalFactory::fractals.push_back(new Vicsek(dim)); // case 3
    }
}

bool FractalFactory::isValidVector(std::vector<std::string> &v)
{
    for (std::string string: v) {
        if (string.empty()) {
            return false;
        }
        if (string[string.size() - 1] == '\r') {
            string.erase(string.size() - 1);
        }
        if (string.size() != 1 || !isdigit((unsigned char) string[0])) {
            return false;
        }
    }
    return true;
}

bool FractalFactory::checkNotDupComma(std::string &string) {
    if (string.size() == 1) {
        return true;
    }
    for (int i = 0; i < (int) string.size() - 1; ++i) {
        if (string[i] == COMMA && string[i + 1] == COMMA) {
            return false;
        }
    }
    return true;
}

void FractalFactory::deleteFractals()
{
    for (Fractal* fractal: FractalFactory::fractals) {
        delete fractal;
    }
}