#ifndef REDACT_H
#define REDACT_H

#include <string>
#include <vector>

std::string redact_all_chars(const std::string &);
std::string redact_alphabet_digits(const std::string &);
std::string redact_words(const std::string &, const std::vector<std::string> &);

#endif
