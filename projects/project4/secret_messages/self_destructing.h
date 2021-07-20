#ifndef SELF_DESTRUCTING_H
#define SELF_DESTRUCTING_H

#include <ios>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class SelfDestructingMessage {
 private:
  std::vector<std::string> messages_ = {};
  long number_of_allowed_views_ = 0;
  std::vector<std::pair<string, long>> msg_and_views_ = {};

 public:
  // constructors
  SelfDestructingMessage(std::vector<std::string>, long);
  SelfDestructingMessage() = default;
  SelfDestructingMessage(SelfDestructingMessage&);  // copy constructor

  // members
  int size();
  std::vector<std::string> get_redacted();
  long number_of_views_remaining(int);
  void add_array_of_lines(string[], long);

  // overloaded operator methods
  const std::string& operator[](size_t);
  SelfDestructingMessage& operator=(SelfDestructingMessage&);

  // friends
  friend std::ostream& operator<<(std::ostream&, const SelfDestructingMessage&);
  friend std::istream& operator>>(std::istream&, SelfDestructingMessage&);
};

#endif
