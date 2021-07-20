#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <sstream>
using std::istringstream;
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

int main() {
  int num_stores = GetNum();
  vector<Store> stores_list = MakeStoresVec(num_stores);
  vector<pair<string, int>> shopping_list =
      MakeShoppingList();  // vector of pair<item, qty needed>
  vector<pair<string, int>> items_available =
      MakeItemsAvailable(stores_list);  // vector of pair<store name,
  vector<pair<string, Shopping>>
      for_output;  // pair<item, shopping>; for output
  std::for_each(shopping_list.begin(), shopping_list.end(),
                [&stores_list, &for_output,
                 &shopping_list](const pair<string, int> &item) {
                  vector<Store> with_item =
                      FindStoreWithItem(stores_list, item.first);
                  Shopping instruct(with_item, shopping_list, item.first);
                  for_output.push_back(make_pair(item.first, instruct));
                });

  cout << "Store Related Information (ordered by in-file order):" << endl;
  cout << "There are " << num_stores << " store(s)." << endl;
  std::for_each(stores_list.begin(), stores_list.end(), [](const Store &store) {
    cout << store.name << " has " << store.invtry.size() << " distinct items."
         << endl;
  });
  cout << endl;

  cout << "Item Related Information (ordered alphabetically):" << endl;
  cout << "There are " << items_available.size()
       << " distinct item(s) available for purchase." << endl;
  std::for_each(items_available.begin(), items_available.end(),
                [](const pair<string, int> &p) {
                  cout << "There are " << p.second << " " << p.first << "(s)."
                       << endl;
                });
  cout << endl;

  int num;
  double overall_total = 0.00;
  cout << "Shopping:" << endl;
  for (auto itr = for_output.begin(); itr != for_output.end(); ++itr) {
    auto item = itr->first;
    auto buying = itr->second.instruct;
    cout << "Trying to order " << itr->second.need << " " << item << "(s)."
         << endl;
    // counting stores that have the item
    num = std::count_if(
        stores_list.begin(), stores_list.end(),
        [&item](Store &s) { return s.invtry.find(item) != s.invtry.end(); });
    cout << num << " store(s) sell " << item << "." << endl;
    cout << "Total price: $" << std::fixed << std::setprecision(2)
         << itr->second.total << endl;
    std::for_each(buying.begin(), buying.end(), [](const pair<Store, int> &s) {
      cout << "Order " << s.second << " from " << s.first.name << " in "
           << s.first.location << endl;
    });
    overall_total += itr->second.total;
    cout << endl;
  }

  cout << "Be sure to bring $" << std::fixed << std::setprecision(2)
       << overall_total << " when you leave for the stores." << endl;
}
