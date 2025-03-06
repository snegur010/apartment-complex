#ifndef MYCLASS_HPP
#define MYCLASS_HPP

#include <stdexcept>
#include <iostream>
#include <utility>

template <class T, class V>
class ViewableTable {
private:

    class Entry {
        public:

            T key;
            V value;

            Entry() = default;
            Entry(const T& k, V& v) : key(std::move(k)), value(std::move(v)) {};
            ~Entry() = default;
    };

    Entry* entries_ = nullptr;
    int size_ = 0;
    int capacity_ = 0;


    void resize() {
        capacity_ *= 2;
        Entry* new_entries = new Entry[capacity_];
        for (int i = 0; i < size_; ++i) {
            new_entries[i] = std::move(entries_[i]);
        }
        delete[] entries_;
        entries_ = new_entries;
    }

public:

    ViewableTable(int capacity = 10) : entries_(new Entry[capacity]), size_(0), capacity_(capacity) {}

    ~ViewableTable() {
        delete[] entries_;
    }

    V& get(const T& key) {
        for (int i = 0; i < size_; ++i) {
            if (entries_[i].key == key) {
                return entries_[i].value;
            }
        }
        throw std::out_of_range("Key not found");
    }

    void add(const T& key, V& value) {
        for (int i = 0; i < size_; ++i) {
            if (entries_[i].key == key) {
                throw std::logic_error("Key already in the table");
            }
        }
        if (size_ == capacity_) {
            resize();
        }
        entries_[size_++] = Entry(key, value);
    }

    void add(T&& key, V&& value) {
        for (int i = 0; i < size_; ++i) {
            if (entries_[i].key == key) {
                throw std::logic_error("Key already in the table");
            }
        }
        if (size_ == capacity_) {
            resize();
        }
        entries_[size_++] = Entry(std::move(key), std::move(value));
    }

    int get_size() const {
        return size_;
    }

    V& operator[](int index) {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return entries_[index].value;
    }


    class Iterator {
    private:
        Entry* current_;

    public:

        explicit Iterator(Entry* ptr) : current_(ptr) {}

        Entry& operator*() const {
            return *current_;
        }

        Iterator& operator++() {
            ++current_;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }
    };


    Iterator begin() {
        return Iterator(entries_);
    }

    Iterator end() {
        return Iterator(entries_ + size_);
    }
};

#endif