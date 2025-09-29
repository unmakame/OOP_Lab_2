#pragma once
#include <cstddef>
#include <initializer_list>
#include <string>
#include "array.hpp"

class Binary
{
    private:
        Array data;

    public:
        Binary();
        Binary(const size_t& n, unsigned char t = 0);
        Binary(const std::initializer_list<unsigned char>& t);
        Binary(const std::string& t);
        Binary(const Binary& other);
        virtual ~Binary();

        static size_t getSize(const Binary& num);
        static Binary copy(const Binary& num);

        static Binary add(const Binary& a, const Binary& b);
        static Binary substract(const Binary& a, const Binary& b);
        static Binary AND(const Binary& a, const Binary& b);
        static Binary OR(const Binary& a, const Binary& b);
        static Binary XOR(const Binary& a, const Binary& b);
        static Binary NOT(const Binary& a);

        static int compare(const Binary& a, const Binary& b);
        static bool equals(const Binary& a, const Binary& b);
        static bool lessThan(const Binary& a, const Binary& b);
        static bool greaterThan(const Binary& a, const Binary& b);

        static Binary shiftLeft(const Binary& a, size_t positions);
        static Binary shiftRight(const Binary& a, size_t positions);

        static std::string toString(const Binary& num);
};

