#include "parser.hpp"
#include <cctype>
#include <vector>

static std::vector<std::string> split_by_semicolon(const std::string& s) {
    std::vector<std::string> parts;
    std::string cur;
    for (char ch : s) {
        if (ch == ';') {
            parts.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(ch);
        }
    }
    parts.push_back(cur);
    return parts;
}

bool parse_contact_line(const std::string &line, Contact &out) {
    auto parts = split_by_semicolon(line);
    if (parts.size() != 4) return false;

    out.last   = parts[0];
    out.first  = parts[1];
    out.middle = parts[2];
    out.phone  = parts[3];
    return true;
}

//эта функция возвращает символ ключ для bucket первая буква фамилии.
char bucket_key_ascii_lastname(const Contact& c){
    if (c.last.empty()) return '#';
    unsigned char ch = (unsigned char)c.last[0];
    ch = (unsigned char)std::toupper(ch);
    if (ch >= 'A' && ch <= 'Z') return (char)ch;
    if (ch >= '0' && ch <= '9') return (char)ch;
    return '#';
}
