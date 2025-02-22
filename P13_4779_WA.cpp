#include "p4_6.h"
#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

vector<int> solve(int m, int n, vector<vector<int>> a) {
  const int TILES = m * n / 2;//at most 75
  if(n < m) swap(n, m);
  const int STATE = 1 << m;// 1<<m
  vector<int>ans(TILES + 1);
  ans[0] = 1;

  vector<vector<vector<long long>>>dp(2, vector<vector<long long>>(STATE, vector<long long>(TILES + 1, 0)));

  int prev = 0, cur = 1;
  for(int j = 0; j < n; j++){//col
    for(int i = 0; i < m; i++){//row
      fill(dp[cur].begin(), dp[cur].end(), vector<long long>(TILES + 1, 0));

      if(j == 0) dp[cur][(1 << (i + 1)) - 1][0] = 1;
      else dp[cur][STATE - 1][0] = 1;

      for(int mask = 0; mask < STATE; mask++){
        for(int tile = 1; tile <= TILES; tile++){
          if(!(mask & (1 << i))){//filled
            if(j > 0 && (a[i][j] != a[i][j - 1])){// horizontal
              dp[cur][mask][tile] += dp[prev][mask ^ (1 << i)][tile - 1];
            }

            if(i > 0 && !(mask & (1 << (i - 1))) && (a[i][j] != a[i - 1][j])){// vertical
              dp[cur][mask][tile] += dp[prev][mask ^ (1 << (i - 1))][tile - 1];// left is filled
              if(dp[cur][mask][tile] >= MOD) dp[cur][mask][tile] -= MOD;
              dp[cur][mask][tile] += dp[prev][mask ^ (1 << (i - 1)) ^ (1 << i)][tile - 1];// left can be empty too
              if(dp[cur][mask][tile] >= MOD) dp[cur][mask][tile] -= MOD;
            }
          }
          else{//empty
            dp[cur][mask][tile] += dp[prev][mask ^ (1 << i)][tile];
            dp[cur][mask][tile] += dp[prev][mask][tile];
            if(dp[cur][mask][tile] >= MOD) dp[cur][mask][tile] -= MOD;
          }
        }
      }

      prev ^= 1, cur ^= 1;
    }
  }

  for(int tile = 1; tile <= TILES; tile++){
    long long sum = 0;
    for(int mask = 0; mask < STATE; mask++){
      sum += dp[prev][mask][tile];
      if(sum >= MOD) sum -= MOD;
    }
    ans[tile] = sum;
  }

  return ans;
}
