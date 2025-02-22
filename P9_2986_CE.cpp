#include "p3_4.h"
#include <vector>
#include <iostream>
int largest_square(int M, int N, std::vector<std::vector<int>> &c) {
    std::vector<int> dp(N + 1, 0);
    int maxsq = 1;

    for(int i = 1; i <= M; i++){
        int prev = 0;
        for(int j = 1; j <= N; j++){
            const int mn = std::min(prev, std::min(dp[j], dp[j - 1]));
            int tmp = dp[j];
            if(mn != 0 
            && c[i - 1][j - 1] == c[i - 2][j - 1]
            && c[i - 1][j - 1] == c[i - 1][j - 2]
            && c[i - 1][j - 1] == c[i - 2][j - 2]){
                dp[j] = mn + 1;
                maxsq = std::max(maxsq, dp[j]);
            }
            else dp[j] = 1;
            prev = tmp;
            /*
            prev       dp[j]
            dp[j - 1]  current
            */
        }
    }
    return maxsq;
}
