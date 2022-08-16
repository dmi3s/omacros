#pragma once
#if !defined(MTFINDER_UTILS_HPP)
#define MTFINDER_UTILS_HPP

#include "types.hpp"

namespace mtfinder {
    string build_regex_string(const std::string& user_mask);

    inline string_view make_string_view(const char* b, const char* e) {
        return {b, static_cast<size_t>(std::distance(b, e))};
    }

    fs::path absolutize(const fs::path& p);
}

#endif //!defined(MTFINDER_UTILS_HPP)
