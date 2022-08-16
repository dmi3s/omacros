#include "utils.hpp"
#include <gtest/gtest.h>
#include <utility>

using std::pair;
using std::string;
using namespace std::string_literals;

using namespace mtfinder;

TEST(utils_tests, build_regex_string) {

#pragma GCC diagnostic push
// Doesn't work for trigraphs ...
#pragma GCC diagnostic ignored "-Wtrigraphs"

    const pair<string, string> tests [] = {
        {""s,  ""s},
        {"?"s, "."s},
        {"??? (test) ???"s, "... \\(test\\) ..."s},
        {"?.()[]{}|^$-*\\?"s, ".\\.\\(\\)\\[\\]\\{\\}\\|\\^\\$\\-\\*\\\\."s},
    };

#pragma GCC diagnostic pop

    for (const auto& p : tests) {
        const auto& user_mask = p.first;
        const auto& awaiting_regex = p.second;
        const auto result = build_regex_string(user_mask);
        ASSERT_EQ(awaiting_regex, result);
    }
}

