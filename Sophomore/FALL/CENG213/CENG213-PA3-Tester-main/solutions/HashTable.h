#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"
#include "ItemNotFoundException.h"
/* Do not add new libraries or files */

#define BUCKET_SIZE 2

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class K, class T>
class HashTable {
    struct Entry {
        K Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[BUCKET_SIZE];
    };

    int _capacity; // INDICATES THE TOTAL CAPACITY OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // THE HASH TABLE

    // == DEFINE HELPER METHODS & VARIABLES BELOW ==


public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    // COPY THE WHOLE CONTENT OF RHS INCLUDING THE KEYS THAT WERE SET AS DELETED
    HashTable(const HashTable<K, T>& rhs);
    HashTable<K, T>& operator=(const HashTable<K, T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. IF THE LOAD FACTOR OF THE TABLE IS GREATER THAN 0.6,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(const K& key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, THROW ItemNotFoundException()
    void Delete(const K& key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THROW ItemNotFoundException()
    T& Get(const K& key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES
    void Resize(int newCapacity);

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const; // RETURN THE TOTAL CAPACITY OF THE TABLE
    int Size() const; // RETURN THE NUMBER OF ACTIVE ITEMS
    void getKeys(K* keys); // PUT THE ACTIVE KEYS TO THE GIVEN INPUT PARAMETER
};


template <class K, class T>
HashTable<K, T>::HashTable() {
    _capacity = 7;
    _size = 0;
    _table = new Bucket[_capacity];
}

template <class K, class T>
HashTable<K, T>::HashTable(const HashTable<K, T>& rhs) {
    this->_capacity = rhs._capacity;
    this->_table = new Bucket[_capacity];
    for (int i = 0; i<rhs._capacity ; ++i) {
        Bucket& bucket = rhs._table[i];
        if (bucket.entries[0].Active){
            this->_table[i].entries[0] = bucket.entries[0];
        }
        else if (bucket.entries[1].Active){
            this->_table[i].entries[1] = bucket.entries[1];
        }
    }
    this->_size = rhs._size;

}

template <class K, class T>
HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& rhs) {
    this->_capacity = rhs._capacity;
    delete[] this->_table;
    this->_table = new Bucket[_capacity];
    for (int i = 0; i<rhs._capacity ; ++i) {
        Bucket& bucket = rhs._table[i];
        for (int j = 0; j < BUCKET_SIZE; ++j){
            this->_table[i].entries[j] = bucket.entries[j];
        }
    }
    this->_size = rhs._size;

    return *this;
}

template <class K, class T>
HashTable<K, T>::~HashTable() {
    delete[] _table;
}

template <class K, class T>
void HashTable<K, T>::Insert(const K& key, const T& value) {
    int first_hash = Hash(key)%_capacity;
    int hash = first_hash;

    Entry ent2inst;
    ent2inst.Key = key;
    ent2inst.Value = value;
    ent2inst.Active = true;

    _size++;
    bool th = true;
    for (int i = 0; th; i++,hash = (first_hash + i*i)% _capacity) {
        Bucket& bucket = _table[hash];
        for (int j = 0; j < BUCKET_SIZE; ++j) {
            if (!bucket.entries[j].Active || bucket.entries[j].Deleted){
                bucket.entries[j] = ent2inst;
                th = false;
                break;
            }
            else if (bucket.entries[j].Key == key){
                bucket.entries[j].Value = value;
                if(!bucket.entries[j].Deleted) _size--;
                th = false;
                break;
            }
        }
    }

    double lf = (float)_size / (_capacity*2);

    if (lf >= 0.6){
        this->Resize(NextCapacity(_capacity));
    }

}

template <class K, class T>
void HashTable<K, T>::Delete(const K& key) {
    int hash = Hash(key)%_capacity;
    _size--;
    int firsthash = hash;
    for (int i = 0; true; i++,hash = (firsthash + (i)*(i))% _capacity) {
        Bucket& bucket = _table[hash];
        if (!bucket.entries[0].Active){
            break;
        }
        for (int j = 0; j < BUCKET_SIZE; ++j) {
            if (bucket.entries[j].Active && !bucket.entries[j].Deleted && bucket.entries[j].Key == key){
                bucket.entries[j].Deleted = true;
                return;
            }
        }

    }

    throw ItemNotFoundException();

}

template <class K, class T>
T& HashTable<K, T>::Get(const K& key) const {
    int hash = Hash(key)%_capacity;
    int firsthash = hash;

    for (int i = 0; i<_capacity; i++,hash = (firsthash + (i)*(i)) % _capacity) {
        Bucket& bucket = _table[hash];

        if (!bucket.entries[0].Active){
            break;
        }
        for (int j = 0; j < BUCKET_SIZE; ++j) {
            if (bucket.entries[j].Active && !bucket.entries[j].Deleted && bucket.entries[j].Key == key){
                return bucket.entries[j].Value;
            }
        }
    }

    throw ItemNotFoundException();

}


template <class K, class T>
void HashTable<K, T>::Resize(int newCapacity) {
    Bucket* backup;
    int old = _capacity;

    backup = new Bucket[newCapacity];

    for (int i = 0; i < old; ++i) {

        Bucket& bucket = _table[i];

        for (int j = 0; j < BUCKET_SIZE; ++j) {

            if (bucket.entries[j].Active && !bucket.entries[j].Deleted){
                int hash = Hash(bucket.entries[j].Key)%newCapacity;
                int starting_hash = hash;
                int th =1;

                for (int k = 0; th; k++,hash = (starting_hash + (k+1)*(k+1))% newCapacity) {
                    Bucket& newbuck = backup[hash];

                    for (int l = 0; l < BUCKET_SIZE; ++l) {

                        if (!newbuck.entries[l].Active || newbuck.entries[l].Deleted){
                            newbuck.entries[l] = bucket.entries[j];
                            th = 0;
                            break;
                        }
                    }

                }
            }
        }
    }

    _capacity = newCapacity;
    delete[] _table;
    _table = backup;

}


template <class K, class T>
int HashTable<K, T>::Capacity() const {
    return _capacity;
}

template <class K, class T>
int HashTable<K, T>::Size() const {
    return _size;
}


template <class K, class T>
void HashTable<K, T>::getKeys(K* keys) {
    int index = 0;

    for (int i = 0; i < _capacity; i++) {
        Bucket& bucket = _table[i];
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (bucket.entries[j].Active && !bucket.entries[j].Deleted) {
                keys[index++] = bucket.entries[j].Key;
            }
        }
    }
}

#endif