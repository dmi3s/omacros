#include "fiter.hpp"
#include "utils.hpp"

namespace mtfinder {
    using std::string;
    using std::cbegin;
    using std::cend;
    using std::distance;

    using namespace boost;

    fiter::fiter(const boost::string_view& range, const string& regex) :
        range(range),
        re("\n|" + regex),
        current_line_begin(std::cbegin(range)),
        founded(cbegin(range), 0),
        line_no(0)
    {
        next();
    }

    bool fiter::next() {
        boost::match_results<string_view::const_iterator> what;
        boost::match_flag_type flags = boost::regex_constants::match_not_dot_newline;
        while (regex_search(cend(founded), cend(range), what, re, flags)) {
            founded = make_string_view(what[0].first, what[0].second);
            if (founded == "\n") {
                ++line_no;
                current_line_begin = cend(founded);
            }
            else
                return true;
        }
        founded = {cend(range), 0};
        return false;
    }

    fiter::operator bool() const {
        return !founded.empty();
    }

    size_t fiter::line(size_t base) const {
        return line_no + base;
    }

    size_t fiter::offset(size_t base) const {
        return static_cast<size_t>(distance(current_line_begin, cbegin(founded))) + base;
    }

    boost::string_view fiter::operator*() const {
        return founded;
    }

    fiter& fiter::operator++() {
        next();
        return *this;
    }

    fiter fiter::operator++(int) {
        auto prev = *this;
        this->operator++();
        return prev;
    }

}
