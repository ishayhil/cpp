//
// Created by Ishay Hil on 11/01/2020.
//

#include "HashMap.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::vector;
using std::endl;


int main()
{
//    list<double> a{1,2};
//    list<double>::Iterator b = a.begin();
//    cout << *b << endl;
//    b++;
//    cout << *b << endl;
//    b++;
//    cout << (b == a.end()) << endl;
//    exit(1);

    HashMap<string, double> h1;
    HashMap<string, double> h2;
//    vector<string> v1{"ishay", "mor", "shira"};
//    vector<double> v2{24.9, 25.3, 24.4};
//    HashMap<string, double> h2(v1, v2);
//    cout << h2["ishay"] << endl;
//    cout << h2["mor"] << endl;
//    cout << h2["shira"] << endl;
//    cout << h2.size() << endl;
//    cout << h2.erase("ishay") << endl;
//    cout << h2.size() << endl;
//    cout << h2.capacity() << endl;

    for (int i = 0; i < 2; ++i)
    {
        h1.insert("ishay_" + std::to_string(i), i);
    }

    cout << h1.size() << endl;

    for (auto &tup: h1)
    {
        h1.erase(tup.first);
    }

    cout << h1.size() << endl;

//    auto a = h1.begin();
//    cout << a->first << " " << a->second << endl;
//    ++a;
//    cout << a->first << a->second << endl;
//    ++a;
//    cout << a->first << a->second << endl;
//    ++a;
//    cout << a->first << a->second << endl;

//    h1.erase("ishay_0");
//    h1.insert("ishay_01", 0);
//    cout << (h1 == h2) << endl;

//    for (int i = 0; i < 16; ++i)
//    {
//        cout << h.erase("ishay_" + std::to_string(i)) << endl;
//        cout << h["ishay_" + std::to_string(i)] << endl;
//    }
//
//    cout << h.erase("a") << endl;
//
//    cout << h.size() << endl;
//    cout << h.capacity() << endl;
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