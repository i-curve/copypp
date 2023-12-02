/* c++
 * @Author: i-curve
 * @Date: 2023-12-02 09:29:13
 * @Last Modified by: i-curve
 * @Name:
 */

#include "icurve/copypp.hh"
#include <gtest/gtest.h>

class A {
public:
    int id;
    std::string name;
    bool sex;
};
class B {
public:
    int id;
    std::string name;
    bool sex;
};

COPYPP_FIELDS_NON_INTRUSIVE(B, A, id);

TEST(copypp_test4, one) {}