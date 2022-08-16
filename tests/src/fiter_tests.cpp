#include <gtest/gtest.h>
#include "fiter.hpp"
#include <string>
#include "utils.hpp"

using namespace mtfinder;
using namespace std::literals;

TEST(fiter_tests, default_constructable_and_comparable) {
    fiter e1, e2;
    ASSERT_EQ(e1, e2);
    const auto src = "\n??e!";
    const auto re = "..e!"s;
    fiter it{src, re};
    ASSERT_TRUE(it);
    // ASSERT_EQ((*it).content, "??e!");
    ++it;
    ASSERT_FALSE(it);
    ASSERT_EQ(it, e1);
    ASSERT_EQ(it, e2);
}

TEST(fiter_tests, last_position) {
    const char src[] = "\n??Oh, my God!\nee";
    const char re[] = "Oh, ..";
    fiter it{src, re};
    ASSERT_TRUE(it);
    ++it;
    ASSERT_FALSE(it);
    auto last_n = &*std::find(std::rbegin(src), std::rend(src), '\n') + 1;
    ASSERT_EQ(it.get_last_end(), last_n);
}

TEST(fiter_tests, simple_test) {
    const auto src = "this is test\njust for _test\n?test";
    const auto re = ".test";
    fiter it{src, re};
    ASSERT_TRUE(it);
    auto founded = *it;
    ASSERT_EQ(founded.content, " test");
    ASSERT_EQ(founded.line, 0);
    ASSERT_EQ(founded.offset, 7);
    ++it;
    ASSERT_TRUE(it);
    founded = *it;
    ASSERT_EQ(founded.content, "_test");
    ASSERT_EQ(founded.line, 1);
    ASSERT_EQ(founded.offset, 9);
    ++it;
    ASSERT_TRUE(it);
    founded = *it;
    ASSERT_EQ(founded.content, "?test");
    ASSERT_EQ(founded.line, 2);
    ASSERT_EQ(founded.offset, 0);

    ++it;
    ASSERT_FALSE(it);
}
