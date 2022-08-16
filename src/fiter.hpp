#pragma once
#if !defined(MTFINDER_FITER_HPP)
#define MTFINDER_FITER_HPP

#include <string>
#include <boost/regex.hpp>
#include <boost/utility/string_view.hpp>

namespace mtfinder {

    class fiter final {
    public:
        fiter(const boost::string_view& range, const std::string& regex);

        operator bool() const;
        size_t line(size_t base = 1) const;
        size_t offset(size_t base = 1) const;
        boost::string_view operator*() const;
        fiter& operator++();
        fiter operator++(int);

        fiter(const fiter&) = default;
        fiter& operator=(const fiter&) = default;
        fiter(fiter&&) = default;
        fiter& operator=(fiter&&) = default;
    private:
        bool next();

    private:
        const boost::string_view range;
        const boost::regex re;
        const char* current_line_begin;
        boost::string_view founded;
        size_t line_no;
    };
    
}

#endif //!defined(MTFINDER_FITER_HPP)
