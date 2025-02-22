#include "p4_4.h"
#include <vector>
int maximum_dishes(std::vector<int>& dishes, int A, int B, long long T){
    if(T < A) return 0;

    const int n = dishes.size();
    std::vector<std::vector<long long>>dp(n+1, std::vector<long long>(n+1));// i: last dish, j: number of dishes
    
    // for(int i = 1; i <= n; i++){
    //     dp[i][1] = A;
    // }

    dp[1][1] = A;
    int max_dishes = 1;
    for(int i = 2; i <= n; i++){
        dp[i][1] = A;
        printf("%lld, ", dp[i][1]);
        for(int j = 2; j <= i; j++){
            dp[i][j] = T + 1;
            for(int k = j - 1; k < i; k++){
                if(dp[k][j-1] >= T) continue;

                long long time = dp[k][j-1]  +  A;
                long long extra = (dishes[i-1] == dishes[k-1]) ? 0 : B;
                if(time > T || (time == T && extra)) continue;
                time += extra;
                if(time >= dp[i][j] || time < 0) continue;

                dp[i][j] = time;
            }
            // printf("%lld, ", dp[i][j]);
            if(dp[i][j] <= T) max_dishes = std::max(max_dishes, j);
        }
        // printf("\n");
    }

    return max_dishes;
}