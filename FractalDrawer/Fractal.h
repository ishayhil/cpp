//
// Created by Ishay Hil on 30/12/2019.
//

#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>
#include <string>
#include <iostream>
#include "boost/tokenizer.hpp"
#include <boost/filesystem.hpp>

#define INVALID_INPUT "Invalid input"
#define INVALID_USAGE "Usage: FractalDrawer <file path>"
#define COMMA ','
#define COMMA_STR ","

/**
 * An abstract class that represent a fractal with it's dim. Can print the fractal.
 */
class Fractal
{
public:
    /**
     * The constructor. Accepts an integer (dim) between 1 and 6.
     * @param dim
     */
    explicit Fractal(int dim);

    /**
     * prints this fractal to stdout.
     */
    void print();

    /**
     * populates the fractalLines vector.
     */
    void populate();

    /**
     * The default deconstructor. virtual due to inheritance.
     */
    virtual ~Fractal() = default;

    /**
     * Vector that holds all the current fractal lines.
     */
    std::vector<std::string> fractalLines;

    /**
     * The base ascii char for the fractal.
     */
    const static char BASE_CHAR = '#';

    /**
     * the space char.
     */
    const static char EMPTY_SPACE = ' ';

protected:
    /**
     * the fractal's dim
     */
    int dim;

    /**
     * @return the template size of the fractal.
     */
    virtual int _getTemplateSize() const = 0;

    /**
     * @return the fractal's template.
     */
    virtual std::vector<std::string> _getTemplate() const = 0;

    /**
     * @return a pointer to a fractal of the current dim with dim-1.
     */
    virtual Fractal *_prevDim() = 0;
private:
    void _generateRow(Fractal *prev, int len, int row, std::string &space);
};

/**
 * Represents a Fractal of type Sierpinski Triangle. Extends public Fractal.
 */
class SierpinskiTriangle: public Fractal
{
public:
    /**
     * The constructor. Accepts an integer (dim) between 1 and 6.
     * @param dim
     */
    explicit SierpinskiTriangle(int dim);

private:
    /**
     * @return the template size of the fractal.
     */
    int _getTemplateSize() const override;

    /**
     * @return the fractal's template.
     */
    std::vector<std::string> _getTemplate() const override;

    /**
     * @return a pointer to a fractal of the current dim with dim-1.
     */
    Fractal *_prevDim() override;
};

/**
 * Represents a Fractal of type Sierpinski Carpet. Extends public Fractal.
*/
class SierpinskiCarpet: public Fractal
{
public:
    /**
     * The constructor. Accepts an integer (dim) between 1 and 6.
     * @param dim
     */
    explicit SierpinskiCarpet(int dim);

private:
    /**
     * @return the template size of the fractal.
     */
    int _getTemplateSize() const override;

    /**
     * @return the fractal's template.
     */
    std::vector<std::string> _getTemplate() const override;

    /**
     * @return a pointer to a fractal of the current dim with dim-1.
     */
    Fractal *_prevDim() override;
};

/**
 * Represents a Fractal of type Vicsek. Extends public Fractal.
*/
class Vicsek: public Fractal
{
public:
    /**
     * The constructor. Accepts an integer (dim) between 1 and 6.
     * @param dim
     */
    explicit Vicsek(int dim);
private:
    /**
     * @return the template size of the fractal.
     */
    int _getTemplateSize() const override;

    /**
     * @return the fractal's template.
     */
    std::vector<std::string> _getTemplate() const override;

    /**
     * @return a pointer to a fractal of the current dim with dim-1.
     */
    Fractal *_prevDim() override;
};

/**
 * A fractal factory - parses the given csv and generates objects of type Fractal.
 */
class FractalFactory
{
public:
    /**
     * the fractals generated by the factory
     */
    static std::vector<Fractal *> fractals;

    /**
     * parses the csv in the given path, ang generates the fractals.
     * @param path
     */
    static void parseCsv(std::string &path);

    /**
     * prints invalid csv input message and exists the program with exit failure.
     */
    static void invalidInput();

    /**
     * deletes (frees) the fractals in the vector
     */
    static void deleteFractals();
private:
    /**
     * allocates the fractals
     * @param fractalsVector vector of (fractal_type, dim)
     * @param ifstream csv stream
     */
    static void _generateFractals(std::vector<std::string> &fractalsVector, std::ifstream &ifstream);

    /**
     * checks if the vector is valid (size, no empty lines, decimal only, 1 char)
     * @param v the vector
     * @return true if vector is valid, false otherwise
     */
    static bool _isValidVector(std::vector<std::string> &v);

    /**
     * @param string to check
     * @return true if the string contains duplicated commas, false otherwise.
     */
    static bool _checkNotDupComma(std::string &string);
};

#endif //FRACTAL_H
