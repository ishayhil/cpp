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


int main() {
//    LinkedList<int, int> list;
//
//    for (int i = 1; i < 11; i++) {
//        list.add(i, 2 * i);
//    }
//
//    auto temp = list.head;
//    while (temp != nullptr) {
////        cout << temp->tuple.first << " " << temp->tuple.second << endl;
//        temp = temp->next;
//    }
//
//    auto list2 = list;
//
//    temp = list2.head;
//    while (temp != nullptr) {
////        cout << temp->tuple.first << " " << temp->tuple.second << endl;
//        temp = temp->next;
//    }
//
//    list.remove(1);
//    assert(list2.exists(1) == 1);
//    assert(list.exists(1) == 0);
//    list = list2;
//    assert(list.exists(1) == 1);
//    list2.remove(1);
//    assert(list.exists(1) == 1);
//    assert(list2.exists(1) == 0);


    HashMap<int, int> map1;
    HashMap<int, int> map2;

    for (int i = 0; i < 10; ++i) {
        map1.insert(i, 2 * i);
    }

//    auto begin = map1.begin();
//    for (; begin != map1.end(); ++begin) {
//        cout << begin->first << " " << begin->second << endl;
//    }

    for (auto &t: map1) {
        cout << t.first << " " << t.second << endl;
    }


    return 1;

}