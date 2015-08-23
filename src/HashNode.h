#ifndef HASHNODE_H
#define HASHNODE_H

// Hash node class template
template<typename K, typename V>
class HashNode
{
public:
    HashNode(const K &key, const V &value) :
            key(key), value(value), next(nullptr)
    { }

    K getKey() const
    {
        return key;
    }

    V getValue() const
    {
        return value;
    }

    void setValue(V value)
    {
        HashNode::value = value;
    }

    HashNode *getNext() const
    {
        return next;
    }

    void setNext(HashNode *next)
    {
        HashNode::next = next;
    }

private:
    K key;
    V value;
    // next bucket with the same key
    HashNode *next;
};

template<typename K, typename V>
bool operator==(const HashNode <K, V> &lhs, const HashNode <K, V> &rhs)
{
    return (lhs.getKey() == rhs.getKey()) && (lhs.getValue() == rhs.getValue());
};

template<typename K, typename V>
bool operator!=(const HashNode <K, V> &lhs, const HashNode <K, V> &rhs)
{
    return (lhs.getKey() != rhs.getKey()) || (lhs.getValue() != rhs.getValue());
};

#endif //HASHNODE_H
