#pragma once
#if !defined(MTFINDER_TYPES_HPP)
#define MTFINDER_TYPES_HPP

#include <string>
#include <ranges>
#include <boost/utility/string_view.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace mtfinder {
    using std::string;
    using std::cbegin;
    using std::cend;
    using std::begin;
    using std::end;
    using std::distance;

    using boost::string_view;
    using boost::regex;
    namespace fs = boost::filesystem;
}

#endif //!defined(MTFINDER_TYPES_HPP)