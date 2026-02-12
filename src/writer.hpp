#pragma once
#include "contact.hpp"
#include <string>
#include <unordered_map>
#include <vector>

void write_buckets_one_file( const std::string &out_path,
    const std::unordered_map<char, std::vector<Contact>> &buckets 
    //этот параметр словарь где ключ символ, а значение вектор контактов начинающихся на этот символ
);
