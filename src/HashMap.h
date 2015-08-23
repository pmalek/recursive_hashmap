#ifndef HASHMAP_H
#define HASHMAP_H

#include <boost/multiprecision/cpp_int.hpp>
#include "HashNode.h"

const unsigned long INIT_TABLE_SIZE = 1024;

// Default hash function class
template<typename K>
class KeyHash
{
public:
    unsigned long operator()(const K &key) const
    {
        return static_cast<unsigned long>(key) % INIT_TABLE_SIZE;
    }
};

// cpp_int specialization using `.convert_to<>()` template
template<>
class KeyHash<boost::multiprecision::cpp_int>
{
public:
    unsigned long operator()(const boost::multiprecision::cpp_int &key) const
    {
        return key.convert_to < unsigned long int > () % INIT_TABLE_SIZE;
    }
};

// Hash map class template
template<typename K, typename V, typename F = KeyHash<K> >
class HashMap
{
public:
    HashMap() : number_of_elements(0), table_size(INIT_TABLE_SIZE)
    {
        // construct zero initialized hash table of size
        table = new HashNode<K, V> *[table_size]();
    }

    ~HashMap()
    {
        // destroy all buckets one by one
        for (unsigned long i = 0; i < table_size; ++i)
        {
            HashNode<K, V> *entry = table[i];
            while (entry != nullptr)
            {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = nullptr;
        }
        // destroy the hash table
        delete[] table;
    }

    bool get(const K &key, V &value)
    {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr)
        {
            if (entry->getKey() == key)
            {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    void put(const K &key, const V &value)
    {
        if (number_of_elements > table_size)
        {
            // may be better ?
            HashNode<K, V> **newTable = new HashNode<K, V> *[table_size * 2]();
            std::copy(table, table + table_size, newTable);
            delete[] table;
            table = newTable;
            table_size *= 2;
        }

        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr && entry->getKey() != key)
        {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr)
        {
            entry = new HashNode<K, V>(key, value);
            ++number_of_elements;
            if (prev == nullptr)
            {
                // insert as first bucket
                table[hashValue] = entry;
            } else
            {
                prev->setNext(entry);
            }
        } else
        {
            // update the value
            entry->setValue(value);
        }
    }

    void remove(const K &key)
    {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr && entry->getKey() != key)
        {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr)
        {
            // key not found
            return;
        }
        else
        {
            if (prev == nullptr)
            {
                // remove first bucket of the list
                table[hashValue] = entry->getNext();
            } else
            {
                prev->setNext(entry->getNext());
            }
            --number_of_elements;
            delete entry;
        }
    }

private:
    HashNode<K, V> **table;
    F hashFunc;
    unsigned long number_of_elements;
    unsigned long table_size;
};

#endif //HASHMAP_H
