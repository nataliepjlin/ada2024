#include "p4_5.h"
#include <vector>

std::vector<long long> count_sets(int n, long long k,
		int L, int R, std::vector<int> c)
{
	std::vector<long long> ans(n);

	std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(R+1, 0));
    // std::vector<std::vector<long long>> board(n + 1, std::vector<long long>(R+1, 0));

	for(int i = 0; i <= n; i++)
		dp[i][0] = 1;
	if(c[0] <= R) dp[1][c[0]] = 1;

    ans[n-1] = 0;
    for(int i = 2; i < n; i++){
        for(int target = 1; target <= R; target++){
            dp[i][target] = dp[i-1][target] + ((c[i-1] <= target) ? dp[i-1][target-c[i-1]]: 0);
            // printf("%lld, ", dp[i][target]);
            if(i == n-1 && target >= L && ans[n-1] < k){
                ans[n-1] += dp[i][target];
                ans[n-1] = std::min(ans[n-1], k);
            }
        }
        // printf("\n");
    }
    // printf("\n");

    for(int skip = n-1; skip >= 1; skip--){
        int prev = skip-1;
        ans[skip - 1] = 0;
        for(int i = skip+1; i <= n; i++){
            for(int target = 1; target <= R; target++){
                dp[i][target] = dp[prev][target] + ((c[i-1] <= target) ? dp[prev][target-c[i-1]]: 0);
                // printf("%lld, ", dp[i][target]);
                if(i == n && target >= L && ans[skip-1] < k){
                    ans[skip-1] += dp[i][target];
                    ans[skip-1] = std::min(ans[skip-1], k);
                }
            }
            prev = i;
            // printf("\n");
        }
        // printf("\n");
    }

    return ans;
}
