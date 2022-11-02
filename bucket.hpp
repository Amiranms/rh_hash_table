#ifndef BUCKET_H
#define BUCKET_H

#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include <cassert>
#include <cmath>

const int EMPTY_BUCKET = -1;

template<typename key_type, typename val_type>
class bucket {
private:
    key_type m_key;
    val_type m_val;
    int m_dist_from_hash;

public:
    bucket(key_type key = {}, val_type val = {}, int dist_from_hash = EMPTY_BUCKET) :
        m_key(key),
        m_val(val),
        m_dist_from_hash(dist_from_hash)
    { }

    bucket(const bucket<key_type, val_type>& other) :
        m_key(other.m_key),
        m_val(other.m_val),
        m_dist_from_hash(other.m_dist_from_hash)
    { }

    bucket(bucket<key_type, val_type>&& other) :
        m_key(other.m_key),
        m_val(other.m_val),
        m_dist_from_hash(other.m_dist_from_hash)
    { other.clear(); }

    bucket<key_type, val_type>& operator=(const bucket<key_type, val_type>& other) {
        if (this != &other) {
            this->m_key = other.m_key;
            this->m_val = other.m_val;
            this->m_dist_from_hash = other.m_dist_from_hash;
        }
        return *this;
    }

    bucket<key_type, val_type>& operator=(bucket<key_type, val_type>&& other) {
        if (this != &other) {
            this->m_key = other.m_key;
            this->m_val = other.m_val;
            this->m_dist_from_hash = other.m_dist_from_hash;
            other.clear();
        }
        return *this;
    }

    const key_type key()       const { return m_key; }
    const val_type value()     const { return m_val; }
    const int dist_from_hash() const { return m_dist_from_hash; }

    void dist_modify(int shift = 0)        { this->m_dist_from_hash += shift; }
    bool empty()                     const { return m_dist_from_hash == EMPTY_BUCKET; }

    void swap(bucket<key_type, val_type>& other) {
        std::swap(this->m_key, other.m_key);
        std::swap(this->m_val, other.m_val);
        std::swap(this->m_dist_from_hash, other.m_dist_from_hash);
    }

    void clear() {
        this->m_dist_from_hash = EMPTY_BUCKET;
    }

    friend std::ostream& operator<<(std::ostream& out, const bucket<key_type, val_type>& bucket) {
        out << "{ " << bucket.key() << "\" : " << bucket.value() << " " <#include <> bucket.dist_from_hash() << "] \"";
        return out;
    }
};

#endif // BUCKET_H