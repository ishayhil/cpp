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
 * a generic Linked List.
 * @tparam KeyT key type
 * @tparam ValueT value type
 */
template<typename KeyT, typename ValueT>
struct LinkedList {
    typedef pair<KeyT, ValueT> DictPair;

    struct Node {
        Node *next;
        DictPair tuple;

        Node(KeyT key, ValueT val, Node *next = nullptr) : next(next), tuple(pair<KeyT, ValueT>(key, val)) {}
    };


    int size;
    Node *head;
    Node *tail;

    LinkedList() : size(0), head(nullptr), tail(nullptr) {}

    LinkedList(LinkedList &other) : LinkedList() {
        if (other.head == nullptr) {
            return;
        }

        Node *temp = other.head;
        while (temp != nullptr) {
            add(temp->tuple.first, temp->tuple.second);
            temp = temp->next;
        }
    }

    ~LinkedList() {
        deleteAll();
    }

    void deleteAll() {
        if (head == nullptr) {
            return;
        }

        Node *prev;
        Node *curr = head;
        while (curr != nullptr) {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    LinkedList &operator=(const LinkedList &other) {
        if (this == &other) {
            return *this;
        }
        deleteAll();
        size = other.size;
        if (other.size == 0) {
            return *this;
        }
        Node *temp = other.head;
        while (temp != nullptr) {
            add(temp->tuple.first, temp->tuple.second);
            temp = temp->next;
        }
        return *this;
    }

    Node *add(KeyT key, ValueT val) {
        if (head == nullptr) {
            head = new Node(key, val);
            tail = head;
            size = 1;
            return nullptr;
        }
        Node *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        Node *newNode = new Node(key, val);
        temp->next = newNode;
        tail = newNode;
        size++;
        return newNode;
    }

    void remove(KeyT key) {
        Node *curr = head;
        Node *prev = head;
        if (size == 0) {
            return;
        } else if (head->tuple.first == key) {
            head = head->next;
            delete curr;
            size--;
            if (size == 0) {
                tail = nullptr;
            }
            return;
        }
        while (curr != nullptr) {
            if (curr->tuple.first == key) {
                prev->next = curr->next;
                if (tail->tuple.first == key) {
                    tail = prev;
                }
                delete curr;
                size--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    bool exists(KeyT key) {
        if (size == 0) {
            return false;
        }
        Node *temp = head;
        while (temp != nullptr) {
            if (temp->tuple.first == key) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
};

/**
 * HashMap class implements a generic Hash Map data structure. lower load factor = 1/4, upper load factor = 3/4.
 * @tparam KeyT type of the keys
 * @tparam ValueT type of the values
 */
template<typename KeyT, typename ValueT>
class HashMap {
private:
    /**
     * declaring the DictPair type
     */
    typedef pair<KeyT, ValueT> DictPair;

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
   * amount of buckets in the hash map
   */
    int _capacity;

    /**
    * amount of elements currently in hash map
    */
    int _size;


    /**
     * the buckets container. Array of linked list.
     */
    LinkedList<KeyT, ValueT> *_map;

    /**
     * @param key
     * @return the bucket the current key will be in.
     */
    LinkedList<KeyT, ValueT> *_bucket(const KeyT key) {
        return &(_map[_bucketIndex(key)]);
    }

    /**
     * @param key
     * @return the bucket the current key will be in.
     */
    LinkedList<KeyT, ValueT> *_bucket(const KeyT key) const {
        return &(_map[_bucketIndex(key)]);
    }

    /**
     *
     * @param key
     * @return a pointer to the DictPair of the given key. nullptr if key not exist.
     */
    DictPair *_tuplePointer(const KeyT key) {
        LinkedList<KeyT, ValueT> *bucket = _bucket(key);

        auto curr = bucket->head;
        while (curr != nullptr) {
            if (curr->tuple.first == key) {
                return &(curr->tuple);
            }
            curr = curr->next;
        }
        return nullptr;
    }

    /**
     *
     * @param key
     * @return a pointer to the DictPair of the given key. nullptr if key not exist.
     */
    DictPair *_tuplePointer(const KeyT key) const {
        LinkedList<KeyT, ValueT> *bucket = _bucket(key);

        auto curr = bucket->head;
        while (curr != nullptr) {
            if (curr->tuple.first == key) {
                return &(curr->tuple);
            }
            curr = curr->next;
        }
        return nullptr;
    }

    /**
     * generates a new map and copies (rehashing) all elements to that map after increasing/decreasing map size.
     * @param factor to increase/decrease the map by
     */
    void _rehash(const double factor) {
        auto *old = new LinkedList<KeyT, ValueT>[_capacity];
        int old_capacity = _capacity;
        for (int i = 0; i < _capacity; ++i) {
            auto &bucket = _map[i];
            old[i] = bucket; // copy by reference
        }
        delete[] _map;
        _capacity *= factor;
        _size = 0;
        _map = new LinkedList<KeyT, ValueT>[_capacity];
        for (int i = 0; i < old_capacity; i++) {
            auto curr = old[i].head;
            while (curr != nullptr) {
                insert(curr->tuple.first, curr->tuple.second);
                curr = curr->next;
            }
        }
        delete[] old;
    }

    /**
     * copies the map of a given HashMap to a new map. Allocates new memory!
     * @param other HashMap
     * @return a pointer to the map copy
     */
    static LinkedList<KeyT, ValueT> *_copyMap(const HashMap &other) { // allocates heap memory!
        auto newMap = new LinkedList<KeyT, ValueT>[other.capacity()];
        for (int i = 0; i < other.capacity(); i++) {
            newMap[i] = other._map[i];
        }
        return newMap;
    }

    /**
     * a functor to send to the delete_if method of std::list.
     */
    struct KeyEquals {
        /**
         * the key to delete
         */
        KeyT key;

        /**
         * KeyEquals constructor
         * @param key
         */
        explicit KeyEquals(KeyT key)
                : key(key) {}

        /**
         *
         * @param tuple from bucket
         * @return true if the key's tuple = this key. false otherwise.
         */
        bool operator()(const DictPair &tuple) {
            return tuple.first == key;
        }
    };

    int _bucketIndex(const KeyT key) const noexcept {
        int hash = std::hash<KeyT>{}(key);
        return hash & (_capacity - 1);
    }

public:
    /**
     * Declaring the Iterator class of HashMap.
     */
    class iterator;

    /**
     * HashMap default constructor. Inits a new HashMap with _BASE_CAPACITY buckets. Allocates the copy map.
     */
    HashMap()
            :
            _capacity(_BASE_CAPACITY), _size(0) {
        _map = new LinkedList<KeyT, ValueT>[_capacity];
    }

    /**
     * Copy constructor
     * @param other HashMap
     */
    HashMap(const HashMap &other)
            : _capacity(other.capacity()),
              _size(other._size), _map(_copyMap(other)) {}

    /**
     * move constructor
     * @param other HashMap
     */
    HashMap(const HashMap &&other) noexcept
            : _capacity(other.capacity()),
              _size(other._size), _map(_copyMap(other)) {}

    /**
     * inits an HashMap from key vector and value vector. Must be in same size.
     * @throws std::out_of_range if keyV and valV aren't of same size.
     * @param keyV key vector
     * @param valV value vector
     */
    HashMap(const vector<KeyT> keyV, const vector<ValueT> valV) : HashMap() {
        if (keyV.size() != valV.size()) {
            throw std::out_of_range(INVALID_VECTORS_SIZE);
        }
        for (size_t i = 0; i < keyV.size(); ++i) {
            (*this)[keyV[i]] = valV[i]; // will override if exists and add a new one if not.
        }
    }

    /**
     * deconstructor. deallocates the map and map copy heap memory.
     */
    ~HashMap() {
        delete[] _map;
        _map = nullptr;
    }

    /**
     * @param key
     * @return index of the bucket that holds the key.
     */
    int bucketIndex(const KeyT key) const {
        if (!containsKey(key)) {
            throw std::out_of_range(KEY_NOT_FOUND);
        }
        return _bucketIndex(key);
    }

    /**
     * @return number of elements in HashMap
     */
    int size() const {
        return _size;
    }

    /**
     * @return number of buckets in HashMap
     */
    int capacity() const {
        return _capacity;
    }

    /**
     * @return true if HashMap has not elements, false otherwise.
     */
    bool empty() const {
        return _size == 0;
    }

    /**
     * inserts a new value to hash map. won't override existing key's val.
     * @param key of value
     * @param val the value
     * @return true if key wasn't in hash map, false otherwise.
     */
    bool insert(const KeyT key, const ValueT val) {
        if (containsKey(key)) {
            return false;
        }
        auto bucket = _bucket(key);
        bucket->add(key, val);
        _size++;
        if (getLoadFactor() > _UPPER_LOAD_FACTOR) {
            _rehash(_INCREASE_FACTOR);
        }
        return true;
    }

    bool containsKey(const KeyT key) const {
        return _tuplePointer(key) != nullptr;
    }

    int bucketSize(const KeyT key) const {
        auto bucket = _bucket(key);
        if (!containsKey(key)) {
            throw std::out_of_range(KEY_NOT_FOUND);
        }
        return _bucket(key)->size;
    }

    double getLoadFactor() const {
        return _size * 1.0 / _capacity;
    }

    ValueT &at(const KeyT key) {
        DictPair *tuple = _tuplePointer(key);
        if (tuple == nullptr) {
            throw std::out_of_range(KEY_NOT_FOUND);
        } else {
            return tuple->second;
        }
    }

    ValueT at(const KeyT key) const {
        DictPair *tuple = _tuplePointer(key);
        if (tuple == nullptr) {
            throw std::out_of_range(KEY_NOT_FOUND);
        } else {
            return tuple->second;
        }
    }

    ValueT &operator[](const KeyT key) noexcept {
        DictPair *tuple = _tuplePointer(key);
        if (tuple == nullptr) {
            insert(key, ValueT());
            return at(key);
        } else {
            return tuple->second;
        }
    }

    ValueT operator[](const KeyT key) const noexcept {
        DictPair *tuple = _tuplePointer(key);
        if (tuple == nullptr) {
            return at(key);
        } else {
            return tuple->second;
        }
    }

    HashMap &operator=(const HashMap other) {
        delete[] _map;
        _map = _copyMap(other);
        _capacity = other.capacity();
        _size = other.size();
        return *this;
    }

    bool operator==(const HashMap &other) const {
        if (_size != other.size()) {
            return false;
        }
        for (int i = 0; i < _capacity; ++i) {
            auto curr = _map[i].head;
            while (curr != nullptr) {
                if (!other.containsKey(curr->tuple.first)) {
                    return false;
                }
                curr = curr->next;
            }
        }
        return true;
    }

    bool operator!=(const HashMap &other) const {
        return !((*this) == other);
    }

    bool erase(const KeyT key) {
        if (!containsKey(key)) {
            return false;
        }
        LinkedList<KeyT, ValueT> *bucket = _bucket(key);
        bucket->remove(key);
        _size--;
        if (getLoadFactor() < _LOWER_LOAD_FACTOR && _capacity >= 2) // no need to rehash if capacity is 1
        {
            _rehash(_DECREASE_FACTOR);
        }
        return true;
    }

    void clear() {
        for (int i = 0; i < _capacity; ++i) {
            _map[i].deleteAll();
        }
        _size = 0;
    }

    iterator cbegin() const {
        return begin();
    }

    iterator begin() const {
        int i = 0;
        while (_map[i].size == 0 && i < _capacity - 1) {
            i++;
        }
        return iterator(_map, _capacity, i);
    }


    iterator cend() const {
        return end();
    }

    iterator end() const {
        auto iter = iterator(_map, _capacity, _capacity - 1);
        for (int i = 0; i < _map[_capacity - 1].size - 1; i++) {
            iter++;
        }
        return iter;
    }


public:
    class iterator {
    public:
        typedef int difference_type;
        typedef iterator self_type;
        typedef DictPair value_type;
        typedef DictPair &reference;
        typedef DictPair *pointer;
        typedef std::forward_iterator_tag iterator_category;

        typename LinkedList<KeyT, ValueT>::Node *currNode;
        LinkedList<KeyT, ValueT> const *map;
        int ind, capacity;


        explicit iterator(LinkedList<KeyT, ValueT> *map, int capacity, int ind) {
            this->map = map;
            this->capacity = capacity;
            this->ind = ind;
            this->currNode = map[ind].head;
        }

        const value_type &operator*() const {
            return currNode->tuple;
        }

        const pointer operator->() const {
            return &(currNode->tuple);
        }

        difference_type operator-(iterator &other) {
            int cnt = 0;
            iterator tmp = this;
            while (tmp != other) {
                tmp++;
                cnt++;
            }
            return cnt;
        }

        const self_type &operator++() {
            if (currNode->next == nullptr) {
                _handleIncrease();
            } else {
                currNode = currNode->next;
            }
            return *this;
        }

        const self_type operator++(int) {
            auto old = *this;
            if (currNode->next == nullptr) {
                _handleIncrease();
            } else {
                currNode = currNode->next;
            }
            return old;
        }

        bool operator!=(const iterator &other) const {
            return !(*this == other);
        }

        bool operator==(const iterator &other) const {
            if (currNode == nullptr && other.currNode == nullptr) {
                return other.ind == ind;
            }
            if (currNode == nullptr || other.currNode == nullptr) {
                return false;
            }
            return other.currNode->tuple == currNode->tuple && other.ind == ind;
        }

    private:
        void _handleIncrease() {
            if (ind != capacity - 1) {
                ind++; // finds next bucket with elements. if reach end, then that is the hashmap.end().
                while (map[ind].size == 0 && ind < capacity - 1) {
                    ind++;
                }
                currNode = map[ind].head;
            }
        }
    };
};


#endif //HASHMAP_HPP
