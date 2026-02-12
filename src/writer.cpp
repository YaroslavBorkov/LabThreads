#include "writer.hpp"
#include <fstream>
#include <algorithm>

void write_buckets_one_file( const std::string &out_path, const std::unordered_map<char, std::vector<Contact>> &buckets) 
{
    std::ofstream out(out_path);
    std::vector<char> keys;
    keys.reserve(buckets.size());
    for (auto& kv : buckets) keys.push_back(kv.first);
    std::sort(keys.begin(), keys.end());

    for (char k : keys) {
        out << "[" << k << "]\n";
        const auto &vec = buckets.at(k);
        for (const auto &c : vec) out << c.last << ";" << c.first << ";" << c.middle << ";" << c.phone << "\n";
        out << "\n";
    }
}
