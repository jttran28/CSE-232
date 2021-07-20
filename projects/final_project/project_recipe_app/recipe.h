#pragma once

#include <string>
using std::string;
#include <iostream>
using std::endl;
using std::ostream;
#include <sstream>
#include <stdexcept>
using std::istringstream;
using std::ostringstream;
#include <vector>
using std::vector;
#include <algorithm>

#include "utility.h"

class Recipe {
 private:
  string name_;
  int srvgs_;
  vector<Ingredient> ingredients_;
  vector<string> instructions_;

 public:
  // constructors
  Recipe() = default;
  Recipe(const string &s, const int &i) {
    name_ = s;
    srvgs_ = i;
  }

  // accesors
  string name() const { return name_; }
  int srvgs() const { return srvgs_; }
  vector<Ingredient> ingrdt() const { return ingredients_; }

  // members
  void AddIngredient(const string &);
  void SetInstructions(const string &);
  string IngredientInOneServing(const string &);
  void ChangeServings(const int &);

  // friend
  friend ostream &operator<<(ostream &, const Recipe &);
};

void Recipe::AddIngredient(const string &s) {
  Ingredient ingrdt(s);
  RemoveWhitespace(ingrdt.name);
  ingredients_.push_back(ingrdt);
}

void Recipe::SetInstructions(const string &s) {
  istringstream iss(s);
  string line;
  while (getline(iss, line)) {
    if (line == "") {
      continue;
    }
    RemoveWhitespace(line);
    instructions_.push_back(line);
  }
}

string Recipe::IngredientInOneServing(const string &s) {
  string output;
  ostringstream oss;
  // finds the ingredient in the vector of ingredients
  auto it = std::find_if(
      ingredients_.begin(), ingredients_.end(),
      [&s](const Ingredient &ingrdt) { return (ingrdt.name == s); });
  if (it == ingredients_.end()) {
    throw std::invalid_argument("Invalid argument");
  }
  Ingredient ingrdt(*it);
  Fraction new_value;
  if (srvgs_ != 1) {
    new_value = (ingrdt.value).divide(srvgs_);
  } else {
    new_value = ingrdt.value;  // division by 1
  }
  oss << new_value << " " << ingrdt.unit << " " << ingrdt.name;
  return oss.str();
}

void Recipe::ChangeServings(const int &n) {
  for (Ingredient &ingrdt : ingredients_) {
    ingrdt.value = ingrdt.value.divide(srvgs_);
    ingrdt.value = ingrdt.value.multiply(n);
  }
  srvgs_ = n;
}

ostream &operator<<(ostream &out, const Recipe &r) {
  out << "Recipe for: " << r.name_ << endl;
  out << "Serves " << r.srvgs_;
  out << "\nIngredients:\n";
  std::for_each(
      r.ingredients_.begin(), r.ingredients_.end(), [&out](auto ingrdt) {
        out << ingrdt.value << " " << ingrdt.unit << " " << ingrdt.name << endl;
      });
  out << endl;
  out << "Instructions:\n";
  std::for_each(r.instructions_.begin(), r.instructions_.end(),
                [&out](const string &line) { out << line << endl; });
  out << endl;
  return out;
}