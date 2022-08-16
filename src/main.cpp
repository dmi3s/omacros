#include <iostream>
#include <iomanip>
#include <optional>
//#include <regex>
#include <string>
#include <string_view>
#include <boost/program_options.hpp>

namespace {
    using std::optional;
    using std::string;
    namespace po = boost::program_options;

    struct mtf_options {
        string file_name;
        string mask;
    };

    optional<mtf_options> get_options(int argc, const char* argv[]) {

        po::options_description desc("Invocation: <program> <filename> <mask>");

        desc.add_options()
        ("file_name", po::value<string>()->required(), "File name")
        ("mask", po::value<string>()->required(), "Mask to search")
        ;

        po::positional_options_description pos_desc;
        pos_desc.add("file_name", 1);
        pos_desc.add("mask", 1);
        po::variables_map vm;

        try {
            po::store(po::command_line_parser(argc, argv).
                        options(desc).
                        positional(pos_desc).run(), vm);
            po::notify(vm);        
        } catch(const po::error& e) {
            std::cerr << "ERROR: " << e.what() << '\n' << desc << std::endl;
            return {};
        }

        return optional<mtf_options>({ vm["file_name"].as<string>()
                                       ,vm["mask"].as<string>() });
    }
}


#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/system.hpp>
#include <boost/filesystem.hpp>


namespace ipc = boost::interprocess;
namespace fs = boost::filesystem;

namespace mtfinder {

    class file_view final {
    public:
        explicit file_view(const std::string& name);
        boost::string_view get() const;
        size_t get_page_size() const;

        file_view(const file_view&) = delete;
        file_view& operator=(const file_view&) = delete;
    private:
        boost::interprocess::file_mapping fm;
        boost::interprocess::mapped_region region;
    };

}

namespace mtfinder {

    file_view::file_view(const std::string& name) :
        fm(name.c_str(), boost::interprocess::read_only),
        region(fm, boost::interprocess::read_only)
    {}

    boost::string_view file_view::get() const {
        return {static_cast<const char*>(region.get_address()), region.get_size()};
    }

    size_t file_view::get_page_size() const {
        return region.get_page_size();
    }

    void run(boost::string_view content) {
        std::cout << content << "<EOF>\n";
    }

}



int main(int argc, const char* argv[]) {

    using namespace mtfinder;
    using namespace std;

    if (auto opts = get_options(argc, argv)) {
        std::cout << opts->file_name << "\t" << opts->mask << "\n";
        try {
            cout << fs::current_path() << endl;
            boost::system::error_code ec;
            auto abs_name = fs::absolute(opts->file_name,ec).string();
            cout << abs_name << endl;
            file_view fw{abs_name};
            run(fw.get());
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    } else
        return 1;

    return 0;    
}
