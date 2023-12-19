#pragma once
#include <string>
#include <cassert>
#include "A.h"

class B {
public:
    int id = 0;
    std::string name = "";
    bool sex = false;

public:
    B() = default;
    B(int id, std::string name, bool sex) : id(id), name(name), sex(sex) {}
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