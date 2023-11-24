/* c++
 * @Author: i-curve
 * @Date: 2023-11-24 15:35:57
 * @Last Modified by: i-curve
 * @Name:
 */
#include <fmt/core.h>
#include <cassert>
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
    assert(aa._getid() == 12);
    assert(aa._getname() == "i-curve");
    assert(aa._getsex() == true);
    aa._setid(5);
    assert(aa._getid() == 5);
    aa._setname("xxx");
    fmt::println("aa.id: {}, aa.name: {}, aa.sex: {}", aa._getid(),
                 aa._getname(), aa._getsex());
    fmt::println("checkaa ok.");
}

// COPYPP
int main() {
    fmt::println("copypp test...");
    A a(1, "curve", true);
    B b;
    icurve::copy(b, a);
    check(b, a);

    checkaa();
    return 0;
}