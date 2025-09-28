#include <string>
#include <cstring>
#include <stdexcept>
#include "binary.hpp"

Binary::Binary() : data(1, 0) {}

Binary::Binary(const size_t& n, unsigned char t): data(n, t) {}

Binary::Binary(const std::initializer_list<unsigned char>& t): data(t) {}

Binary::Binary(const std::string& s): data(s) {}

Binary::Binary(const Binary& other): data(other.data) {}

Binary::~Binary() {}

size_t Binary::getSize(const Binary& num) 
{
    return num.data.size();
}

int Binary::compare(const Binary& a, const Binary& b)
{
    if (a.data.size() > b.data.size()) return 1;
    if (a.data.size() < b.data.size()) return -1;

    for (int i = a.data.size() - 1; i >= 0; --i)
    {
        if (a.data.get(i) > b.data.get(i)) return 1;
        if (a.data.get(i) < b.data.get(i)) return -1;
    }

    return 0;
} 

Binary Binary::copy(const Binary& num) 
{
    return Binary(num);
}

Binary Binary::add(const Binary& a, const Binary& b)
{
    size_t maxSize = std::max(a.data.size(), b.data.size());
    Binary result(maxSize + 1, 0);

    int carry = 0;
    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_a = (i < a.data.size()) ? a.data.get(i) : 0;
        int digit_b = (i < b.data.size()) ? b.data.get(i) : 0;

        int sum = digit_a + digit_b + carry;
        result.data.set(i, sum % 2);
        carry = sum / 2;
    }

    if (carry > 0)
    {
        result.data.set(maxSize, carry);
    }
    else
    {
        size_t newSize = maxSize;
        while (newSize > 1 && result.data.get(newSize - 1) == 0)
        {
            --newSize;
        }
        result.data.resize(newSize);
    }

    return result;
}

Binary Binary::substract(const Binary& a, const Binary& b)
{
    int cmp = compare(a, b);

    if (cmp < 0)
    {
        throw std::invalid_argument("Negative number in substraction result");
    }
    if (cmp == 0)
    {
        return Binary(1, 0);
    }

    size_t maxSize = a.data.size();
    Binary result(maxSize, 0);

    int borrow = 0;

    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_a = a.data.get(i);
        int digit_b = (i < b.data.size()) ? b.data.get(i) : 0;

        int diff = digit_a - digit_b - borrow;

        if (diff < 0)
        {
            diff += 2;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result.data.set(i, diff);
    }

    size_t newSize = maxSize;
    while(newSize > 1 && result.data.get(newSize - 1) == 0)
    {
        --newSize;
    }

    result.data.resize(newSize);

    return result;
}

Binary Binary::AND(const Binary& a, const Binary& b)
{
    size_t maxSize = std::max(a.data.size(), b.data.size());
    Binary result(maxSize, 0);

    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_a = (i < a.data.size()) ? a.data.get(i) : 0;
        int digit_b = (i < b.data.size()) ? b.data.get(i) : 0;
        result.data.set(i, digit_a & digit_b);
    }

    size_t newSize = maxSize;
    while (newSize > 1 && result.data.get(newSize - 1) == 0)
    {
        --newSize;
    }
    result.data.resize(newSize);

    return result;
}

Binary Binary::OR(const Binary& a, const Binary& b)
{
    size_t maxSize = std::max(a.data.size(), b.data.size());
    Binary result(maxSize, 0);

    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_a = (i < a.data.size()) ? a.data.get(i) : 0;
        int digit_b = (i < b.data.size()) ? b.data.get(i) : 0;
        result.data.set(i, digit_a | digit_b);
    }

    return result;
}

Binary Binary::XOR(const Binary& a, const Binary& b)
{
    size_t maxSize = std::max(a.data.size(), b.data.size());
    Binary result(maxSize, 0);

    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_a = (i < a.data.size()) ? a.data.get(i) : 0;
        int digit_b = (i < b.data.size()) ? b.data.get(i) : 0;
        result.data.set(i, digit_a ^ digit_b);
    }

    size_t newSize = maxSize;
    while (newSize > 1 && result.data.get(newSize - 1) == 0)
    {
        --newSize;
    }
    result.data.resize(newSize);

    return result;
}

Binary Binary::NOT(const Binary& a)
{
    Binary result(a.data.size(), 0);

    for (size_t i = 0; i < a.data.size(); ++i)
    {
        // Инвертируем бит: 0 -> 1, 1 -> 0
        result.data.set(i, 1 - a.data.get(i));
    }

    // Убираем ведущие нули
    size_t newSize = result.data.size();
    while (newSize > 1 && result.data.get(newSize - 1) == 0)
    {
        --newSize;
    }
    result.data.resize(newSize);

    return result;
}

Binary Binary::shiftLeft(const Binary& a, size_t positions)
{
    Binary result(a.data.size() + positions, 0);

    for (size_t i = 0; i < a.data.size(); ++i)
    {
        result.data.set(i + positions, a.data.get(i));
    }

    return result;
}

Binary Binary::shiftRight(const Binary& a, size_t positions)
{
    if (positions >= a.data.size())
    {
        return Binary(1, 0);
    }

    Binary result(a.data.size() - positions, 0);

    for (size_t i = positions; i < a.data.size(); ++i)
    {
        result.data.set(i - positions, a.data.get(i));
    }

    return result;
}

bool Binary::lessThan(const Binary& a, const Binary& b) 
{
    return compare(a, b) < 0;
}

bool Binary::greaterThan(const Binary& a, const Binary& b) 
{
    return compare(a, b) > 0;
}

bool Binary::equals(const Binary& a, const Binary& b) 
{
    return compare(a, b) == 0;
}

std::string Binary::toString(const Binary& num)
{
    if (num.data.empty() || (num.data.size() == 1 && num.data.get(0) == 0))
    {
        return "0";
    }

    std::string result;

    for (int i = num.data.size() - 1; i >= 0; --i)
    {
        result += (num.data.get(i) ? '1' : '0');
    }

    return result;
}