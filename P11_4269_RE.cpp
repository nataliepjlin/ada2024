#include "p4_4.h"
#include <vector>

int solve(int i, const int n, int src_val, const std::vector<int>& dishes, const int A, const int B, long long T, std::vector<std::vector<std::vector<int>>>&dp){
    if(i == n || T == 0) return 0;
    int is_same = (src_val == -1 || src_val == dishes[i]);
    if(src_val != -1 && dp[is_same][i][T] != -1) return dp[is_same][i][T];
    
    long long cost = A + ((src_val == -1 || src_val == dishes[i]) ? 0 : B);
    int skip = solve(i + 1, n, src_val, dishes, A, B, T, dp);
    int take = (T >= cost) ? solve(i + 1, n, dishes[i], dishes, A, B, T - cost, dp) + 1 : 0;

    return dp[is_same][i][T] = std::max(skip, take);
}

int maximum_dishes(std::vector<int>& dishes, int A, int B, long long T){
    int n = dishes.size();
    std::vector<std::vector<std::vector<int>>>dp(2, std::vector<std::vector<int>>(n, std::vector<int>(T, -1)));
    return solve(0, n, -1, dishes, A, B, T, dp);;
}