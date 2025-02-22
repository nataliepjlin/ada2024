#include "p4_4.h"
#include <vector>

int solve(int i, const int n, int src, const std::vector<int>& dishes, const int A, const int B, long long T, std::vector<std::vector<std::vector<int>>>&dp){
    if(i == n || T == 0) return 0;
    if(src != -1 && dp[src][i][T] != -1) return dp[src][i][T];
    
    long long cost = A + ((src == -1 || dishes[src] == dishes[i]) ? 0 : B);
    int skip = solve(i + 1, n, src, dishes, A, B, T, dp);
    int take = (T >= cost) ? solve(i + 1, n, i, dishes, A, B, T - cost, dp) + 1 : 0;

    int ans = std::max(skip, take);
    if(src != -1) dp[src][i][T] = ans;
    return ans;
}

int maximum_dishes(std::vector<int>& dishes, int A, int B, long long T){
    int n = dishes.size();
    std::vector<std::vector<std::vector<int>>>dp(n, std::vector<std::vector<int>>(n, std::vector<int>(T, -1)));
    return solve(0, n, -1, dishes, A, B, T, dp);;
}

