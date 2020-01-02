#include <iostream>
#include "Fractal.h"
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int dim = 3;
    Fractal *s = new Vicsek(dim);
    s->populate();
//    std::vector<std::string> v;
//    s.print();
//    std::cout << s->fractalLines.size();
//    std::cout << s->fractalLines.at(1);
    s->print();
}