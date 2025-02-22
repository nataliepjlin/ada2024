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
    dp[1].max = 1;
    dp[1].time = A;
    for(int i = 2; i <= n; i++){
        for(int j = 1; j < i; j++){
            long long cost = A + ((dishes[i - 1] == dishes[j - 1]) ? 0 : B);
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