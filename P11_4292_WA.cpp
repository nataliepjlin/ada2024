#include "p4_4.h"
#include <vector>
#include <climits>
struct Cell{
    int max = -1;//max dishes
    long long time = LONG_MAX;//cost
};
int maximum_dishes(std::vector<int>& dishes, int A, int B, long long T){
    int n = dishes.size();
    std::vector<Cell> dp(n + 1);
    dp[0].max = 0;
    dp[0].time = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < i; j++){
            long long cost = A;
            long long extra = (j == 0 || dishes[j - 1] == dishes[i - 1]) ? 0 : B;
            cost += extra;
            cost += dp[j].time;

            int skip = dp[j].max;
            int take = (cost <= T) ? (dp[j].max + 1) : 0;
            
            if(skip > dp[i].max || (skip == dp[i].max && dp[j].time < dp[i].time)){
                dp[i].max = skip;
                dp[i].time = dp[j].time;
            }
            if(take > dp[i].max || (take == dp[i].max && cost < dp[i].time)){
                dp[i].max = take;
                dp[i].time = cost;
            }
        }
    }
    return dp[n].max;
}