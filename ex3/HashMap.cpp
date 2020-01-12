//
// Created by Ishay Hil on 11/01/2020.
//

#include "HashMap.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::endl;


int main()
{
    HashMap<string, double> h;
    for (int i = 0; i < 16; ++i)
    {
        h.insert("ishay_" + std::to_string(i), i);
    }

    for (int i = 0; i < 16; ++i)
    {
        h.erase("ishay_" + std::to_string(i));
//        cout << h["ishay_" + std::to_string(i)] << endl;
    }

    cout << h.size() << endl;
    cout << h.capacity() << endl;
//    cout << h.at("ishay_0") << endl;

//    cout << h.size() << endl;
//    cout << h.containsKey("ishay") << endl;
//    cout << h.insert("ishay", 24) << endl;
//    cout << h.size() << endl;
//    cout << h.bucketSize("ishay") << endl;
//    cout << h.bucketSize("mor") << endl;
//    cout << h.at("ishay") << endl;
//    cout << h["mor"] << endl;


//    HashMap<string, string> h1;
//    cout << h1.size() << endl;
//    cout << h1.containsKey("ishay") << endl;
//    cout << h1.insert("ishay", "24") << endl;
//    cout << h1.size() << endl;
//    cout << h1.bucketSize("ishay") << endl;
//    cout << h1.bucketSize("mor") << endl;
//    cout << h1.at("ishay") << endl;
//    h1.at("ishay") = "new";
//    cout << h1.at("ishay") << endl;
//    cout << h1["mor"] << endl;
//    std::cout << "hi";
    return 1;
}