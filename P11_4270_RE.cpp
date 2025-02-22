#include "p4_4.h"
#include <vector>
struct Cell{
    int max = -1;
    int prev = -1;
};

int solve(int i, int prev, const int n, int src_val, const std::vector<int>& dishes, const int A, const int B, long long T, std::vector<std::vector<Cell>>&dp){
    if(i == n || T == 0) return 0;
    if(dp[i][T].prev != -1 && prev != -1
    && dishes[ dp[i][T].prev ] == dishes[prev]) return dp[i][T].max;
    
    long long cost = A + ((src_val == -1 || src_val == dishes[i]) ? 0 : B);
    int skip = solve(i + 1, prev, n, src_val, dishes, A, B, T, dp);
    int take = (T >= cost) ? solve(i + 1, i, n, dishes[i], dishes, A, B, T - cost, dp) + 1 : 0;

    int ans = std::max(skip, take);
    if(ans > dp[i][T].max){
        dp[i][T].max = ans;
        dp[i][T].prev = (ans == skip) ? prev : i;
    }
    return ans;
}

int maximum_dishes(std::vector<int>& dishes, int A, int B, long long T){
    int n = dishes.size();
    std::vector<std::vector<Cell>>dp(n, std::vector<Cell>(T + 1));
    return solve(0, -1, n, -1, dishes, A, B, T, dp);;
}