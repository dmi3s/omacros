#include "fiter.hpp"
#include "utils.hpp"
#include <assert.h>

namespace mtfinder {
    using namespace boost;

    fiter_eol::fiter_eol() {}

    fiter_eol::fiter_eol(const string_view& range, const string& regex) :
        range(range),
        re("\n|" + regex),
        founded{{cbegin(range), 0}, 0, 0}
    {
        next();
    }

    bool fiter_eol::next() {
        boost::match_results<string_view::const_iterator> what;
        boost::match_flag_type flags = boost::regex_constants::match_not_dot_newline;
        while (regex_search(cend(founded.content), cend(range), what, re, flags)) {
            founded.offset = distance(cend(founded.content), what[0].first);
            founded.content = { make_string_view(what[0].first, what[0].second) };
            if (founded.content == "\n")
                ++founded.line;
            return true;
        }
        founded.content = { cend(founded.content), 0 };
        return false;
    }

    fiter_eol::operator bool() const {
        return !founded.content.empty();
    }

    fiter_data fiter_eol::operator*() const {
        assert(*this);
        return founded;
    }

    string_view::const_iterator fiter_eol::get_last_end() const {
        return cend(founded.content);
    }

    fiter_eol& fiter_eol::operator++() {
        assert(*this);
        next();
        return *this;
    }

    // fiter fiter::operator++(int) {
    //     auto prev = *this;
    //     this->operator++();
    //     return prev;
    // }

    bool operator==(const fiter_data& fb1, const fiter_data& fb2) {
        return fb1.content.empty() && fb2.content.empty() ||
            cbegin(fb1.content) == cbegin(fb2.content) &&
            cend(fb1.content) == cend(fb2.content) &&
            fb1.line == fb2.line &&
            fb1.offset == fb2.offset;
    }


    bool operator==(const fiter_eol& it1, const fiter_eol& it2) {
        return !it1 && !it2 ||
            it1.range == it2.range && it1.founded == it2.founded;
    }

    bool operator==(const fiter& it1, const fiter& it2) {
        return it1.impl == it2.impl;
    }


    fiter::fiter() 
    {}

    fiter::fiter(const string_view& range, const std::string& regex) :
        impl(range, regex) 
    {
        if (impl.operator*().content == "\n")
            next();
    }

    fiter::operator bool() const {
        return impl.operator bool();
    }

    fiter_data fiter::operator*() const {
        return impl.operator*();
    }

    fiter& fiter::operator++() {
        assert(*this);
        next();
        return *this;
    }

    string_view::const_iterator fiter::get_last_end() const {
        return impl.get_last_end();
    }

    bool fiter::next() {
        do {
            ++impl;
        } while (impl && impl.operator*().content == "\n");

        return impl.operator bool();
    }

}
