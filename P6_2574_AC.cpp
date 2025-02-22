#include "p2_5.h"
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
long long diff(const int root1, const int root2,
    const vector<int> &l1, const vector<int> &r1, const vector<int> &s1,
    const vector<int> &l2, const vector<int> &r2, const vector<int> &s2, vector<vector<long long>>&dp){
  if (dp[root1][root2] != -1) return dp[root1][root2];
  
  if(!root1 && !root2) return dp[root1][root2] = 0;
  else if(!root1){
    return dp[root1][root2] = s2[root2] + diff(root1, l2[root2], l1, r1, s1, l2, r2, s2, dp) + diff(root1, r2[root2], l1, r1, s1, l2, r2, s2, dp);
  }
  else if(!root2){
    return dp[root1][root2] = s1[root1] + diff(l1[root1], root2, l1, r1, s1, l2, r2, s2, dp) + diff(r1[root1], root2, l1, r1, s1, l2, r2, s2, dp);
  }

  return dp[root1][root2] = abs(s1[root1] - s2[root2]) + min(diff(l1[root1], l2[root2], l1, r1, s1, l2, r2, s2, dp) + diff(r1[root1], r2[root2], l1, r1, s1, l2, r2, s2, dp),
  diff(l1[root1], r2[root2], l1, r1, s1, l2, r2, s2, dp) + diff(r1[root1], l2[root2], l1, r1, s1, l2, r2, s2, dp));
}
long long solve(int N, int M,
    vector<int> l1, vector<int> r1, vector<int> s1,
    vector<int> l2, vector<int> r2, vector<int> s2) {
    
  vector<vector<long long>>dp(N + 1, vector<long long>(M + 1, -1));
  return diff(1, 1, l1, r1, s1, l2, r2, s2, dp);
}
