#pragma once
#if !defined(MTFINDER_UTILS_HPP)
#define MTFINDER_UTILS_HPP

#include <string>
#include <boost/utility/string_view.hpp>

namespace mtfinder {
    std::string build_regex_string(const std::string& user_mask);

    inline boost::string_view make_string_view(const char* b, const char* e) {
        return {b, static_cast<size_t>(std::distance(b, e))};
    }
}

#endif //!defined(MTFINDER_UTILS_HPP)