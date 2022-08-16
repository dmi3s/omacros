#pragma once
#if !defined(MTFINDER_FITER_HPP)
#define MTFINDER_FITER_HPP

#include "types.hpp"

namespace mtfinder {

    struct fiter_data final {
        string_view content = {};
        ptrdiff_t line= 0, offset= 0;
    };

    bool operator==(const fiter_data& fb1, const fiter_data& fb2);

    class fiter_eol final {
    public:
        fiter_eol();
        fiter_eol(const string_view& range, const std::string& regex);

        operator bool() const;
        fiter_data operator*() const;
        fiter_eol& operator++();
        string_view::const_iterator get_last_end() const;

    private:
        bool next();

    private:
        const string_view range;
        const regex re;
        fiter_data founded;

        friend bool operator==(const fiter_eol& it1, const fiter_eol& it2);
    };

    bool operator==(const fiter_eol& it1, const fiter_eol& it2);

    class fiter final {
    public:
        fiter();
        fiter(const string_view& range, const std::string& regex);

        operator bool() const;
        fiter_data operator*() const;
        fiter& operator++();
        string_view::const_iterator get_last_end() const;

    private:
        bool next();

    private:
        fiter_eol impl;

        friend bool operator==(const fiter& it1, const fiter& it2);
    };

    bool operator==(const fiter_eol& it1, const fiter_eol& it2);
}

#endif //!defined(MTFINDER_FITER_HPP)
