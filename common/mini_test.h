#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace mini {

struct Case {
    std::string name;
    std::function<void()> fn;
};

inline std::vector<Case>& registry() {
    static std::vector<Case> cases;
    return cases;
}

inline int& failuresInCurrentTest() {
    static int n = 0;
    return n;
}

struct Registrar {
    Registrar(const std::string& name, std::function<void()> fn) {
        registry().push_back({name, std::move(fn)});
    }
};

inline void addCase(const std::string& name, std::function<void()> fn) {
    registry().push_back({name, std::move(fn)});
}

template <class A, class B>
void checkEq(const A& expected, const B& actual, const char* expr,
             const char* file, int line) {
    if (!(expected == actual)) {
        ++failuresInCurrentTest();
        std::ostringstream e, a;
        e << expected;
        a << actual;
        std::cout << "    " << file << ":" << line << ": CHECK_EQ failed: "
                  << expr << "\n      expected: " << e.str()
                  << "\n      actual:   " << a.str() << std::endl;
    }
}

inline void checkTrue(bool cond, const char* expr, const char* file, int line) {
    if (!cond) {
        ++failuresInCurrentTest();
        std::cout << "    " << file << ":" << line
                  << ": CHECK_TRUE failed: " << expr << std::endl;
    }
}

inline int runAll() {
    int passed = 0, failed = 0;
    for (const auto& c : registry()) {
        failuresInCurrentTest() = 0;
        c.fn();
        if (failuresInCurrentTest() == 0) {
            std::cout << "[  OK  ] " << c.name << std::endl;
            ++passed;
        } else {
            std::cout << "[ FAIL ] " << c.name << std::endl;
            ++failed;
        }
    }
    std::cout << "\nTests: " << (passed + failed) << ", passed: " << passed
              << ", failed: " << failed << std::endl;
    return failed == 0 ? 0 : 1;
}

} 

#define TEST(name)                                                         \
    static void name();                                                    \
    static mini::Registrar registrar_##name(#name, name);                  \
    static void name()

#define CHECK_EQ(expected, actual) \
    mini::checkEq((expected), (actual), #expected " == " #actual, __FILE__, __LINE__)
#define CHECK_TRUE(cond) \
    mini::checkTrue((cond), #cond, __FILE__, __LINE__)
#define RUN_ALL_TESTS() mini::runAll()
