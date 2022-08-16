#include <gtest/gtest.h>
#include "fiter.hpp"
#include <string>
#include "utils.hpp"

using namespace mtfinder;

TEST(fiter_tests, simple_test) {
    const auto src = "this is test\njust for _test\n?test";
    const auto re = ".test";
    fiter it{src, re};
    ASSERT_TRUE(it);
    ASSERT_EQ(*it, " test");
    ASSERT_EQ(it.line(), 1);
    ASSERT_EQ(it.offset(), 8);
    ++it;
    ASSERT_TRUE(it);
    ASSERT_EQ(*it, "_test");
    ASSERT_EQ(it.line(), 2);
    ASSERT_EQ(it.offset(), 10);
    ++it;
    ASSERT_TRUE(it);
    ASSERT_EQ(*it, "?test");
    ASSERT_EQ(it.line(), 3);
    ASSERT_EQ(it.offset(), 1);

    ++it;
    ASSERT_FALSE(it);
}
