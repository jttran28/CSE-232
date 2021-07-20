#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <sstream>
using std::istringstream;
using std::ostringstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <utility>
using std::make_pair;
using std::pair;
#include <algorithm>
#include <iomanip>

#include "project3.h"

Store::Store() {
  /*
  initializes variables within Store struct
  */
  string input_str;
  // for each item in inventoy
  int qty;
  double price;
  string item;
  string temp;
  istringstream iss;

  // init store
  getline(cin, name);
  getline(cin, location);

  // iterating thru inventory
  while (getline(cin, input_str)) {
    if (input_str.empty() == true) {
      break;
    }
    iss.str(input_str);
    getline(iss, item, ',');
    iss >> qty;
    getline(iss, temp);
    price = std::stod(temp.substr(2, 4));
    invtry.insert({item, make_pair(qty, price)});
    iss.clear();
  }
}

Shopping::Shopping(vector<Store> with_item,
                   vector<pair<string, int>> shopping_list, string item_name) {
  /*
  constructor that creates Shopping struct variables
  */
  auto itr = std::find_if(
      shopping_list.begin(), shopping_list.end(),
      [&item_name](const auto &s) { return s.first == item_name; });
  need = itr->second;
  int temp = need;

  // creating instruct variable
  for (Store &store : with_item) {
    /*
    iterating through vector of stores with the particular item
    */
    int i = 0;
    while (i < store.invtry[item_name].first) {
      if (temp == 0) {
        break;
      }
      total += store.invtry[item_name].second;
      --temp;
      ++i;
    }
    if (i != 0) {
      instruct.push_back(make_pair(store, i));
    }
  }
}

vector<pair<string, int>> MakeShoppingList() {
  /*
  creates a vector of pairs (shopping list) of string (item name) and int (qty
  needed for item)
  */
  vector<pair<string, int>> shopping_list;
  string input_str;
  string item;
  int qty;
  istringstream iss;
  getline(cin, input_str);  // skips qty and shopping list line
  while (getline(cin, input_str)) {
    if (input_str.empty() == true) {
      break;
    }
    iss.str(input_str);
    iss >> qty;
    getline(iss, item);
    item = item.substr(1, item.length());
    iss.clear();
    shopping_list.push_back(make_pair(item, qty));
  }
  return shopping_list;
}

int GetNum() {
  /*
  initializes the number of stores there are given the input;
  */
  string input_str;
  int num;
  getline(cin, input_str);
  istringstream iss(input_str);
  iss >> num;
  iss.clear();
  return num;
}

vector<Store> MakeStoresVec(const int &n) {
  /*
  accepts the number of stores there are as int, returns a vector of all the
  stores
  */
  vector<Store> stores;
  for (int i = 0; i < n; ++i) {
    Store store;
    stores.push_back(store);
  }
  return stores;
}

vector<pair<string, int>> MakeItemsAvailable(const vector<Store> &s) {
  /*
  accepts a vector of stores, creates a vector of pairs string (item) and int
  (qty available) for all the stores combined
  */
  map<string, int> temp;
  vector<pair<string, int>> items_available;
  for (auto &store : s) {  // iterating thru all the stores in the vector
    for (auto itr = store.invtry.begin(); itr != store.invtry.end(); ++itr) {
      /*
      iterating thru all items in inventory; following link helped me how to
      determine a key exists in a map:
      https://stackoverflow.com/questions/1939953/how-to-find-if-a-given-key-exists-in-a-c-stdmap
    */
      if (temp.find(itr->first) == temp.end()) {
        temp.insert({itr->first, itr->second.first});
      } else {
        temp[itr->first] += itr->second.first;
      }
    }
  }
  std::for_each(temp.begin(), temp.end(),
                [&items_available](pair<string, int> input) {
                  items_available.push_back(input);
                });
  std::sort(items_available.begin(), items_available.end(),
            [](const pair<string, int> &p1, const pair<string, int> &p2) {
              return p1.first < p2.first;
            });
  return items_available;
}

vector<Store> FindStoreWithItem(const vector<Store> &stores_list,
                                const string &item_name) {
  /*
  accepts vector of stores and string item name, returns a vector of stores with
  only one type of item
  */
  vector<Store> with_item;  // key: store name, value: store
  std::for_each(stores_list.begin(), stores_list.end(),
                [&with_item, &item_name](const Store &s) {
                  if (s.invtry.find(item_name) != s.invtry.end()) {
                    with_item.push_back(s);
                  }
                });
  std::sort(with_item.begin(), with_item.end(),
            [&item_name](Store &s1, Store &s2) {
              return s1.invtry[item_name].second < s2.invtry[item_name].second;
            });
  return with_item;
}