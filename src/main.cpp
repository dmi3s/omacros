#include <iostream>
#include <iomanip>
#include <optional>
#include <string>
#include <string_view>
#include <boost/program_options.hpp>
#include <regex>

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

namespace bipc = boost::interprocess;



int main(int argc, const char* argv[]) {

    if (auto opts = get_options(argc, argv)) {
        std::cout << opts->file_name << "\t" << opts->mask << "\n";

        bipc::file_mapping fm(opts->file_name.c_str(), bipc::read_only);
        bipc::mapped_region region(fm, bipc::read_only);

        std::cout << "addr = 0x" << std::ios::hex << static_cast<const char*>(region.get_address()) 
                << std::ios::dec << "\nsz = " << region.get_size();
    } else
        return 1;

    return 0;    
}
