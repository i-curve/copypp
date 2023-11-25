/* c++
 * @Author: i-curve
 * @Date: 2023-11-24 17:50:57
 * @Last Modified by: i-curve
 * @Name:
 */
#include <fmt/core.h>
#include <cassert>
#include "icurve/copypp.hh"
#include "A.h"
#include "B.h"

void check();
void check1();
void check2();

int main() {
    fmt::println("copypp test2...");
    check1();
    check2();
    return 0;
}

void check(BB &b, AA &a) {
    assert(a.getId() == b.getId());
    fmt::println("a.name: {}, b.name: {}", a.getName(), b.getName());
    assert(a.getName() == b.getName());
    assert(a.getSex() == b.getSex());
}

void check1() {
    fmt::println("check1:");
    AA a(10, "curve", false);
    a._prepareFields();
    for (auto item : a._data) {
        fmt::println("type: {}, name: {}, size: {}", item.field_type,
                     item.field_name, item.field_size);
    }
}

void check2() {
    AA a(10, "curve", true);
    BB b;
    icurve::copy(b, a);
    check(b, a);
    fmt::println("a: id: {}, name: {}, sex: {}", a.getId(), a.getName(),
                 a.getSex());
    fmt::println("b: id: {}, name: {}, sex: {}", b.getId(), b.getName(),
                 b.getSex());
    fmt::println("check2 ok");
}