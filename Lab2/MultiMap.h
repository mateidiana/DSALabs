#pragma once
#include<vector>
#include<utility>
#include <vector>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

//20. ADT MultiMap reprasentiert als DLL von eindeutigen Schlusseln. Jedem Schlussel entspricht ein DLL von Werten.
//20. ADT MultiMap represented as a DLL of unique keys. Each key corresponds a DLL of values.

struct values{
    TValue value;
    values *next;
    values *prev;
};
struct keys{
    TKey key;
    keys *next;
    keys *prev;
    values *headvalue;

};

class MultiMap
{
    friend class MultiMapIterator;

private:
    keys *head;
    keys *tail;
    int nrelems;

    void removeKey(TKey k);

    bool removeValue(TKey k, TValue v);

    void addNewKey(TKey k, TValue v);

    void addNewValue(TKey k, TValue v);

    void deleteValues(keys *node);

public:
    keys* searchNode(TKey k) const;

    void print();

    vector<pair<TKey,int>> Occurences() const;

    //constructor
    MultiMap();

    //adds a key value pair to the multimap
    void add(TKey c, TValue v);

    //removes a key value pair from the multimap
    //returns true if the pair was removed (if it was in the multimap) and false otherwise
    bool remove(TKey c, TValue v);

    //returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
    vector<TValue> search(TKey c) const;

    //returns the number of pairs from the multimap
    int size() const;

    //checks whether the multimap is empty
    bool isEmpty() const;

    //returns an iterator for the multimap
    MultiMapIterator iterator() const;

    //descturctor
    ~MultiMap();


};


