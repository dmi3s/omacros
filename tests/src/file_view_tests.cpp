#include "file_view.hpp"
#include <gtest/gtest.h>
#include "utils.hpp"

using namespace mtfinder;
using namespace std::string_literals;

TEST(file_view_tests, file_veiw) {
    const string fname = "tests/data/example.txt"s;
    const fs::path abs_fname{absolutize(fname)};
    const size_t file_sz = fs::file_size(abs_fname);
    file_view fw{abs_fname.string()};
    const string_view content = fw.get();
    const size_t content_sz = content.length();
    ASSERT_EQ(file_sz, content_sz);
}
