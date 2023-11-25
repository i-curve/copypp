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
    COPYPP_FIELDS_INTRUSIVE(id, name, sex)
    // void _prepareFields() {
    //     if (this->_is_prepare) {
    //         return;
    //     }
    //     this->_data.push_back(
    //         _copypp_raw_meta(typeid(id).name(), "id", sizeof(id), &id));
    //     this->_data.push_back(
    //         _copypp_raw_meta(typeid(name).name(), "name", sizeof(name),
    //         &name));
    //     this->_data.push_back(
    //         _copypp_raw_meta(typeid(sex).name(), "sex", sizeof(sex), &sex));
    //     this->_is_prepare = true;
    //     return;
    // }
    // void _setField(std::string name, void *val) {
    //     if (1 == 0) {
    //     } else if (name == "id") {
    //         _setid(*static_cast<decltype(id) *>(val));
    //     } else if (name == "name") {
    //         _setname(*static_cast<decltype(name) *>(val));
    //     } else if (name == "sex") {
    //         _setsex(*static_cast<decltype(sex) *>(val));
    //     }
    // }
};