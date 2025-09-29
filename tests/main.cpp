#include <gtest/gtest.h>
#include <stdexcept>
#include "binary.hpp"

TEST(BinaryConstructorTest, DefaultConstructor) {
    Binary b;
    EXPECT_EQ(Binary::toString(b), "0");
}

TEST(BinaryConstructorTest, SizeConstructor) {
    Binary b(4, 1);
    EXPECT_EQ(Binary::toString(b), "1111");
}

TEST(BinaryConstructorTest, InitializerListConstructor) {
    Binary b{1, 0, 1, 1};
    EXPECT_EQ(Binary::toString(b), "1101");  
}

TEST(BinaryConstructorTest, StringConstructor) {
    Binary b3("0001101");
    EXPECT_EQ(Binary::toString(b3), "0001101");  
}

TEST(BinaryConstructorTest, InvalidStringConstructor) {
    EXPECT_THROW(Binary("102"), std::invalid_argument);
    EXPECT_THROW(Binary("1A0"), std::invalid_argument);
    EXPECT_THROW(Binary("abc"), std::invalid_argument);
}

TEST(BinaryArithmeticTest, Addition) {
    Binary a("1010");
    Binary b("110");
    Binary result = Binary::add(a, b);
    EXPECT_EQ(Binary::toString(result), "10000");
    
    Binary zero("0");
    Binary add_zero = Binary::add(a, zero);
    EXPECT_EQ(Binary::toString(add_zero), "1010");
}

TEST(BinaryArithmeticTest, Subtraction) {
    Binary a("1101");
    Binary b("101");
    Binary result = Binary::substract(a, b);
    EXPECT_EQ(Binary::toString(result), "1000");
    
    Binary equal_sub = Binary::substract(a, a);
    EXPECT_EQ(Binary::toString(equal_sub), "0");
    
    EXPECT_THROW(Binary::substract(Binary("10"), Binary("11")), std::invalid_argument);
}

TEST(BinaryLogicalTest, AND) {
    Binary a("1101");
    Binary b("1010");
    Binary result = Binary::AND(a, b);
    EXPECT_EQ(Binary::toString(result), "1000");
    
    Binary zero("0");
    Binary and_zero = Binary::AND(a, zero);
    EXPECT_EQ(Binary::toString(and_zero), "0");
}

TEST(BinaryLogicalTest, OR) {
    Binary a("1101");
    Binary b("1010");
    Binary result = Binary::OR(a, b);
    EXPECT_EQ(Binary::toString(result), "1111");
}

TEST(BinaryLogicalTest, XOR) {
    Binary a("1101");
    Binary b("1010");
    Binary result = Binary::XOR(a, b);
    EXPECT_EQ(Binary::toString(result), "111");
}

TEST(BinaryLogicalTest, NOT) {
    Binary a("1010");
    Binary result = Binary::NOT(a);
    EXPECT_EQ(Binary::toString(result), "101");
    
    Binary b("0");
    Binary not_zero = Binary::NOT(b);
    EXPECT_EQ(Binary::toString(not_zero), "1");
}

TEST(BinaryComparisonTest, Equals) {
    Binary a("1010");
    Binary b("1010");
    Binary c("1100");
    
    EXPECT_TRUE(Binary::equals(a, b));
    EXPECT_FALSE(Binary::equals(a, c));
    EXPECT_TRUE(Binary::equals(a, a));
}

TEST(BinaryComparisonTest, LessThan) {
    Binary a("101");
    Binary b("1100");
    
    EXPECT_TRUE(Binary::lessThan(a, b));
    EXPECT_FALSE(Binary::lessThan(b, a));
    EXPECT_FALSE(Binary::lessThan(a, a));
}

TEST(BinaryComparisonTest, GreaterThan) {
    Binary a("1100");
    Binary b("101");
    
    EXPECT_TRUE(Binary::greaterThan(a, b));
    EXPECT_FALSE(Binary::greaterThan(b, a));
    EXPECT_FALSE(Binary::greaterThan(a, a));
}

TEST(BinaryShiftTest, ShiftLeft) {
    Binary a("101");
    
    Binary shift1 = Binary::shiftLeft(a, 1);
    EXPECT_EQ(Binary::toString(shift1), "1010");
    
    Binary shift2 = Binary::shiftLeft(a, 2);
    EXPECT_EQ(Binary::toString(shift2), "10100");
    
    Binary shift0 = Binary::shiftLeft(a, 0);
    EXPECT_EQ(Binary::toString(shift0), "101");
}

TEST(BinaryShiftTest, ShiftRight) {
    Binary a("10100");
    
    Binary shift1 = Binary::shiftRight(a, 1);
    EXPECT_EQ(Binary::toString(shift1), "1010");
    
    Binary shift2 = Binary::shiftRight(a, 2);
    EXPECT_EQ(Binary::toString(shift2), "101");
    
    Binary overshift = Binary::shiftRight(a, 10);
    EXPECT_EQ(Binary::toString(overshift), "0");
}

TEST(BinaryEdgeCasesTest, ZeroOperations) {
    Binary zero("0");
    
    EXPECT_EQ(Binary::toString(zero), "0");
    EXPECT_TRUE(Binary::equals(zero, zero));
    
    Binary add_zero = Binary::add(zero, zero);
    EXPECT_EQ(Binary::toString(add_zero), "0");
    
    Binary sub_zero = Binary::substract(zero, zero);
    EXPECT_EQ(Binary::toString(sub_zero), "0");
}

TEST(BinaryEdgeCasesTest, LargeNumbers) {
    Binary large("1111111111111111");
    Binary one("1");
    
    Binary result = Binary::add(large, one);
    EXPECT_EQ(Binary::toString(result), "10000000000000000");
}

TEST(BinaryUtilityTest, GetSize) {
    Binary empty;
    EXPECT_EQ(Binary::getSize(empty), 1);
    
    Binary small("1");
    EXPECT_EQ(Binary::getSize(small), 1);
    
    Binary large("10000000000000000");
    EXPECT_EQ(Binary::getSize(large), 17);
}

TEST(BinaryUtilityTest, Copy) {
    Binary original("1101");
    Binary copy = Binary::copy(original);
    
    EXPECT_TRUE(Binary::equals(original, copy));
    EXPECT_EQ(Binary::toString(original), Binary::toString(copy));
}

int main(int argc, char **argv) {
    std::cout << "Running Binary Calculator Tests..." << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}