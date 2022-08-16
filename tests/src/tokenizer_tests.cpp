#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>
#include <optional>
#include <string>
//#include <string_view>
#include <boost/regex.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/any.hpp>
//#include <boost/utility/string_ref.hpp>
#include <vector>
#include <array>
#include <algorithm>
#include "utils.hpp"

namespace mtfinder {

    class finder {
    public:
        struct iterator {
            const char* next;
        };

        finder(const char* cbegin, const char* cend, 
            boost::regex re);

    private:
        const char* cbegin;
        const char* cend;
        boost::regex re;
    };

}

using namespace mtfinder;
using boost::string_view;

void dump(const std::vector<string_view>& v) {
    std::cout << "founds: " << v.size() << '\n';
    for (const auto& sv: v)
        std::cout << " - " << sv << '\n';
}


TEST(regex_test, base) {
    // auto expression = boost::regex("(?:'\\n'|.test.)");
    // auto expression = boost::regex("\n|.test\\.");
    auto expression = boost::regex( "\n|" +
        mtfinder::build_regex_string("?test.?([A-Z]*\\)"));
    auto const test_str_view = string_view("this is test. ([A-Z]*\\)\nstring\r\nfor.test. regex\n");
    std::vector<string_view> result;
    

    string_view::const_iterator 
        begin = test_str_view.cbegin(),
        end = test_str_view.cend();

    boost::match_results<string_view::const_iterator> what;
    boost::match_flag_type flags = boost::regex_constants::match_not_dot_newline;
    while (regex_search(begin, end, what, expression, flags)) {
        result.push_back(make_string_view(what[0].first, what[0].second));
        // update search position: 
        begin = what[0].second;
        // update flags: 
//        flags |= boost::match_prev_avail;
//        flags |= boost::match_not_bob;
    }
    dump(result);
    ASSERT_TRUE(true);
}








