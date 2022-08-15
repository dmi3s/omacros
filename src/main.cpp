#include <optional>
#include <tuple>
#include <boost/program_options.hpp>

using std::optional;
using std::tuple;
using std::string;


optional<tuple<string>> process_po(int argc, const char*argv[]) {
    return {};
}

namespace po = boost::program_options;

int main(int argc, const char*argv[]) {
    po::options_description desc("General options");
    
  }
