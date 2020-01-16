//
// Created by Ishay Hil on 11/01/2020.
//

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <list>
#include <string>
#include <vector>
#include <csignal>
#include <iostream>
/**
 * key not found msg
 */
#define KEY_NOT_FOUND "Key not found!"

/**
 * invalid vector size for hashmap 2 vectors constructor msg
 */
#define INVALID_VECTORS_SIZE "key vector size != val vector size!"

using std::list;
using std::pair;
using std::vector;

/**
 * HashMap class implements a generic Hash Map data structure. lower load factor = 1/4, upper load factor = 3/4.
 * @tparam KeyT type of the keys
 * @tparam ValueT type of the values
 */
template<typename KeyT, typename ValueT>
class HashMap
{
private:
    /**
     * declaring the DictPair type
     */
    typedef pair<KeyT, ValueT> DictPair;

    /**
     * amount of elements currently in hash map
     */
    int _size;

    /**
     * amount of buckets in the hash map
     */
    int _capacity;

    /**
     * lower load factor
     */
    const double _LOWER_LOAD_FACTOR = 1.0 / 4;

    /**
     * upper load factor
     */
    const double _UPPER_LOAD_FACTOR = 3.0 / 4;

    /**
     * bucket amount increase factor
     */
    const double _INCREASE_FACTOR = 2;

    /**
     * bucket amount decrease factor
     */
    const double _DECREASE_FACTOR = 1.0 / 2;

    /**
     * initial bucket amount
     */
    static const int _BASE_CAPACITY = 16;

    /**
     * the buckets container. Array of linked list.
     */
    list<DictPair> *_map;

    /**
     * a copy of _map field
     */
    list<DictPair> *_mapCopy;

    /**
     * @param key
     * @return the bucket the current key will be in.
     */
    list<DictPair> *_bucket(const KeyT key)
    {
        return &(_map[_bucketIndex(key)]);
    }

    /**
     * @param key
     * @return the bucket the current key will be in.
     */
    list<DictPair> *_bucket(const KeyT key) const
    {
        return &(_map[_bucketIndex(key)]);
    }

    /**
     *
     * @param key
     * @return a pointer to the DictPair of the given key. nullptr if key not exist.
     */
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

    /**
     *
     * @param key
     * @return a pointer to the DictPair of the given key. nullptr if key not exist.
     */
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

    /**
     * generates a new map and copies (rehashing) all elements to that map after increasing/decreasing map size.
     * @param factor to increase/decrease the map by
     */
    void _rehash(const double factor)
    {
        list<DictPair> *old = new list<DictPair>[_capacity];
        int old_capacity = _capacity;
        for (int i = 0; i < _capacity; ++i)
        {
            auto &bucket = _map[i];
            old[i] = bucket; // copy by reference
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

    /**
     * copies the map of a given HashMap to a new map. Allocates new memory!
     * @param other HashMap
     * @return a pointer to the map copy
     */
    list<DictPair> *_copyMap(const HashMap &other) const
    { // allocates heap memory!
        auto newMap = new list<DictPair>[other.capacity()];
        for (int i = 0; i < other.capacity(); i++)
        {
            for (auto &tuple: other._map[i])
            {
                newMap[i].push_back(DictPair(tuple.first, tuple.second));
            }
        }
        return newMap;
    }

    /**
     * a functor to send to the delete_if method of std::list.
     */
    struct KeyEquals
    {
        /**
         * the key to delete
         */
        KeyT key;
        /**
         * KeyEquals constructor
         * @param key
         */
        explicit KeyEquals(KeyT key)
            : key(key)
        {}
        /**
         *
         * @param tuple from bucket
         * @return true if the key's tuple = this key. false otherwise.
         */
        bool operator()(const DictPair &tuple)
        {
            return tuple.first == key;
        }
    };

    int _bucketIndex(const KeyT key) const noexcept
    {
        int hash = std::hash<KeyT>{}(key);
        return hash & (_capacity - 1);
    }

public:
    /**
     * Declaring the Iterator class of HashMap.
     */
    class Iterator;

    /**
     * HashMap default constructor. Inits a new HashMap with _BASE_CAPACITY buckets. Allocates the copy map.
     */
    HashMap()
        : _size(0), _capacity(_BASE_CAPACITY)
    {
        _map = new list<DictPair>[_capacity];
        _mapCopy = new list<DictPair>[_capacity];
    }

    /**
     * Copy constructor
     * @param other HashMap
     */
    HashMap(const HashMap &other)
    {
        _map = _copyMap(other);
        _mapCopy = _copyMap(other);
        _capacity = other.capacity();
        _size = other.size();
    }

    /**
     * move constructor
     * @param other HashMap
     */
    HashMap(const HashMap &&other) noexcept
    {
        _map = _copyMap(other);
        _mapCopy = _copyMap(other);
        _capacity = other.capacity();
        _size = other.size();
    }

    /**
     * inits an HashMap from key vector and value vector. Must be in same size.
     * @throws std::out_of_range if keyV and valV aren't of same size.
     * @param keyV key vector
     * @param valV value vector
     */
    HashMap(const vector<KeyT> keyV, const vector<ValueT> valV)
        : HashMap()
    {
        if (keyV.size() != valV.size())
        {
            throw std::out_of_range(INVALID_VECTORS_SIZE);
        }
        for (size_t i = 0; i < keyV.size(); ++i)
        {
            (*this)[keyV[i]] = valV[i]; // will override if exists and add a new one if not.
        }
    }

    /**
     * deconstructor. deallocates the map and map copy heap memory.
     */
    ~HashMap()
    {
        delete[] _map;
        delete[] _mapCopy;
        _map = nullptr;
        _mapCopy = nullptr;
    }

    /**
     * @param key
     * @return index of the bucket that holds the key.
     */
    int bucketIndex(const KeyT key) const
    {
        if (!containsKey(key))
        {
            throw std::out_of_range(KEY_NOT_FOUND);
        }
        return _bucketIndex(key);
    }

    /**
     * @return number of elements in HashMap
     */
    int size() const
    {
        return _size;
    }

    /**
     * @return number of buckets in HashMap
     */
    int capacity() const
    {
        return _capacity;
    }

    /**
     * @return true if HashMap has not elements, false otherwise.
     */
    bool empty() const
    {
        return _size == 0;
    }

    /**
     * inserts a new value to hash map. won't override existing key's val.
     * @param key of value
     * @param val the value
     * @return true if key wasn't in hash map, false otherwise.
     */
    bool insert(const KeyT key, const ValueT val)
    {
        if (containsKey(key))
        {
            return false;
        }
        list<DictPair> *bucket = _bucket(key);
        bucket->push_back(DictPair(key, val));
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
        auto bucket = _bucket(key);
        if (!containsKey(key))
        {
            throw std::out_of_range(KEY_NOT_FOUND);
        }
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
            throw std::out_of_range(KEY_NOT_FOUND);
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
            throw std::out_of_range(KEY_NOT_FOUND);
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
            insert(key, ValueT());
            return at(key);
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
            insert(key, ValueT());
            return at(key);
        }
        else
        {
            return tuple->second;
        }
    }

    HashMap &operator=(const HashMap other)
    {
        delete[] _map;
        _map = _copyMap(other);
        _capacity = other.capacity();
        _size = other.size();
        return *this;
    }

    bool operator==(const HashMap &other) const
    {
        if (_size != other.size())
        {
            return false;
        }
        for (int i = 0; i < _capacity; ++i)
        {
            for (auto &tuple: _map[i])
            {
                auto otherTuple = other._tuplePointer(tuple.first);
                if (otherTuple == nullptr || otherTuple->second != tuple.second)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const HashMap &other) const
    {
        return !((*this) == other);
    }

    bool erase(const KeyT key)
    {
        if (!containsKey(key))
        {
            return false;
        }
        list<DictPair> *bucket = _bucket(key);
        bucket->remove_if(KeyEquals(key));
        _size--;
        if (getLoadFactor() < _LOWER_LOAD_FACTOR && _capacity >= 2) // no need to rehash if capacity is 1
        {
            _rehash(_DECREASE_FACTOR);
        }
        return true;
    }

    void clear()
    {
        delete[] _map;
        _map = new list<DictPair>[_capacity];
        _size = 0;
    }

    Iterator cbegin()
    {
        delete[] _mapCopy;
        int ind = 0;
        _mapCopy = _copyMap(*this);
        while (_map[ind].size() == 0 && ind < _capacity - 1) // find first non empty bucket
        {
            ind++;
        }
        return Iterator(_mapCopy, _capacity, ind);
    }

    Iterator cend()
    {
        auto itr = Iterator(_mapCopy, _capacity, _capacity - 1);
        for (size_t i = 0; i < _mapCopy[_capacity - 1].size(); ++i)
        {
            itr.itr++;
        }
        return itr;
    }


public:
    class Iterator
    {
    public:
        list<DictPair> *map;
        int &capacity;
        int ind;
        list<DictPair> *bucket;
        typename list<DictPair>::iterator itr;
        explicit Iterator(list<DictPair> *map, int &capacity, int ind)
            : map(map), capacity(capacity), ind(ind), bucket(&(map[ind])), itr(bucket->begin())
        {}

        const DictPair &operator*() const
        {
            return *itr;
        }

        const DictPair *operator->() const
        {
            return &(*itr);
        }

        const Iterator &operator++()
        {
            if (itr == bucket->end() || ++itr == bucket->end()) // if deleted, can reach end before ++
            {
                _handleIncrease();
            }
            return *this;
        }

        const Iterator &operator++(int)
        {
            auto old = this;
            itr++;
            if (itr == bucket->end() || ++itr == bucket->end()) // if deleted, can reach end before ++
            {
                _handleIncrease();
            }
            return *old;
        }

        bool operator!=(const Iterator &other) const
        {
            return itr != other.itr;
        }

    private:
        void _handleIncrease()
        {
            if (ind != capacity - 1)
            {
                ind++; // finds next bucket with elements. if reach end, then that is the hashmap.end().
                while (map[ind].size() == 0 && ind < capacity - 1)
                {
                    ind++;
                }
                bucket = &(map[ind]);
                itr = bucket->begin();
            }
        }
    };
};
#endif //HASHMAP_HPP
