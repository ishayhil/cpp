//
// Created by Ishay Hil on 30/12/2019.
//

#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>
#include <string>
#include <iostream>
#include "boost/tokenizer.hpp"
//#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
//#undef BOOST_NO_CXX11_SCOPED_ENUMS

#define INVALID_INPUT "Invalid input"
#define INVALID_USAGE "Usage: FractalDrawer <file path>"

class Fractal
{
public:
    explicit Fractal(int dim);
    void print();
    void populate();
    std::vector<std::string> fractalLines;
    const static char BASE_CHAR = '#';
    const static char EMPTY_SPACE = ' ';

protected:
    int dim;

    virtual int _getTemplateSize() const = 0;
    virtual std::vector<std::string> _getTemplate() const = 0;
    virtual Fractal *PrevDim() = 0;
private:
    void _generateRow(Fractal *prev, int len, int row, std::string &space);
};

class SierpinskiTriangle: public Fractal
{
public:
    explicit SierpinskiTriangle(int dim);

protected:
    int _getTemplateSize() const override;
    std::vector<std::string> _getTemplate() const override;
    Fractal *PrevDim() override;
};

class SierpinskiCarpet: public Fractal
{
public:
    explicit SierpinskiCarpet(int dim);

protected:
    int _getTemplateSize() const override;
    std::vector<std::string> _getTemplate() const override;
    Fractal *PrevDim() override;
};

class Vicsek: public Fractal
{
public:
    explicit Vicsek(int dim);
protected:
    int _getTemplateSize() const override;
    std::vector<std::string> _getTemplate() const override;
    Fractal *PrevDim() override;
};

class FractalFactory
{
public:
    static std::vector<Fractal *> fractals;
    static void parseCsv(std::string &path);
private:
    static void invalidInput();

    static void generateFractals(std::vector<std::string> &fractalsVector);

    static bool isValidVector(std::vector<std::string> &v);
};

#endif //FRACTAL_H
