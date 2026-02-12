#pragma once
#include "contact.hpp"
#include <string>

bool parse_contact_line(const std::string& line, Contact& out);
char bucket_key_ascii_lastname(const Contact& c);
