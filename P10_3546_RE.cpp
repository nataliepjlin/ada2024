#include "p3_6.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
vector<int>TO_CHECK(23);
const int mask = 0x7FFFFF;

void perm(int visited, vector<vector<long long>>&dp, vector<int>&service_loc, 
long long &min_sum, vector<int>&min_order, long long cur_sum, vector<int>&cur_order,
int num, int num_pos, const int n){
  const int exist_neighbor = TO_CHECK[num] & visited;

  long long dists = 0;
  if(exist_neighbor){
    for(int bit = 0; bit < n; bit++){
      if(exist_neighbor & (1 << bit))
        dists += abs(service_loc[bit] - num_pos);
    }
  }

  cur_sum += dists;
  if(cur_sum >= min_sum){
    return;
  }
  // dp[num][visited] = dists;
  // cout << "dp[" << num << "][" << visited << "] = " << dp[num][visited] << "\n";
  if(num_pos == n - 1){
    min_sum = cur_sum;
    // cout << "min_sum = " << min_sum << "\n\n";
    for(int i = 0; i < n; i++) min_order[i] = cur_order[i] + 1;
    return;
  }

  for(int i = 0; i < n; i++){
    if(visited & (1 << i)) continue;
    const int next_visited = visited | (1 << i);
    if((next_visited ^ mask) < next_visited) continue;// avoid mirrored permutation
    service_loc[i] = num_pos + 1;
    cur_order[num_pos + 1] = i; 
    perm(next_visited | (1 << i), dp, service_loc, min_sum, min_order, cur_sum, cur_order, i, num_pos + 1, n);
  }
}

pair<int, vector<int>> solve(int n, int m, vector<pair<int, int>> es) {
  const int size = 1 << n;
  vector<vector<long long>>dp(n, vector<long long>(size, -1));
  
  vector<int>service_loc(n);

  fill(TO_CHECK.begin(), TO_CHECK.end(), 0);
  for(int i = 0; i < m; i++){
    const int a = es[i].first - 1, b = es[i].second - 1;
    TO_CHECK[a] |= (1 << b);
    TO_CHECK[b] |= (1 << a);
  }

  vector<int>min_order(n);
  vector<int>cur_order(n);
  long long min_sum = LONG_MAX;
  for(int i = 0; i < n; i++){
    service_loc[i] = 0;
    cur_order[0] = i;
    perm(1 << i, dp, service_loc, min_sum, min_order, 0, cur_order, i, 0, n);
  }

  return make_pair(min_sum, min_order);
}
