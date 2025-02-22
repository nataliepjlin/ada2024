#include "p4_4.h"
#include <vector>
#include <climits>
struct Info{
    int plate;
    long long time;
};
int solve(int cur, const int n, const std::vector<int>& dishes, const int A, const int B, long long T, std::vector<std::vector<int>>&dp){
    if(T <= 0) return 0;

    if(dp[cur][T] != -1) return dp[cur][T];
    if(cur == n - 1) return dp[cur][T] = 0;

    for(int i = cur + 1; i < n; i++){
        long long extra = (dishes[cur] == dishes[i]) ? 0 : B;
        long long cost = A + extra;

        int skip = solve(i, n, dishes, A, B, T, dp);
        int take = (T >= cost) ? 1 + solve(i, n, dishes, A, B, T - cost, dp) : 0;
        dp[cur][T] = std::max(dp[cur][T], std::max(skip, take));
    }
    // printf("dp[%d][%lld] = %d\n", cur, T, dp[cur][T]);
    return dp[cur][T];
}
int maximum_dishes(std::vector<int>& dishes, int A, int B, long long T){
    const int n = dishes.size();
    std::vector<std::vector<int>>dp(n, std::vector<int>(T + 1, -1));//max plate
    
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans = std::max(ans, 1 + solve(i, n, dishes, A, B, T - A, dp));
    }
    return ans;
}