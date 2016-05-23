#pragma once

#include <iostream>

#define ASSERT( exp, test ) test_assert((test), (exp), __FILE__, __LINE__)
#define LAUNCH( func ) test_launch((#func), (func))

int tests_h_total = 0;
int tests_h_ok = 0;

void test_assert(const char* test, bool exp, const char* file, int line)
{
    ++tests_h_total;
    std::cout << "Test: " << test << "...\n";
    if (exp)
    {
        ++tests_h_ok;
        std::cout << "\tOK" << std::endl;
    }
    else
        std::cerr << "NOK: " << file << ":" << line << std::endl;
}

void test_launch(const char* test, void (*func)())
{
    std::cout << "==== Running test " << test << " ====\n";
    tests_h_total = 0;
    tests_h_ok = 0;
    func();
    std::cout << "------\n"
              << "Result: \n"
              << "\tPassed: " << tests_h_ok << "\n"
              << "\tFailed: " << tests_h_total - tests_h_ok << "\n"
              << "\tTotal: " << tests_h_total << std::endl;
}