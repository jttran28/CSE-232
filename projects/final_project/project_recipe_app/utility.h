#pragma once

#include <string>
using std::string;
#include <sstream>
using std::istringstream;
using std::ostringstream;
#include <vector>
using std::vector;
#include <algorithm>
#include <iostream>
#include <iterator>
using std::ostream;

class Fraction {
 private:
  int dvdnd_ = 0;
  int dvsr_ = 1;
  int whole_num_ = dvdnd_ / dvsr_;
  string type_frac_;

 public:
  // constructors
  Fraction() = default;
  Fraction(const string &);
  Fraction(const int &, const int &);
  Fraction(const int &num) {
    whole_num_ = num;
    type_frac_ = "whole";
  }
  // accessors
  int whole() const { return whole_num_; }

  // member
  Fraction to_improper();
  void simplify();
  Fraction multiply(const int &);
  Fraction divide(const int &);

  // friend
  friend Fraction operator+(const Fraction &, const Fraction &);
  friend Fraction operator/(Fraction &, Fraction &);
  friend ostream &operator<<(ostream &out, Fraction &f) {
    f.simplify();
    if (f.type_frac_ == "mixed") {
      out << f.whole_num_ << '-' << (f.dvdnd_ % f.dvsr_) << '/' << f.dvsr_;
    } else if (f.type_frac_ == "normal") {
      out << f.dvdnd_ << "/" << f.dvsr_;
    } else {
      out << f.whole_num_;
    }
    return out;
  }
};

Fraction::Fraction(const string &s) {
  istringstream iss(s);
  char ch;
  if ((s.find('-') != string::npos) || (s.length() == 1)) {
    iss >> whole_num_;
    iss.get(ch);
  }
  iss >> dvdnd_;
  iss.get(ch);
  iss >> dvsr_;
  if (s.length() == 1) {
    type_frac_ = "whole";
  } else if (dvdnd_ % dvsr_ == 0) {
    type_frac_ = "whole";
    whole_num_ += dvdnd_ / dvsr_;
  } else if (s.find('-') != string::npos) {
    type_frac_ = "mixed";
    whole_num_ += dvdnd_ / dvsr_;
  } else if (((dvdnd_ % dvsr_) != 0) && (dvdnd_ > dvsr_)) {
    type_frac_ = "mixed";
    whole_num_ = dvdnd_ / dvsr_;
  } else {
    type_frac_ = "normal";
  }
}

Fraction::Fraction(const int &num, const int &denom) {
  dvdnd_ = num;
  dvsr_ = denom;
  if (((dvdnd_ % dvsr_) == 0) || (dvdnd_ == dvsr_)) {
    type_frac_ = "whole";
    whole_num_ = dvdnd_ / dvsr_;
  } else if (dvdnd_ > dvsr_) {
    type_frac_ = "mixed";
    whole_num_ = num / denom;
  } else {
    type_frac_ = "normal";
  }
}

Fraction Fraction::to_improper() {  // assuming its mixed
  int n = (whole_num_ * dvsr_) + (dvdnd_ % dvsr_);
  Fraction f(n, dvsr_);
  f.type_frac_ = "normal";
  return f;
}

Fraction operator+(const Fraction &f1,
                   const Fraction &f2) {  // assuming both are in improper form;
  int n, d, n1, n2;
  if (f1.dvsr_ != f2.dvsr_) {
    if ((f1.dvsr_ % f2.dvsr_ != 0) || (f2.dvsr_ % f1.dvsr_ != 0)) {
      d = f1.dvsr_ * f2.dvsr_;
      n1 = f1.dvdnd_ * f2.dvsr_;
      n2 = f2.dvdnd_ * f1.dvsr_;
      n = n1 + n2;
      Fraction new_f(n, d);
      return new_f;
    } else if (f1.dvsr_ > f2.dvsr_) {
      d = (f1.dvsr_ / f2.dvsr_) * f2.dvsr_;
      n = d * f2.dvdnd_;
      Fraction new_f(n + f1.dvdnd_, d);
      return new_f;
    } else {
      d = (f2.dvsr_ / f1.dvsr_) * f2.dvsr_;
      n = d * f1.dvdnd_;
      Fraction new_f(n + f2.dvdnd_, d);
    }
  }
  Fraction new_f(f1.dvdnd_ + f2.dvdnd_, f2.dvsr_);
  return new_f;
}

Fraction operator/(Fraction &f1, Fraction &f2) {
  Fraction f1_i = f1.to_improper();
  Fraction f2_i = f2.to_improper();
  Fraction f(f1_i.dvdnd_ * f2_i.dvsr_, f1_i.dvsr_ * f2_i.dvdnd_);
  return f;
}

Fraction Fraction::multiply(const int &i) {
  if (type_frac_ == "mixed") {
    Fraction temp = this->to_improper();
    Fraction f(temp.dvdnd_ * i, temp.dvsr_);
    return f;
  } else if (type_frac_ == "whole") {
    if (((whole_num_ % i) != 0) && (whole_num_ > i)) {
      Fraction f(whole_num_ / i);
    }
    Fraction f(whole_num_, i);
    return f;
  } else {
    Fraction f(i * dvdnd_, dvsr_);
    return f;
  }
}

Fraction Fraction::divide(const int &i) {
  if (type_frac_ == "mixed") {
    Fraction temp = this->to_improper();
    Fraction f(temp.dvdnd_, temp.dvsr_ * i);
    return f;
  } else if (type_frac_ == "whole") {
    if (((whole_num_ % i) == 0) && (whole_num_ > i)) {
      Fraction f(whole_num_ / i);
    }
    Fraction f(whole_num_, i);
    return f;
  } else {
    Fraction f(dvdnd_, dvsr_ * i);
    return f;
  }
}

void Fraction::simplify() {
  int gcd = std::__gcd(dvdnd_, dvsr_);
  if (gcd != 0) {
    dvdnd_ /= gcd;
    dvsr_ /= gcd;
  }
}

struct Ingredient {
  string unit;
  string name;
  Fraction value;
  // constructors
  Ingredient() = default;
  Ingredient(string s) {
    istringstream iss(s);
    string value_str;
    char ch;
    iss >> value_str;
    Fraction rvalue(value_str);
    value = rvalue;
    iss >> unit;
    iss.get(ch);
    getline(iss, name);
  }
};

void RemoveWhitespace(string &s) {
  /*
  the following source helped me write this function to remove leading and
  trailing whitespace:
  https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
  */
  auto it1 = std::find_if(s.begin(), s.end(),
                          [](auto &c) { return (isspace(c) == false); });
  s.erase(s.begin(), it1);
  auto it2 = std::find_if(s.rbegin(), s.rend(),
                          [](auto &c) { return (isspace(c) == false); });
  s.erase(it2.base(), s.end());
}