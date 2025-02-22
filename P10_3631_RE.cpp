#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
struct Cell{
  long long cost = LONG_MAX;// minimal local arrangement
  int cut;// weighted sum of edges with the other set
  int rightmost = -1;
  vector<int> order;
};
vector<int> neighbor(23);
vector<Cell>table;
const int MASK = 0x7FFFFF;
int cut_g(const int v, const int st){
 return __builtin_popcount(neighbor[v] & st);
}
pair<int, vector<int>> solve(int n, int m, vector<pair<int, int>> es){
    const int size = 1 << n;  

    fill(neighbor.begin(), neighbor.end(), 0);
    for(int i = 0; i < m; i++){
        const int a = es[i].first - 1, b = es[i].second - 1;
        neighbor[a] |= (1 << b);
        neighbor[b] |= (1 << a);
    }

    table.clear();
    table.resize(size);
    table[0].cost = 0;
    table[0].cut = 0;

    for(int s = 0; s < size - 1; s++){
      const long long cut_s = table[s].cut;
      const int new_cost = table[s].cost + cut_s;
      for(int bit = 0; bit < n; bit++){
        const int bit_mask = 1 << bit;
        if(s & bit_mask) continue;

        const int new_subset = (s | bit_mask);
        table[s].order.push_back(bit + 1);

        if((table[new_subset].cost > new_cost)
        || (table[new_subset].cost == new_cost && table[new_subset].order > table[s].order)){
          table[new_subset].cost = new_cost;
          table[new_subset].rightmost = bit;
          table[new_subset].order = table[s].order;
          table[new_subset].cut = cut_s - cut_g(bit, s) + cut_g(bit, MASK ^ s);
        }
        table[s].order.pop_back();
      }
      table[s].order.clear();
    }

    const int set = size - 1;
    return make_pair(table[set].cost, table[set].order);
}
