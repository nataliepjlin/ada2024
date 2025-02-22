#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

struct Cell {
    long long cur_sum;
    long long max;
    long long min;
};

long long minimum_possible_unbalancedness(std::vector<int>& a) {
    const int n = a.size();
    if (n == 2) return std::abs(a[0] - a[1]);

    std::vector<std::vector<Cell>> dp(n + 1, std::vector<Cell>(n + 1));

    dp[1][0].cur_sum = 0;// for prefix sum
    dp[1][1].cur_sum = a[0];
    dp[1][1].max = a[0];
    dp[1][1].min = a[0];

    for(int i = 2; i <= n; i++){ 
        // diagonal
        dp[i][i].cur_sum = a[i - 1];
        dp[i][i].max = std::max(dp[i - 1][i - 1].max, (long long)a[i - 1]);
        dp[i][i].min = std::min(dp[i - 1][i - 1].min, (long long)a[i - 1]);
        
        // 1st column
        dp[i][1].cur_sum = dp[i - 1][1].cur_sum + a[i - 1];
        dp[i][1].max = dp[i][1].min = dp[i][1].cur_sum;
    }

    long long ans = dp[n][n].max - dp[n][n].min;
    for(int i = 3; i <= n; i++){
        for(int j = 2; j < i; j++){
            // extend from dp[i-1][j]
            long long cur_sum = dp[i - 1][j].cur_sum + a[i - 1];
            long long mx = std::max(dp[i - 1][j].max, cur_sum), mn = dp[i - 1][j].min;
            long long diff = mx - mn;
            // std::cout << "init dp[" << i << "][" << j << "] as " << diff << "\n";
            
            // add new from dp[j-1~i-1][j-1]
            for(int k = j - 1; k <= i - 1; k++){
                long long tmp_sum = dp[i][1].cur_sum - dp[k][1].cur_sum;
                long long tmp_max = std::max(dp[k][j - 1].max, tmp_sum);
                long long tmp_min = std::min(dp[k][j - 1].min, tmp_sum);
                long long tmp_diff = tmp_max - tmp_min;
                if(tmp_diff < diff){
                    cur_sum = tmp_sum;
                    mx = tmp_max;
                    mn = tmp_min;
                    diff = tmp_diff;
                    // std::cout << "update dp[" << i << "][" << j << "] to " << diff << " by [" << k << "][" << j - 1 << "] with tmp_sum = " << tmp_sum << "\n";
                }
            }
            dp[i][j].cur_sum = cur_sum;
            dp[i][j].max = mx;
            dp[i][j].min = mn;

            if(i == n) ans = std::min(ans, diff);
        }
    }

    // for(int i = 2; i <= n; i++){
    //     for(int j = 2; j <= i; j++){
    //         std::cout << dp[i][j].max - dp[i][j].min << ", ";
    //     }
    //     std::cout << "\n";
    // }

    return ans;
}