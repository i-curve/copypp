# COPYPP

support field copy in different c++ struct.

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [COPYPP](#copypp)
  - [Required](#required)
  - [Usage](#usage)
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

include the header file

```c++
#include <icurve/copypp.hh>
```

COPYPP_FIELDS_NON_INTRUSIVE:

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
