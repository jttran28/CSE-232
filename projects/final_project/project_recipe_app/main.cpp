#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "app.h"
#include "recipe.h"
#include "utility.h"

using std::cout; using std::endl;

int WhichLineDifferent(const std::string& expected, const std::string& result) {
  std::istringstream iss_expected(expected);
  std::istringstream iss_result(result);

  for (int i = 0;; ++i) {
    std::string line_expected;
    std::string line_result;
    std::getline(iss_expected, line_expected, '\n');
    std::getline(iss_result, line_result, '\n');
    if (!iss_expected.good() || !iss_result.good()) {
      if (iss_expected.good() || iss_result.good()) {
        std::cout << "One of the texts has less lines than the other."
                  << std::endl;
        if (iss_expected.good()) {
          std::cout << "Expected is longer" << std::endl;
          std::cout << "With this line: \"" << line_expected << "\""
                    << std::endl;
        } else {
          std::cout << "Result is longer" << std::endl;
          std::cout << "With this line: \"" << line_result << "\"" << std::endl;
        }
        return i;
      }
      break;
    }
    if (line_expected != line_result) {
      std::cout << "This line from expected: \"" << line_expected << "\""
                << std::endl;
      std::cout << "Doesn't match this line from result: \"" << line_result
                << "\"" << std::endl;
      return i;
    }
  }
  return -1;
}

// int main() { cout << "Hello World!" << endl; }

int main_recipe_app() {
  RecipeApp ra;
  Recipe simple_pop("Simple Popcorn", 1);
  simple_pop.AddIngredient("1/4 cup unpopped popcorn");
  simple_pop.AddIngredient("1/4 teaspoon vegetable oil");
  simple_pop.AddIngredient("1/4 teaspoon salt");
  simple_pop.SetInstructions(R"***(Pop it!)***");

  Recipe apples("An Apple", 3);
  apples.AddIngredient("1-5/6 unit apple");
  apples.SetInstructions(R"***(Grab it!)***");

  ra.AddRecipe(simple_pop);
  ra.AddRecipe(apples);
  ra.AddIngredientToPantry("2 cup unpopped popcorn");
  ra.AddIngredientToPantry("4-7/8 unit apple");
  cout << ra << endl;

  Recipe r = ra.UseUpIngredient("10 unit apple");
  cout << "Using up apples" << endl;
  cout << r;

  cout << ra;
  return 0;
}

int main_recipe() {
  std::cout << "Start" << std::endl;
  Recipe r("Microwave Popcorn", 3);
  r.AddIngredient("1/2 cup unpopped popcorn");
  r.AddIngredient("1 teaspoon vegetable oil");
  r.AddIngredient("1/2 teaspoon salt");
  r.SetInstructions(
      R"***(In a cup or small bowl, mix together the unpopped popcorn and oil. 
  Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt. 
    Fold the top of the bag over twice to seal in the ingredients. 

  Cook in the microwave at full power for 2 1/2 to 3 minutes, 
   or until you hear pauses of about 2 seconds between pops. 

  Carefully open the bag to avoid steam, and pour into a serving bowl. 
  From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/
  )***");

  std::cout << r << std::endl;

  std::ostringstream oss;
  oss << r;
  std::string expected = R"***(Recipe for: Microwave Popcorn
Serves 3
Ingredients:
1/2 cup unpopped popcorn
1 teaspoon vegetable oil
1/2 teaspoon salt

Instructions:
In a cup or small bowl, mix together the unpopped popcorn and oil.
Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt.
Fold the top of the bag over twice to seal in the ingredients.
Cook in the microwave at full power for 2 1/2 to 3 minutes,
or until you hear pauses of about 2 seconds between pops.
Carefully open the bag to avoid steam, and pour into a serving bowl.
From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/

)***";

  std::cout << expected << std::endl;

  WhichLineDifferent(oss.str(), expected);
  assert(oss.str() == expected);

  cout << r.IngredientInOneServing("unpopped popcorn") << endl;

  cout << "Changing servings to 6" << endl;
  r.ChangeServings(6);

  std::cout << r << std::endl;

  std::cout << "End" << std::endl;
  return 0;
}