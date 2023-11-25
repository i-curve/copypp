/* c++
 * @Author: i-curve
 * @Date: 2023-11-25 14:43:18
 * @Last Modified by: i-curve
 * @Name:
 */
#include <fmt/core.h>
#include <cassert>
#include <icurve/copypp_only.hh>

class A {
public:
    int id;
    std::string name;
    bool sex;

public:
    A() = default;
    A(int id, std::string name, bool sex) : id(id), name(name), sex(sex) {}
};

class AA {
private:
    int id;
    std::string name;
    bool sex;

public:
    AA() = default;
    AA(int id, std::string name, bool sex) : id(id), name(name), sex(sex) {}

    void setId(decltype(id) id) { this->id = id; }
    void setName(decltype(name) name) { this->name = name; }
    void setSex(decltype(sex) sex) { this->sex = sex; }
    auto getId() const { return this->id; }
    auto getName() const { return this->name; }
    auto getSex() const { return this->sex; }

public:
    COPYPP_FIELDS_INTRUSIVE(id, name, sex)
};

class B {
public:
    int id;
    std::string name;
    bool sex;

public:
    B() = default;
    B(int id, std::string name, bool sex) : id(id), name(name), sex(sex) {}

public:
    COPYPP_FIELDS_INTRUSIVE(id, name, sex)
};

class BB {
private:
    int id;
    std::string name;
    bool sex;

public:
    BB() = default;
    BB(int id, std::string name, bool sex) : id(id), name(name), sex(sex) {}

    void setId(decltype(id) id) { this->id = id; }
    void setName(decltype(name) name) { this->name = name; }
    void setSex(decltype(sex) sex) { this->sex = sex; }
    auto getId() const { return this->id; }
    auto getName() const { return this->name; }
    auto getSex() const { return this->sex; }

public:
    COPYPP_FIELDS_INTRUSIVE(id, name, sex)
};

COPYPP_FIELDS_NON_INTRUSIVE(B, A, id, name, sex)

void check(B &b, A &a) {
    assert(b.id == a.id);
    assert(b.name == a.name);
    assert(b.sex == a.sex);
    fmt::println("check ok.");
}

void checkaa(BB &b, AA &a) {
    assert(b.getId() == a.getId());
    assert(b.getName() == a.getName());
    assert(b.getSex() == a.getSex());
    fmt::println("check ok.");
}

void check1();

void check2();

void check3();

int main() {
    fmt::println("test copypp_only...");
    check1();
    check2();
    check3();
    return 0;
}

void check1() {
    A a(1, "curve", true);
    B b;
    icurve::copy(b, a);
    check(b, a);
}

void check2() {
    AA a(10, "curve", false);
    a._prepareFields();
    for (auto item : a._data) {
        fmt::println("type: {}, name: {}, size: {}", item.field_type,
                     item.field_name, item.field_size);
    }
}

void check3() {
    AA a(10, "curve", true);
    BB b;
    icurve::copy(b, a);
    checkaa(b, a);
    fmt::println("a: id: {}, name: {}, sex: {}", a.getId(), a.getName(),
                 a.getSex());
    fmt::println("b: id: {}, name: {}, sex: {}", b.getId(), b.getName(),
                 b.getSex());
    fmt::println("check2 ok");
}