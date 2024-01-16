# COPYPP

[![cMake on multiple platforms](https://github.com/i-curve/copypp/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/i-curve/copypp/actions/workflows/cmake-multi-platform.yml)
[![Vcpkg Version](https://img.shields.io/vcpkg/v/copypp)](https://vcpkg.link/ports/copypp)
[![Conan Center](https://img.shields.io/conan/v/copypp)](https://conan.io/center/recipes/copypp)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/i-curve/copypp/raw/master/LICENSE)

support field copy in different c++ data type.

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [COPYPP](#copypp)
  - [Required](#required)
  - [Usage](#usage)
    - [struct/class](#structclass)
    - [json string](#json-string)
    - [array copy](#array-copy)
    - [stl support](#stl-support)
  - [Integration](#integration)
    - [copy the single header file](#copy-the-single-header-file)
    - [cmake](#cmake)
    - [vcpkg](#vcpkg)
    - [conan](#conan)
  - [License](#license)

<!-- /code_chunk_output -->

## Required

c++20

## Usage

- COPYPP_FIELDS_NON_INTRUSIVE(destination, source, field1, field2, ...) is to be defined inside the namespace of the class/struct to create code for.
- COPYPP_FIELDS_INTRUSIVE(field1, field2, field3, ...) is to be defined outside the namespace of class/struct to create code for. This macro can also access private members.
- copy between json string and struct
- support array copy

include the header file

```c++
#include <icurve/copypp.hh>
```

### struct/class

COPYPP_FIELDS_NON_INTRUSIVE
defination the need to copy class

```c++
class A {
public:
    int id;
    std::string name;
    bool sex;

public:
    A() = default;
    A(int id, std::string name, bool sex) : id(id), name(name), sex(sex) {}
};

class B {
public:
    int id;
    std::string name;
    bool sex;

public:
    B() = default;
    B(int id, std::string name, bool sex) : id(id), name(name), sex(sex) {}
};
```

add the fields

```c++
// need to copy fields from A to B
COPYPP_FIELDS_NON_INTRUSIVE(B, A, id, name, sex)
```

```c++
// declare variables
A a(1, "curve", true);
B b;
// copy a.{fields} the b
icurve::copy(b, a);
```

COPYPP_FIELDS_INTRUSIVE:

defination the class

```c++
class AA {
private:
    int id;
    std::string name;
    bool sex;

public:
    AA() = default;
    AA(int id, std::string name, bool sex) : id(id), name(name), sex(sex) {}
public:
    COPYPP_FIELDS_INTRUSIVE(AA, id, name, sex)
};
class BB {
private:
    int id;
    std::string name;
    bool sex;

public:
    BB() = default;
    BB(int id, std::string name, bool sex) : id(id), name(name), sex(sex) {}
public:
    COPYPP_FIELDS_INTRUSIVE(BB, id, name, sex)
};
```

```c++
AA a(10, "curve", true);
BB b;
icurve::copy(b, a);
```

### json string

copypp support copy between json's string and struct, this copy depency [nlohmann-json](https://github.com/nlohmann/json) library, so you need

1. install the nlohmann-json lib
2. add `#include <nlohmann-json>` before the copypp header `#include <icurve/copypp.hh>` file
3. use COPYPP_FIELDS_INTRUSIVE defination method

```c++
#include <nlohmann/json.hpp>
#include "copypp_only.h"

void func() {
    BB b;
    std::string s = R"({"id":5,"name":"i-curve", "age": 25})";
    icurve::copy(b, s); // copy from string to struct
    icurve::copy(s, b); // copy from struct to string
}
```

### array copy

c style array, you need to delivery the array message

```c++
AA a[3];
BB b[2] = {BB(1, "first", true), BB(2, "second", false)};
icurve::copy<AA, 3, BB, 2>(a, b);
```

c++ style array

```c++
std::array<AA,3> a;
std::array<BB, 2> b = {BB(1, "first", true), BB(2, "second", false)};
icurve::copy(a, b);
```

### stl support

copypp support stl copy, condition:

> 1. the source has forward end iterator(begin, end)
> 2. the destiontion has forward iterator(begin, and)
> 3. if the destination has back_insert_iterator, copypp will copy the all source item. Otherwise, it only copy the minimum length between source and destination

copypp can copy it, even in a different stl type.

```c++
AA a[3];
BB b[2] = {BB(1, "first", true), BB(2, "second", false)};
std::span<AA> aa(a);
std::span<BB> bb(b);
icurve::copy(aa, bb);
```

If it's vector, you can directly use it.

```c++
vector<AA> a;
vector<BB> b = {BB(1, "first", true), BB(2, "second", false)};
icurve::copy(a, b);
```

different stl type

if the destionation can append item, it will clear destionation and append new item.

```c++
std::vector<AA> a = {AA(1, "first", true), AA(2, "second", false)};
std::list<BB> b; // copy all items
icurve::copy(b, a);
```

```c++
std::vector<AA> a = {AA(1, "first", true), AA(2, "second", false)};
std::array<BB, 1> b;
std::array<BB, 3> c;
icurve::copy(b, a); // will copy 1 item(min(a.size(), b.size())
icurve::copy(c, a); // will copy 2 items(min(a.size(), c.size()))
```

## Integration

---

### copy the single header file

copypp_only.hh is the single required file in include/icurve or [released here](https://raw.githubusercontent.com/i-curve/copypp/master/include/icurve/copypp_only.hh). You need to copy to your include directories. then use it by

```c++
#include <copypp_only.hh>

using copy = icurve::copy;
```

### cmake

clone the project and build.

```bash
git clone https://github.com/i-curve/copypp.git
cd copypp && mkdir build && cd build
# build and shut the test.if you open the test, you must install the fmt package.
cmake -DCOPYPP_TEST=OFF .
make
```

install

```bash
make install
```

### vcpkg

if you use the vcpkg, you can install it by

```
vcpkg install copypp
```

### conan

conanfile.txt

```txt
[requires]
copypp/[version]
```

## License

---

{copypp} is distributed under the [MIT License](LICENSE).
