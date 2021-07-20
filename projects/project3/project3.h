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

struct Store {
  string name;
  string location;
  map<string, pair<int, double>>
      invtry;  // key: item, value: pair of qty and price
  Store();
};
struct Shopping {  // creating class for items to be shopped for
  vector<pair<Store, int>>
      instruct;  // vector of pairs of Store and qty there is particular item
  double total = 0.00;
  int need;  // qty needed for item
  Shopping(vector<Store> st, vector<pair<string, int>> m, string s);
};

vector<pair<string, int>> MakeShoppingList();
int GetNum();
vector<Store> MakeStoresVec(const int &n);
vector<pair<string, int>> MakeItemsAvailable(const vector<Store> &s);
vector<Store> FindStoreWithItem(const vector<Store> &stores_list,
                                const string &item_name);