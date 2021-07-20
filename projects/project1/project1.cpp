#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cmath>
#include <string>
using std::string;

int convert_other_base_to_decimal(int value, int base) {
  // the following source helped me figure how to find the length of an integer
  // using std::to_string
  // https://stackoverflow.com/questions/22648978/c-how-to-find-the-length-of-an-integer
  int n = std::to_string(value).length();
  int total = 0;
  int digit;
  // the following link helped me figure out how to iterate through digits of an
  // int
  // https://stackoverflow.com/questions/8671845/iterating-through-digits-in-integer-in-c
  for (int i = 0; i <= n; ++i) {
    digit = value % 10;
    total += (digit * pow(base, i));
    value /= 10;
  }
  return total;
}

int convert_decimal_to_other_base(int value, int base) {
  string total = "";
  int r;
  while (value > 0) {
    r = value % base;
    total.insert(0, std::to_string(r));
    value /= base;
  }
  return std::stoi(total);
}

int math_in_other_base(int other_base_a, int other_base_b, int base,
                       char math_operator) {
  int a_dec = convert_other_base_to_decimal(other_base_a, base);
  int b_dec = convert_other_base_to_decimal(other_base_b, base);
  int result;

  switch(math_operator){
    case '+':
      result = a_dec + b_dec;
      break;
    case '-':
      result = a_dec - b_dec;
      break;
    case '/':
      result = a_dec / b_dec;
      break;
    case '%':
      result = a_dec % b_dec;
      break;
    case '*':
      result = a_dec * b_dec;
      break;
    default:
      break;
  }
  return convert_decimal_to_other_base(result, base);
}

int main() {
  int a;
  int b;
  int base;
  char math_operator;
  cin >> a >> b >> base >> math_operator;
  return 0;
}