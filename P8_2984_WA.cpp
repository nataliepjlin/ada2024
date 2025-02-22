#include "p3_4.h"
#include <vector>
#include <iostream>
int largest_square(int M, int N, std::vector<std::vector<int>> &c) {
    std::vector<std::vector<int>> dp(M + 1, std::vector<int>(N + 1, 0));
    int maxsq = 0;
    for(int i = 1; i <= M; i++){
        for(int j = 1; j <= N; j++){
            const int mn = std::min(dp[i - 1][j - 1], std::min(dp[i - 1][j], dp[i][j - 1]));
            if(mn != 0 
            && c[i - 1][j - 1] == c[i - 2][j - 1]
            && c[i - 1][j - 1] == c[i - 1][j - 2]
            && c[i - 1][j - 1] == c[i - 2][j - 2]){
                dp[i][j] = mn + 1;
                maxsq = std::max(maxsq, dp[i][j]);
            }
            else dp[i][j] = 1;
        }
    }
    
    // for(int i = 0; i <= M; i++){
    //     for(int j = 0; j <= N; j++){
    //         std::cout << dp[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return maxsq;
}
