#pragma once
#if !defined(MTFINDER_FILE_VIEW_HPP)
#define MTFINDER_FILE_VIEW_HPP

#include "types.hpp"
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/utility/string_view.hpp>

namespace mtfinder {

    namespace ipc = boost::interprocess;

    class file_view final {
    public:
        explicit file_view(const string& name);
        string_view get() const;
        size_t get_page_size() const;

        file_view(const file_view&) = delete;
        file_view& operator=(const file_view&) = delete;
    private:
        ipc::file_mapping fm;
        ipc::mapped_region region;
    };

}

#endif //!defined(MTFINDER_FILE_VIEW_HPP)