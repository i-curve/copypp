#pragma once
#include <string>
#include "icurve/copypp.hh"
#include <fmt/core.h>

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