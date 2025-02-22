#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
struct Cell{
  int cost = INT_MAX;// minimal local arrangement
  int cut;// weighted sum of edges with the other set
  int rightmost;
  // __uint128_t priority = 0;
};
vector<int> neighbor(23);
vector<Cell> table;
const int MASK = 0x7FFFFF;
int cut_g(const int v, const int st){
 return __builtin_popcount(neighbor[v] & st);
}
pair<int, vector<int>> solve(int n, int m, vector<pair<int, int>> es){
    const int size = 1 << n;  

    fill(neighbor.begin(), neighbor.begin() + n, 0);
    for(int i = 0; i < m; i++){
        const int a = es[i].first - 1, b = es[i].second - 1;
        neighbor[a] |= (1 << b);
        neighbor[b] |= (1 << a);
    }

    table.clear();
    table.resize(size);
    table[0].cost = 0;
    table[0].cut = 0;
    // table[0].priority = 0;

    for(int s = 0; s < size - 1; s++){
      const int cut_s = table[s].cut;
      const int new_cost = table[s].cost + cut_s;
      // table[s].priority <<= 5;

      for(int bit = 0; bit < n; bit++){
        const int bit_mask = 1 << bit;
        if(s & bit_mask) continue;

        const int new_subset = (s | bit_mask);

        // table[s].priority |= (n - bit);

        if(table[new_subset].cost >= new_cost){
          table[new_subset].cost = new_cost;
          table[new_subset].cost = new_cost;
          table[new_subset].rightmost = bit;
          // table[new_subset].priority = table[s].priority;
          table[new_subset].cut = cut_s - cut_g(bit, s) + cut_g(bit, MASK ^ s);
        }

        // table[s].priority ^= (n - bit);
      }
      // table[s].priority >>= 5;
      // table[s].priority.clear();
      // table[s].priority.shrink_to_fit();
    }

    int set = size - 1;
    vector<int>order(n);
    for(int i = 0; i < n; i++){
      const int v = table[set].rightmost;
      order[i] = v + 1;
      set ^= (1 << v);
    }
    return make_pair(table[size - 1].cost, order);
}
