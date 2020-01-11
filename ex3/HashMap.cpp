//
// Created by Ishay Hil on 11/01/2020.
//

#include "HashMap.hpp"
#include <iostream>

using std::cout;
using std::string;
using std::endl;


int main() {
    HashMap<string, int> h;
    cout << h.size() << endl;
    cout << h.containsKey("ishay") << endl;
    cout << h.insert("ishay", 24) << endl;
    cout << h.size() << endl;
    cout << h.bucketSize("ishay") << endl;
    cout << h.bucketSize("mor") << endl;
//    std::cout << "hi";
    return 1;
}