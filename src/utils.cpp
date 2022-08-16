#include "utils.hpp"
#include <vector>

namespace mtfinder {
    using std::string;


    string build_regex_string(const string& user_mask) {
        const size_t max_regex_len = user_mask.length() * 2;
        std::vector<char> re;
        re.reserve(max_regex_len);

        for (const auto& ch: user_mask) {
            switch (ch) {
                case '?':
                    re.push_back('.');
                    break;
                case '.':
                case '(':
                case ')':
                case '[':
                case ']':
                case '{':
                case '}':
                case '|':
                case '^':
                case '$':
                case '-':
                case '*':
                case '\\':
                    re.push_back('\\');
                default:
                    re.push_back(ch);
            }
        }
        return {std::cbegin(re), std::cend(re)};
    }

}