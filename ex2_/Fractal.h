//
// Created by Ishay Hil on 30/12/2019.
//

#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>
#include <string>
#include <iostream>
#define BASE_CHAR "#";

class Fractal
{
public:
    explicit Fractal(int dim);
    void print();

protected:
    int dim;
    std::vector<std::string> fractalLines;

    virtual bool _canPutSymbol(int row, int col) const = 0;
    virtual void _populateFractalLines() = 0;
    virtual int _getTemplateSize() const = 0;
};

class Sierpinski: public Fractal
{
public:
    explicit Sierpinski(int dim);

protected:
    bool _canPutSymbol(int row, int col) const override;
    void _populateFractalLines() override;
};

class SierpinskiTriangle: public Sierpinski
{
public:
    explicit SierpinskiTriangle(int dim);

protected:
    int _getTemplateSize() const override;
};

class SierpinskiCarpet: public Sierpinski
{
public:
    explicit SierpinskiCarpet(int dim);

protected:
    int _getTemplateSize() const override;
};


#endif //FRACTAL_H
