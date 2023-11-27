/* c++
 * @Author: i-curve
 * @Date: 2023-11-27 23:40:11
 * @Last Modified by: i-curve
 * @Name:
 */
#include "icurve/copypp.hh"
#include <gtest/gtest.h>
#include "A.h"
#include "B.h"

COPYPP_FIELDS_NON_INTRUSIVE(B, A, id, name, sex)

TEST(COPYPP_FIELDS_NON_INTRUSIVE, one) {
    A a(3, "Incididunt et veniam non aute nulla.", true);
    B b;
    EXPECT_TRUE(a.id == 3);
    EXPECT_TRUE(a.name == "Incididunt et veniam non aute nulla.");
    EXPECT_TRUE(a.sex == true);
    EXPECT_TRUE(b.id == 0);
    EXPECT_TRUE(b.name == "");
    EXPECT_TRUE(b.sex == false);
    icurve::copy(b, a);
    EXPECT_TRUE(b.id == a.id);
    EXPECT_TRUE(b.name == a.name);
    EXPECT_TRUE(b.sex == a.sex);
}

TEST(COPYPP_FIELDS_INTRUSIVE, one) {
    AA a(15, "Velit cupidatat deserunt dolor non ullamco.", false);
    BB b;
    EXPECT_TRUE(a.getId() == 15);
    EXPECT_FALSE(a.getName() == "");
    EXPECT_TRUE(a.getSex() == false);
    icurve::copy(b, a);
    EXPECT_TRUE(b.getId() == a.getId());
    EXPECT_TRUE(b.getName() == a.getName());
    EXPECT_TRUE(b.getSex() == a.getSex());
    EXPECT_EQ(b.getId(), a.getId());
    EXPECT_EQ(b.getName(), a.getName());
}