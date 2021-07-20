#pragma once

#include <iostream>
using std::endl;
using std::ostream;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <algorithm>
#include <iterator>

#include "recipe.h"
#include "utility.h"

class RecipeApp {
 private:
  vector<Recipe> recipes_;
  vector<Ingredient> pantry_;

 public:
  RecipeApp() = default;
  void AddRecipe(const Recipe &);
  Recipe UseUpIngredient(const string &);
  void AddIngredientToPantry(const string &);
  friend ostream &operator<<(ostream &, const RecipeApp &);
};

void RecipeApp::AddRecipe(const Recipe &r) {
  recipes_.push_back(r);
  std::sort(recipes_.begin(), recipes_.end(),
            [](Recipe p1, Recipe p2) { return p1.name() < p2.name(); });
}
void RecipeApp::AddIngredientToPantry(const string &s) {
  Ingredient ingrdt(s);
  pantry_.push_back(s);
  std::sort(pantry_.begin(), pantry_.end(),
            [](const Ingredient &p1, const Ingredient &p2) {
              return p1.name < p2.name;
            });
}

Recipe RecipeApp::UseUpIngredient(const string &s) {
  Ingredient new_ingrdt(s);    // convert string into ingredient
  Recipe rcp;                  // recipe for output
  bool found = false;          // default
  Ingredient ingrdt_this;      // specific ingredient trying to use up
  for (Recipe r : recipes_) {  // iterating thru recipes
    for (size_t i = 0; i < r.ingrdt().size();
         ++i) {  // iterating thru ingredients for each recipe
      Ingredient ingrdt = r.ingrdt().at(i);
      if (ingrdt.name == new_ingrdt.name) {  // if found, hault for loops
        ingrdt_this = ingrdt;
        found = true;
        rcp = r;
        break;
      }
    }
    if (found == true) {
      break;
    }
  }
  if (found != true) {
    throw std::invalid_argument("Invalid argument");
  }
  Fraction one_srvg = ingrdt_this.value.divide(rcp.srvgs());  // one serving
  Fraction srvg =
      new_ingrdt.value / one_srvg;  // # of servings to use up ingredient
  rcp.ChangeServings(srvg.whole());
  return rcp;
}

ostream &operator<<(ostream &out, const RecipeApp &r) {
  out << "Recipes in the app (ordered by name):\n";
  std::for_each(r.recipes_.begin(), r.recipes_.end(),
                [&out](Recipe rcp) { out << rcp; });
  out << "Ingredients in pantry (ordered by name):\n";
  std::for_each(r.pantry_.begin(), r.pantry_.end(), [&out](Ingredient ingrdt) {
    out << ingrdt.value << " " << ingrdt.unit << " " << ingrdt.name << endl;
  });
  return out;
}