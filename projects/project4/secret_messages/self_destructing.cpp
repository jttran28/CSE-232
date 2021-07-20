#include <string>
#include <vector>
using std::vector;
#include <ios>
#include <iostream>
using std::istream;
using std::ostream;
#include <string>
using std::string;
#include <algorithm>
#include <utility>
using std::make_pair;
using std::pair;
#include <iomanip>
#include <stdexcept>

#include "redact.h"
#include "self_destructing.h"

SelfDestructingMessage::SelfDestructingMessage(vector<string> v, long n) {
  messages_ = v;
  number_of_allowed_views_ = n;
  for (string &msg : messages_) {
    msg_and_views_.push_back(make_pair(msg, n));
  }
}

SelfDestructingMessage::SelfDestructingMessage(SelfDestructingMessage &sdm) {
  number_of_allowed_views_ = sdm.number_of_allowed_views_;
  messages_ = sdm.messages_;
  msg_and_views_ = sdm.msg_and_views_;
  for (auto &pair_msg_views : sdm.msg_and_views_) {
    pair_msg_views.second = 0;
  }
}

int SelfDestructingMessage::size() { return messages_.size(); }

vector<string> SelfDestructingMessage::get_redacted() {
  vector<string> redacted_msg;
  std::for_each(messages_.begin(), messages_.end(), [&redacted_msg](auto m) {
    redacted_msg.push_back(redact_alphabet_digits(m));
  });
  return redacted_msg;
}

long SelfDestructingMessage::number_of_views_remaining(int i) {
  return msg_and_views_[i].second;
}

const string &SelfDestructingMessage::operator[](size_t i) {
  if (i > messages_.size() - 1) {
    throw std::out_of_range("Out of range");
  } else if (msg_and_views_[i].second == 0) {
    throw std::invalid_argument("Invalid argument");
  }
  --msg_and_views_[i].second;
  return msg_and_views_[i].first;
}

ostream &operator<<(std::ostream &out, const SelfDestructingMessage &sdm) {
  for (auto &pair_msg_views : sdm.msg_and_views_) {
    /*
    how i formatted the numbers for there to be leading zeros:
    https://stackoverflow.com/questions/1714515/how-can-i-pad-an-int-with-leading-zeros-when-using-cout-operator/14011098
    */
    out << std::setfill('0') << std::setw(2) << pair_msg_views.second;
    out << ": " << redact_alphabet_digits(pair_msg_views.first) << std::endl;
  }
  return out;
}

SelfDestructingMessage &SelfDestructingMessage::operator=(
    SelfDestructingMessage &sdm) {
  number_of_allowed_views_ = sdm.number_of_allowed_views_;
  messages_ = sdm.messages_;
  msg_and_views_ = sdm.msg_and_views_;
  for (auto &pair_msg_views : sdm.msg_and_views_) {
    pair_msg_views.second = 0;
  }
  return *this;
}

istream &operator>>(std::istream &is, SelfDestructingMessage &sdm) {
  string msg;
  getline(is, msg);
  sdm.messages_.push_back(msg);
  sdm.msg_and_views_.push_back(make_pair(msg, sdm.number_of_allowed_views_));
  return is;
}

void SelfDestructingMessage::add_array_of_lines(string str_arr[], long n) {
  size_t size = n;
  for (size_t i = 0; i < size; ++i) {
    messages_.push_back(str_arr[i]);
    msg_and_views_.push_back(make_pair(str_arr[i], number_of_allowed_views_));
  }
}