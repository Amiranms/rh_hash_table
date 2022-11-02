#ifndef NOT_RH_HASH_H
#define NOT_RH_HASH_H

#include <functional>
#include <iostream>
#include <iterator>
#include <string>
// #include <utility>
#include <vector>

#include <cassert>
#include <cmath>

#include "bucket.hpp"

const size_t DEFAULT_CAPACITY = 2;
const double MAX_LOAD_FACTOR = 0.95;

template<typename key_type, typename val_type, typename hash_func = std::hash<key_type>>
class rh_map {
private:
    size_t m_size;
    size_t m_capacity;
    size_t m_max_size;
    double m_max_load_factor;
    std::vector<bucket<key_type, val_type>> m_storage;

public:
    rh_map(const size_t capacity = DEFAULT_CAPACITY, const double max_load_factor = MAX_LOAD_FACTOR) :
        m_size(0),
        m_capacity(capacity),
        m_max_size(std::floor(std::clamp(max_load_factor, 0.0, 1.0) * m_capacity)),
        m_max_load_factor(max_load_factor),
        m_storage(m_capacity)
    { }

    rh_map(const rh_map<key_type, val_type, hash_func>& other) :
        m_size(other.m_size),
        m_capacity(other.m_capacity),
        m_max_size(other.m_max_size),
        m_max_load_factor(other.m_max_load_factor),
        m_storage(other.m_storage)
    { }

    rh_map(rh_map<key_type, val_type, hash_func>&& other) :
        m_size(other.m_size),
        m_capacity(other.m_capacity),
        m_max_size(other.m_max_size),
        m_max_load_factor(other.m_max_load_factor),
        m_storage(other.m_storage)
    { other.clear(); }

    rh_map<key_type, val_type, hash_func>& operator=(const rh_map<key_type, val_type, hash_func>& other) {
        if (this != &other) {
            this->m_size = other.m_size;
            this->m_capacity = other.m_capacity;
            this->m_max_size = other.m_max_size;
            this->m_max_load_factor = other.m_max_load_factor;
            this->m_storage = other.m_storage;
        }
        return *this;
    }

    rh_map<key_type, val_type, hash_func>& operator=(rh_map<key_type, val_type, hash_func>&& other) {
        if (this != &other) {
            this->m_size = other.m_size;
            this->m_capacity = other.m_capacity;
            this->m_max_size = other.m_max_size;
            this->m_max_load_factor = other.m_max_load_factor;
            this->m_storage = other.m_storage;
            other.clear();
        }
        return *this;
    }

    const size_t hash_key(const key_type& key) const {
        return hash_func{}(key) % m_capacity;
    }

    size_t size()            const { return m_size; }
    size_t capacity()        const { return m_capacity; }
    size_t max_size()        const { return m_max_size; }
    size_t max_load_factor() const { return m_max_load_factor; }
    bool empty()             const { return m_size == 0; }

    void clear() {
        m_size = 0;
        m_capacity = DEFAULT_CAPACITY;
        m_storage.resize(DEFAULT_CAPACITY);
        for (auto &bucket : m_storage) {
            bucket.clear();
        }
    }

    void swap(rh_map<key_type, val_type, hash_func>& other) {
        std::swap(this->m_size, other.m_size);
        std::swap(this->m_capacity, other.m_capacity);
        std::swap(this->m_max_size, other.m_max_size);
        std::swap(this->m_max_load_factor, other.m_max_load_factor);
        std::swap(this->m_storage, other.m_storage);
    }

    void expand_and_rehash() {
        rh_map<key_type, val_type, hash_func> rh_new(2 * m_capacity, m_max_load_factor);
        for (auto& bucket : m_storage) {
            if (!bucket.empty()) {
                rh_new.insert(bucket.key(), bucket.value());
            }
        }
        rh_new.swap(*this);
    }

    void insert(key_type key, val_type val) {
        if (m_size + 1 == m_max_size) {
            expand_and_rehash();
        }

        bucket<key_type, val_type> cur_bucket = bucket<key_type, val_type>(key, val, 0);

        while (!cur_bucket.empty()) {
            size_t cur_hash = (hash_key(cur_bucket.key()) + cur_bucket.dist_from_hash()) % m_capacity;
            
            while (cur_bucket.key() != m_storage[cur_hash].key() && cur_bucket.dist_from_hash() <= m_storage[cur_hash].dist_from_hash()) {
                cur_hash = (cur_hash + 1) % m_capacity;
                cur_bucket.dist_modify(1);
            }

            cur_bucket.swap(m_storage[cur_hash]);

            if (cur_bucket.empty()) {
                m_size++;
            }

            if (cur_bucket.key() == m_storage[cur_hash].key()) {
                cur_bucket.clear();
            }
        }
    }

    void erase(key_type key) {
        auto it = find(key, hash_key(key));

        if (it != end()) {
            it->clear();
            m_size--;

            size_t pre_hash = std::distance(m_storage.begin(), it);
            size_t cur_hash = (pre_hash + 1) % m_capacity;
            
            while (m_storage[cur_hash].dist_from_hash() > 0) {                
                m_storage[pre_hash].swap(m_storage[cur_hash]);
                m_storage[pre_hash].dist_modify(-1);

                pre_hash = cur_hash;
                cur_hash = (cur_hash + 1) % m_capacity;
            }
        }
    }

    typename std::vector< bucket<key_type, val_type> >::iterator find(key_type key) {
        return find(key, hash_key(key));
    }

    typename std::vector< bucket<key_type, val_type> >::iterator find(key_type key, size_t hash_key) {
        size_t cur_hash = hash_key % m_capacity;
        int cur_dist_from_hash = 0;

        while (cur_dist_from_hash <= m_storage[cur_hash].dist_from_hash()) {
            if (key == m_storage[cur_hash].key()) {
                return (m_storage.begin() + cur_hash);
            }
            
            cur_hash = (cur_hash + 1) % m_capacity;
            cur_dist_from_hash++;
        }
        
        return end();
    }

    void print(bool all = false, int limit = -1) {
        if (limit < 0) limit = m_capacity;
        int count = 0;
        for (size_t i = 0; i < m_capacity && count < limit; i++) {
            if (all || !m_storage[i].empty()) {
                std::cout << m_storage[i] << std::endl;
                count++;
            }
        }
    }

    typename std::vector< bucket<key_type, val_type> >::iterator begin() noexcept { return m_storage.begin(); }
    typename std::vector< bucket<key_type, val_type> >::const_iterator cbegin() const noexcept { return m_storage.cbegin(); }

    typename std::vector< bucket<key_type, val_type> >::iterator end() noexcept { return m_storage.end(); }
    typename std::vector< bucket<key_type, val_type> >::const_iterator cend() const noexcept { return m_storage.cend(); }
};

#endif