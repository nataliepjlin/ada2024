#include "p4_4.h"
#include <vector>
#include <climits>
int maximum_dishes(std::vector<int>& dishes, int A, int B, long long T){
    const int n = dishes.size();
    std::vector<std::vector<long long>>dp(n + 1, std::vector<long long>(n + 1, T + 1));// time
    dp[0][0] = 0;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < i; j++){
            for(int plate = 0; plate <= j; plate++){
                dp[i][plate] = std::min(dp[i][plate], dp[j][plate]);// skip
                if(dp[i][plate] <= T && plate > ans) ans = plate;

                if(dp[j][plate] < T){
                    long long cost = A + dp[j][plate];
                    cost += (j == 0 || dishes[j - 1] == dishes[i - 1]) ? 0 : B;
                    if(cost > 0){
                        dp[i][plate + 1] = std::min(dp[i][plate + 1], cost);// avoid overflow
                        if(dp[i][plate + 1] <= T && plate + 1 > ans) ans = plate + 1;
                    }
                }
                
            }
        }
    }
    return ans;
}