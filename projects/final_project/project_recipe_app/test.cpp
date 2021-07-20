#include <iostream>
#include <string>
using std::string;
#include "app.h"
#include "recipe.h"
#include "utility.h"

int main() {
  Recipe r("Microwave Popcorn", 3);
  r.AddIngredient(" 7/28 cup \tunpopped   popcorn ");
  r.AddIngredient("9-7/7 teaspoon vegetable oil");
  r.AddIngredient("3-7/3 teaspoon salt");
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
1/4 cup unpopped   popcorn
10 teaspoon vegetable oil
5-1/3 teaspoon salt

Instructions:
In a cup or small bowl, mix together the unpopped popcorn and oil.
Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt.
Fold the top of the bag over twice to seal in the ingredients.
Cook in the microwave at full power for 2 1/2 to 3 minutes,
or until you hear pauses of about 2 seconds between pops.
Carefully open the bag to avoid steam, and pour into a serving bowl.
From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/

)***";

  std::cout << std::boolalpha << (expected == oss.str());
}