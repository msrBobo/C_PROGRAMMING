#include <iostream>
#include <string>
std::string my_cpp_journey_substring(const std::string& s1, int begin, int end) {
    return s1.substr(begin, end - begin + 1);
}