#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
struct Cell{
  long long cost = LONG_MAX;// minimal local arrangement
  long long cut = LONG_MAX;// weighted sum of edges
  int rightmost = -1;
};
vector<int> neighbor(23);
const int MASK = 0x7FFFFF;
long long cut_g(const int v, const int st){
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

    vector<Cell>table(size);
    table[0].cost = 0;
    table[0].cut = 0;

    
    vector<vector<int>>sets(n, vector<int>());
    sets[0].push_back(0);
    for(int i = 1; i < size - 1; i++){
      const int bit = __builtin_popcount(i);
      // cout << "i = " << i << " has " << bit << " bits set\n";
      sets[bit].push_back(i);
    }

    for(int bit = 0; bit < n; bit++){
      for(const int &s: sets[bit]){
        // cout << "sets[" << bit << "] = " << s << "\n";
        const long long cut_s = table[s].cut;
        const long long new_cost = table[s].cost + cut_s;
        for(int j = 0; j < n; j++){
          const int j_mask = 1 << j;
          if((s & j_mask) || (table[s | j_mask].cost <= new_cost)) continue;
          const int new_subset = (s | j_mask);
          table[new_subset].cost = new_cost;
          table[new_subset].rightmost = j;
          table[new_subset].cut = cut_s - cut_g(j, s) + cut_g(j, MASK ^ s);
        }
      }
    }

    int set = size - 1;
    vector<int>order(n);
    for(int i = n - 1; i >= 0; i--){
      const int v = table[set].rightmost;
      order[i] = v + 1;
      set ^= (1 << v);
    }
    return make_pair(table[size - 1].cost, order);
}
