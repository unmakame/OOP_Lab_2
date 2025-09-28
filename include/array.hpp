#pragma once
#include <string>

class Array {
private:
    size_t _size;
    unsigned char* data;
    void clear();
    void copyFrom(const Array& other);
    
public:
    Array();
    Array(size_t size, unsigned char t = 0);
    Array(const std::initializer_list<unsigned char>& t);
    Array(const std::string& t);
    Array(const Array& other);
    virtual ~Array();

    size_t size() const;
    bool empty() const; 
    void resize(size_t newSize, unsigned char value = 0);
    unsigned char get(const size_t& index) const;
    void set(const size_t& index, const unsigned char& value);
};