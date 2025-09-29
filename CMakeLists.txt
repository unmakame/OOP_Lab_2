cmake_minimum_required(VERSION 3.10)
project(BinaryCalculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)


add_executable(binary_calculator
    src/main.cpp
    src/binary.cpp
    src/array.cpp
)


enable_testing()

find_package(GTest QUIET)

if(GTest_FOUND)
    add_executable(binary_tests
        tests/main.cpp
        src/binary.cpp
        src/array.cpp
    )
    
    target_link_libraries(binary_tests GTest::GTest GTest::Main)
    add_test(NAME BinaryTests COMMAND binary_tests)
else()
    message(WARNING "Google Test not found - tests will not be built")
endif()
