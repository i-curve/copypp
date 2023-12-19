/* c++
 * @Author: i-curve
 * @Date: 2023-11-25 14:43:18
 * @Last Modified by: i-curve
 * @Name:
 */
#include <fmt/core.h>
#include <cassert>
#include <list>
#include <array>
#include <icurve/copypp_only.hh>
#include <gtest/gtest.h>

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
    COPYPP_FIELDS_INTRUSIVE(AA, id, name, sex)
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
    COPYPP_FIELDS_INTRUSIVE(B, id, name, sex)
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
    COPYPP_FIELDS_INTRUSIVE(BB, id, name, sex)
};

COPYPP_FIELDS_NON_INTRUSIVE(B, A, id, name, sex)

void checkA(A a, B b) {
    assert(a.id == b.id);
    assert(a.name == b.name);
    assert(a.sex == b.sex);
}

void checkAA(AA a, BB b) {
    assert(a.getId() == b.getId());
    assert(a.getName() == b.getName());
    assert(a.getSex() == b.getSex());
}

TEST(COPYPP_ONLY, _1) {
    A a(1, "curve", true);
    B b;
    icurve::copy(b, a);
    checkA(a, b);
}

TEST(COPYPP_ONLY, _2) {
    AA a(10, "curve", false);
    a._prepareFields();
    for (auto item : a._data) {
        fmt::println("type: {}, name: {}, size: {}", item.field_type,
                     item.field_name, item.field_size);
    }
}

TEST(COPYPP_ONLY, _3) {
    AA a(10, "curve", true);
    BB b;
    icurve::copy(b, a);
    checkAA(a, b);
    fmt::println("a: id: {}, name: {}, sex: {}", a.getId(), a.getName(),
                 a.getSex());
    fmt::println("b: id: {}, name: {}, sex: {}", b.getId(), b.getName(),
                 b.getSex());
    fmt::println("check2 ok");
}

TEST(COPYPP_ARRAY, TEXT_KNOW) {
    if (std::is_convertible<int, double>::value) {
        std::cout << "can change int to double\n";
    } else {
        std::cout << "can't change int to double\n";
    }
    if (std::is_convertible<double, int>::value) {
        std::cout << "cant chagne double to int\n";
    } else {
        std::cout << "can't change double to int\n";
    }
}

TEST(COPYPP_ARRAY, _1) {
    AA a[3];
    BB b[2] = {BB(1, "first", true), BB(2, "second", false)};

    icurve::copy(a, b);
    checkAA(a[0], b[0]);
    checkAA(a[1], b[1]);
    // icurve::copy(std::span<AA>(a, 3), std::span<BB>(b, 2));
    // icurve::copy(std::span<AA>(a), std::span<BB>(b));
}

TEST(COPYPP_ARRAY, _2) {
    std::array<AA, 2> a;
    std::array<BB, 2> b = {BB(1, "first", true), BB(2, "second", false)};
    // a.clear();
    icurve::copy(a, b);
    for (int i = 0; i < 2; i++) {
        EXPECT_TRUE(a[i].getId() == b[i].getId());
        EXPECT_TRUE(a[i].getName() == b[i].getName());
        EXPECT_TRUE(a[i].getSex() == b[i].getSex());
    }
}

TEST(COPYPP_ARRAY, _3) {
    AA a[3];
    BB b[2] = {BB(1, "first", true), BB(2, "second", false)};
    std::span<AA> aa(a);
    std::span<BB> bb(b);
    icurve::copy(aa, bb);
    checkAA(aa[0], bb[0]);
    checkAA(aa[1], bb[1]);
}

TEST(COPYPP_ARRAY, _4) {
    std::vector<AA> a;
    std::vector<BB> b = {BB(1, "first", true), BB(2, "second", false)};
    // std::back_insert_iterator(a);
    // std::vector<AA>::it
    // std::back_inserter(b, BB(1, "first", true));
    icurve::copy(a, b);
    for (int i = 0; i < 2; i++) {
        EXPECT_TRUE(a[i].getId() == b[i].getId());
        EXPECT_TRUE(a[i].getName() == b[i].getName());
        EXPECT_TRUE(a[i].getSex() == b[i].getSex());
    }
}

TEST(COPYPP_ARRAY, _5) {
    std::list<int> n1;
    // std::back_insert(n1, 12);
    n1.push_back(5);
}
TEST(COPYPP_ARRAY, _x) {
    A a = {3, "minal a", false};
    B b;
    /// compile error
    // icurve::copy(b, a);
    int c = 25;
    int d;
    icurve::copy(d, c);
}

TEST(COPYPP_ARRAY, tmp) {
    int a[3] = {1, 2, 3};
    int b[3];
    icurve::copy(b, a);
    EXPECT_TRUE(a[0] == b[0]);
    EXPECT_TRUE(a[1] == b[1]);
    EXPECT_TRUE(a[2] == b[2]);
    int c = 5;
    int d;
    icurve::copy(d, c);
    EXPECT_TRUE(c == d);
}

TEST(COPYPP_STL, _1) {
    std::vector<AA> a = {AA(1, "first", true), AA(2, "second", false)};
    std::list<BB> b;
    icurve::copy(b, a);
    EXPECT_TRUE(b.size() == a.size());
    size_t s = 0;
    for (auto [ap, bp] = std::make_tuple(a.begin(), b.begin());
         ap != a.end(), bp != b.end(); ++ap, ++bp) {
        s++;
        checkAA(*ap, *bp);
    }
    EXPECT_TRUE(s == a.size());
}

TEST(COPYPP_STL, _2) {
    std::vector<AA> a = {AA(1, "first", true), AA(2, "second", false)};
    std::array<BB, 1> b;
    std::array<BB, 3> c;
    icurve::copy(b, a);
    icurve::copy(c, a);
    EXPECT_TRUE(a.size() == 2);
    EXPECT_TRUE(b.size() == 1);
    checkAA(a[0], b[0]);
    checkAA(a[0], c[0]);
    checkAA(a[1], c[1]);
}