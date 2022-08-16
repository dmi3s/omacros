#pragma once
#if !defined(MTFINDER_FITER_HPP)
#define MTFINDER_FITER_HPP

#include <string>
#include <boost/regex.hpp>
#include <boost/utility/string_view.hpp>

namespace mtfinder {

    struct fiter_base final {
        boost::string_view content = {};
        ptrdiff_t line= 0, offset= 0;
    };

    bool operator==(const fiter_base& fb1, const fiter_base& fb2);

    class fiter final {
    public:
        fiter();
        fiter(const boost::string_view& range, const std::string& regex);

        operator bool() const;
        fiter_base operator*() const;
        fiter& operator++();
        // fiter operator++(int);
        boost::string_view::const_iterator get_last_end() const;

        fiter(const fiter&) = default;
        fiter& operator=(const fiter&) = default;
        fiter(fiter&&) = default;
        fiter& operator=(fiter&&) = default;
    private:
        bool next();

    private:
        const boost::string_view range;
        const boost::regex re;
        fiter_base founded;

         friend bool operator==(const fiter& it1, const fiter& it2);
    };

    bool operator==(const fiter& it1, const fiter& it2);
}

#endif //!defined(MTFINDER_FITER_HPP)
