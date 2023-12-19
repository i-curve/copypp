/* c++
 * @Author: i-curve
 * @Date: 2023-11-24 15:35:57
 * @Last Modified by: i-curve
 * @Name:
 */
#include <fmt/core.h>
#include <cassert>
#include <gtest/gtest.h>
#include "icurve/copypp.hh"
#include "A.h"
#include "B.h"

COPYPP_FIELDS_NON_INTRUSIVE(B, A, id, name, sex)

void check(B &b, A &a) {
    assert(b.id == a.id);
    assert(b.name == a.name);
    assert(b.sex == a.sex);
    fmt::println("check ok.");
}

void checkaa() {
    AA aa(12, "i-curve", true);
    assert(aa.getId() == 12);
    assert(aa.getName() == "i-curve");
    assert(aa.getSex() == true);
    aa.setId(5);
    assert(aa.getId() == 5);
    aa.setName("xxx");
    fmt::println("aa.id: {}, aa.name: {}, aa.sex: {}", aa.getId(), aa.getName(),
                 aa.getSex());
    fmt::println("checkaa ok.");
}

// COPYPP
TEST(COPYPP_TEST1, _1) {
    fmt::println("copypp test...");
    A a(1, "curve", true);
    B b;
    icurve::copy(b, a);
    check(b, a);

    checkaa();
}