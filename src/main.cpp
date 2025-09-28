#include <iostream>
#include <string>
#include <stdexcept>
#include "/Users/vladislavbaanov/Desktop/OOP_Laba_2/include/binary.hpp"

int main() 
{
    std::string input_a;
    std::string input_b;
    std::cin >> input_a;
    std::cin >> input_b;

    try {
        Binary a(input_a);
        Binary b(input_b);

        Binary add_result = Binary::add(a, b);
        std::cout << Binary::toString(add_result) << std::endl;

        Binary sub_result = Binary::substract(a, b);
        std::cout << Binary::toString(sub_result) << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}