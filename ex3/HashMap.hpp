//
// Created by Ishay Hil on 11/01/2020.
//

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <list>
#include <string>
#include <csignal>
#include <iostream>

using std::list;
using std::pair;

template<typename KeyT, typename ValueT>
class HashMap
{
private:
    typedef pair<KeyT, ValueT> DictPair;
    int _size;
    int _capacity;
    ValueT _undefined_val = ValueT();
    const double _LOWER_LOAD_FACTOR = 1.0 / 4;
    const double _UPPER_LOAD_FACTOR = 3.0 / 4;
    const double _INCREASE_FACTOR = 2;
    const double _DECREASE_FACTOR = 1.0 / 2;
    static const int _BASE_CAPACITY = 16;

    list<DictPair> *_map;
    list<DictPair> *_bucket(const KeyT key)
    {
        return &(_map[bucketIndex(key)]);
    }

    list<DictPair> *_bucket(const KeyT key) const
    {
        return &(_map[bucketIndex(key)]);
    }

    DictPair *_tuplePointer(const KeyT key)
    {
        list<DictPair> *bucket = _bucket(key);

        for (auto &tuple: *bucket)
        {
            if (tuple.first == key)
            {
                return &tuple;
            }
        }
        return nullptr;
    }

    DictPair *_tuplePointer(const KeyT key) const
    {
        list<DictPair> *bucket = _bucket(key);

        for (auto &tuple: *bucket)
        {
            if (tuple.first == key)
            {
                return &tuple;
            }
        }
        return nullptr;
    }

    void _rehash(const double factor)
    {
        list<DictPair> *old = new list<DictPair>[_capacity];
        int old_capacity = _capacity;
        for (int i = 0; i < _capacity; ++i)
        {
            old[i] = _map[i];
        }
        delete[] _map;
        _capacity *= factor;
        _size = 0;
        _map = new list<DictPair>[_capacity];
        for (int i = 0; i < old_capacity; i++)
        {
            for (auto &tuple: old[i])
            {
                insert(tuple.first, tuple.second);
            }
        }
        delete[] old;
    }

    struct KeyEquals
    {
        KeyT key;
        explicit KeyEquals(KeyT key)
            : key(key)
        {}
        bool operator()(const DictPair &tuple)
        {
            return tuple.first == key;
        }
    };

public:
    HashMap()
        : _size(0), _capacity(_BASE_CAPACITY)
    {
        _map = new list<DictPair>[_capacity];
    }

    ~HashMap()
    {
        delete[] _map;
        _map = nullptr;
    }

    int bucketIndex(const KeyT key) const
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

    bool insert(const KeyT key, const ValueT val) // todo why would not it work?
    {
        if (containsKey(key))
        {
            return false;
        }
        list<DictPair> *bucket = _bucket(key);
        bucket->push_back(pair<KeyT, ValueT>(key, val));
        _size++;
        if (getLoadFactor() > _UPPER_LOAD_FACTOR)
        {
            _rehash(_INCREASE_FACTOR);
        }
        return true;
    }

    bool containsKey(const KeyT key) const
    {
        return _tuplePointer(key) != nullptr;
    }

    int bucketSize(const KeyT key) const
    {
        return _bucket(key)->size();
    }

    double getLoadFactor() const
    {
        return _size * 1.0 / _capacity;
    }

    ValueT &at(const KeyT key)
    {
        DictPair *tuple = _tuplePointer(key);
        if (tuple == nullptr)
        {
            throw std::out_of_range("key not found!");
        }
        else
        {
            return tuple->second;
        }
    }

    ValueT at(const KeyT key) const
    {
        DictPair *tuple = _tuplePointer(key);
        if (tuple == nullptr)
        {
            throw std::out_of_range("key not found!");
        }
        else
        {
            return tuple->second;
        }
    }

    ValueT &operator[](const KeyT key) noexcept
    {
        DictPair *tuple = _tuplePointer(key);
        if (tuple == nullptr)
        {
            return _undefined_val;
        }
        else
        {
            return tuple->second;
        }
    }

    ValueT operator[](const KeyT key) const noexcept
    {
        DictPair *tuple = _tuplePointer(key);
        if (tuple == nullptr)
        {
            return _undefined_val;
        }
        else
        {
            return tuple->second;
        }
    }

    bool erase(const KeyT key)
    {
        if (!containsKey(key))
        {
            return false;
        }
        KeyEquals keyEquals(key);
        list<DictPair> *bucket = _bucket(key);
        bucket->remove_if(keyEquals);
        _size--;
        if (getLoadFactor() < _LOWER_LOAD_FACTOR && _capacity >= 2)
        {
            _rehash(_DECREASE_FACTOR);
        }
        return true;
    }
};
#endif //HASHMAP_HPP
