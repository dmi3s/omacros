#include "file_view.hpp"
#include "utils.hpp"
#include <iostream>
#include <iomanip>
#include <optional>
#include <boost/program_options.hpp>

namespace {
    using std::optional;
    using namespace mtfinder;
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


namespace mtfinder {

    void run(boost::string_view content) {
        std::cout << content << "<EOF>\n";
    }

}


int main(int argc, const char* argv[]) {

    using namespace mtfinder;

    if (auto opts = get_options(argc, argv)) {
        std::cout << opts->file_name << "\t" << opts->mask << "\n";
        try {
            file_view fw{absolutize(opts->file_name).string()};
            run(fw.get());
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    } else
        return 1;

    return 0;    
}
