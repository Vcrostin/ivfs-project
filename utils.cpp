//
// Created by brostin on 09.06.22.
//

#include "utils.h"

std::vector<std::string_view> StringSplit(std::string_view str, char delim) {
    std::vector<std::string_view> splitted_string;
    for (auto begin_it = str.begin(); begin_it != str.end();) {

        if (*begin_it == delim) {
            begin_it++;
            continue;
        }
        auto end_it = begin_it + 1;
        while (end_it != str.end() && *end_it != delim) {
            end_it++;
        }
        // c++ 20 :
        // splitted_string.push_back({str.begin(), str.end()});

        // c++ 17
        auto str_ref = std::string_view(str);
        str_ref.remove_prefix(begin_it - str.begin());
        str_ref.remove_suffix(str.end() - end_it);
        splitted_string.push_back({str_ref});
        begin_it = end_it;
    }
    return splitted_string;
}
