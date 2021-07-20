#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
#include <iterator>

#include "redact.h"

string redact_all_chars(const string &s) {
  string new_s(s.length(), '#');
  return new_s;
}

string redact_alphabet_digits(const string &s) {
  string new_s(s.length(), ' ');
  auto lambdaReplace = [](auto &c) { return (isdigit(c) || isalpha(c)); };
  std::replace_copy_if(s.begin(), s.end(), new_s.begin(), lambdaReplace, '#');
  return new_s;
}

string redact_words(const string &s, const vector<string> &v) {
  string new_s(s.length(), ' ');
  std::copy(s.begin(), s.end(), new_s.begin());
  for (auto word : v) {
    /*
    following source helped me figure how to find all instances of a word in
    string and replace them:
    https://stackoverflow.com/questions/22433706/c-function-to-replace-in-a-string-all-occurrences-of-a-given-substring
    */
    for (auto pos = new_s.find(word); pos != string::npos;
         pos = new_s.find(word)) {
      string redact(word.length(), '#');
      new_s.replace(pos, word.length(), redact);
    }
  }
  return new_s;
}