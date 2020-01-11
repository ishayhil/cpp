//
// Created by Ishay Hil on 11/01/2020.
//

#ifndef HASHMA_HPP
#define HASHMA_HPP

#include <list>
#include <string>

using std::list;
using std::pair;

template<typename KeyT, typename ValueT>
class HashMap
{
private:
    typedef pair<KeyT, ValueT> DictPair;
    int _size;
    int _capacity;
    const double _LOWER_LOAD_FACTOR = 1.0 / 4;
    const double _UPPER_LOAD_FACTOR = 3.0 / 4;
//    struct Node
//    {
//        ValueT val;
//        Node *next;
//        Node(ValueT val = ValueT(), Node *next = nullptr)
//            : val(val), next(next)
//        {}
//    };
    list<DictPair> map[16];
    list<DictPair> &_bucket(KeyT key)
    {
        return map[bucketIndex(key)];
    }

public:
    HashMap()
        : _size(0), _capacity(16)
    {}

    int bucketIndex(KeyT key) const
    {
        int hash = std::hash<KeyT>{}(key);
        return hash & (_capacity - 1);
    }

    int size() const
    {
        return _size;
    }

    int capacity() const
    {
        return _capacity;
    }

    bool empty() const
    {
        return _capacity == 0;
    }

    bool insert(KeyT key, ValueT val) // todo why would not it work?
    {

        list<DictPair> &bucket = _bucket(key);
        for (auto tuple: bucket)
        {
            if (tuple.second == val)
            {
                return false;
            }
        }
        bucket.push_back(pair<KeyT, ValueT>(key, val));
        _size++;
        return true;
//        while (head->next != nullptr)
//        {
//            head = head->next;
//        }
//        head->next = val;
//        return true;
    }

    bool containsKey(KeyT key)
    {
        return _bucket(key).size() > 0;
    }

    int bucketSize(KeyT key)
    {
        return _bucket(key).size();
    }

    double getLoadFactor()
    {
        return _size * 1.0 / _capacity;
    }

};
#endif //HASHMA_HPP
