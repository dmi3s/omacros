#include "file_view.hpp"

namespace mtfinder {

    file_view::file_view(const string& name) :
        fm(name.c_str(), boost::interprocess::read_only),
        region(fm, boost::interprocess::read_only)
    {}

    string_view file_view::get() const {
        return {static_cast<const char*>(region.get_address()), region.get_size()};
    }

    size_t file_view::get_page_size() const {
        return region.get_page_size();
    }

}