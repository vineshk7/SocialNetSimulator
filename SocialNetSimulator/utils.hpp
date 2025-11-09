#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

/**
 * @brief Normalizes a string to lowercase.
 * @param s The input string.
 * @return The lowercase version of the string.
 */
inline string normalize(const string& s) {
    string out = s;
    transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return tolower(c); });
    return out;
}

/**
 * @brief Trims whitespace and quotes from the beginning and end of a string.
 * @param str The string to trim.
 * @return The trimmed string.
 */
inline string trim(const string& str) {
    const string whitespace = " \t\n\r\f\v"; 
    size_t first = str.find_first_not_of(whitespace);
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, (last - first + 1));
}

#endif 
