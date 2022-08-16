#include "file_view.hpp"
#include "utils.hpp"
#include "fiter.hpp"
#include <iostream>
#include <iomanip>
#include <optional>
#include <deque>
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

    void run(boost::string_view content, const string& re) {
        fiter it{content, re};
        std::deque<fiter_data> results;
        while (it) {
            results.push_back(*it);
            ++it;
        }
        std::cout << results.size() << '\n';
        for (const auto& r : results) {
            std::cout << r.line + 1 << ' ' << r.offset + 1 << ' '
                      << r.content << '\n';
        }
    }

}


int main(int argc, const char* argv[]) {

    using namespace mtfinder;

    if (auto opts = get_options(argc, argv)) {
        std::cout << opts->file_name << "\t" << opts->mask << "\n";
        try {
            file_view fw{absolutize(opts->file_name).string()};
            std::cout << "Page size: " << fw.get_page_size() << '\n';
            const auto re = build_regex_string(opts->mask);
            std::cout << "regex: \'" << re << "\'\n";
            run(fw.get(), re);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    } else
        return 1;

    return 0;    
}
