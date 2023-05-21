#include <catch2/catch_test_macros.hpp>
#include <random>
#include <limits>
#include "VInt.h"
#include <string>

using namespace std;

#define GENERATE_COUNT 1000000

TEST_CASE("VInt instance & casting"){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(1, numeric_limits<unsigned int>::max());
    std::string testNum;
    SECTION("Default VInt"){
        VInt num;
        VInt explicitZero = 0;
        REQUIRE(static_cast<int>(num) == 0);
        REQUIRE(num == explicitZero);
        REQUIRE(num == VInt(0));
    }
    for (unsigned int i = 0; i < GENERATE_COUNT; i ++){
        testNum = to_string(i);
        SECTION("VInt Creation", testNum.c_str()){
            unsigned long long a = dist(rng);
            VInt va = a;
            REQUIRE(static_cast<unsigned long long>(va) == a);
        }
    }
    
    for (unsigned int i = 0; i < GENERATE_COUNT; i ++){
        testNum = to_string(i);
        SECTION("VInt comapre ", testNum.c_str()){
            unsigned int a = dist(rng);
            unsigned int b = dist(rng);
            VInt va = a, vb = b;
            REQUIRE((a == b) == (va == vb));
            REQUIRE((a <= b) == (va <= vb));
            REQUIRE((a >= b) == (va >= vb));
            REQUIRE((a < b) == (va < vb));
            REQUIRE((a > b) == (va > vb));
        }
    }

    for (unsigned int i = 0; i < GENERATE_COUNT; i ++){
        testNum = to_string(i);
        SECTION("VInt addition", testNum.c_str()){
            unsigned long long a = dist(rng);
            unsigned long long b = dist(rng);
            VInt va = a, vb = b;
            unsigned long long res = a + b;
            VInt vRes = va + vb;
            REQUIRE(static_cast<unsigned long long>(vRes) == res);
        }
    }

    for (unsigned int i = 0; i < GENERATE_COUNT; i ++){
        testNum = to_string(i);
        SECTION("VInt substitution", testNum.c_str()){
            unsigned int a = dist(rng);
            unsigned int b = dist(rng);
            VInt va = a, vb = b;
            unsigned int res = a - b;
            VInt vRes = va - vb;
            unsigned long long castedResult = static_cast<unsigned long long>(vRes);
            REQUIRE(castedResult == res);
        }
    }

    for (unsigned int i = 0; i < GENERATE_COUNT; i ++){
        testNum = to_string(i);
        SECTION("VInt right-shift", testNum.c_str()){
            unsigned long long a = dist(rng);
            unsigned long long b = dist(rng);
            VInt va = a;
            VInt vb = b;
            for (int j = 1; j <= 32; j ++){
                a >>=1;
                va >>=1;
                VInt resVB = vb >> i;
                REQUIRE(static_cast<unsigned long long>(va) == a);
                REQUIRE(static_cast<unsigned long long>(resVB) == (b >> i));
            }
        }
    }
    for (unsigned int i = 0; i < GENERATE_COUNT; i ++){
        testNum = to_string(i);
        SECTION("VInt left-shift", testNum.c_str()){
            unsigned long long a = dist(rng);
            unsigned long long b = dist(rng);
            VInt va = a;
            VInt vb = b;
            for (int j = 1; j <= 32; j ++){
                a <<=1;
                va <<=1;
                VInt resVB = vb.operator<<(i);
                REQUIRE(static_cast<unsigned long long>(va) == a);
                REQUIRE(static_cast<unsigned long long>(resVB) == (b << i));
            }
        }
    }

    for (unsigned int i = 0; i < GENERATE_COUNT; i ++){
        testNum = to_string(i);
        SECTION("VInt AND operator", testNum.c_str()){
            unsigned long long a = dist(rng);
            unsigned long long b = dist(rng);
            VInt va = a;
            VInt vb = b;
            a &= b;
            va &= vb;
            REQUIRE(static_cast<unsigned long long>(va) == a);
        }
    }

    for (unsigned int i = 0; i < GENERATE_COUNT; i ++){
        testNum = to_string(i);
        SECTION("VInt OR operator", testNum.c_str()){
            unsigned long long a = dist(rng);
            unsigned long long b = dist(rng);
            VInt va = a;
            VInt vb = b;
            a |= b;
            va |= vb;
            REQUIRE(static_cast<unsigned long long>(va) == a);
        }
    }

    for (unsigned int i = 0; i < GENERATE_COUNT; i ++){
        testNum = to_string(i);
        SECTION("VInt XOR operator", testNum.c_str()){
            unsigned long long a = dist(rng);
            unsigned long long b = dist(rng);
            VInt va = a;
            VInt vb = b;
            a ^= b;
            va ^= vb;
            REQUIRE(static_cast<unsigned long long>(va) == a);
        }
    }

    for (unsigned int i = 0; i < GENERATE_COUNT; i ++){
        testNum = to_string(i);
        SECTION("VInt multiplication", testNum.c_str()){
            unsigned long long a = dist(rng);
            unsigned long long b = dist(rng);
            VInt va = a, vb = b;
            unsigned long long res = a * b;
            VInt vRes = va * vb;
            unsigned long long castedResult = static_cast<unsigned long long>(vRes);
            REQUIRE(castedResult == res);
        }
    }

}
