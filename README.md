# COPYPP

support field copy in different c++ struct.

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [COPYPP](#copypp)
  - [Required](#required)
  - [Usage](#usage)
    - [struct](#struct)
    - [COPY JSON string](#copy-json-string)
    - [array copy](#array-copy)
  - [Integration](#integration)
    - [copy the single header file](#copy-the-single-header-file)
    - [cmake](#cmake)
    - [vcpkg](#vcpkg)
  - [License](#license)

<!-- /code_chunk_output -->

## Required

c++14 (**recommend c++20**)

## Usage

- COPYPP_FIELDS_NON_INTRUSIVE(destination, source, field1, field2, ...) is to be defined inside the namespace of the class/struct to create code for.
- COPYPP_FIELDS_INTRUSIVE(field1, field2, field3, ...) is to be defined outside the namespace of class/struct to create code for. This macro can also access private members.
- copy between json string and struct
- support array copy

include the header file

```c++
#include <icurve/copypp.hh>
```

### struct

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

### COPY JSON string

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

c++ array

```c++
std::array<AA,3> a;
std::array<BB, 2> b = {BB(1, "first", true), BB(2, "second", false)};
icurve::copy(a, b);
```

c++20 span
note: the minimum c++ standard is c++20

```c++
AA a[3];
BB b[2] = {BB(1, "first", true), BB(2, "second", false)};
icurve::copy(std::span<AA>(a), std::span<BB>(b));
```

If it's vector, you can directly use it.

```c++
vector<AA> a;
vector<BB> b = {BB(1, "first", true), BB(2, "second", false)};
icurve::copy(a, b);
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

## License

---

{copypp} is distributed under the [MIT License](LICENSE).
