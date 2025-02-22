#include "p4_5.h"
#include <vector>

std::vector<long long> count_sets(int n, long long k,
		int L, int R, std::vector<int> c)
{
	std::vector<long long> ans(n);

	std::vector<std::vector<long long>> prefix_dp(n + 1, std::vector<long long>(R+1, 0));
    std::vector<std::vector<long long>> suffix_dp(n + 2, std::vector<long long>(R+1, 0));

    std::vector<std::vector<long long>> sum(n + 2, std::vector<long long>(R+1, 0));

	for(int i = 0; i <= n; i++){
        prefix_dp[i][0] = 1;
        suffix_dp[i][0] = 1;
    }
    suffix_dp[n+1][0] = 1;

    for(int i = 1, j = n; i <= n; i++, j--){
        for(int target = 1; target <= R; target++){
            prefix_dp[i][target] = prefix_dp[i-1][target] + ((c[i-1] <= target) ? prefix_dp[i-1][target-c[i-1]]: 0);

            suffix_dp[j][target] = suffix_dp[j+1][target] + ((c[j-1] <= target) ? suffix_dp[j+1][target-c[j-1]]: 0);
            sum[j][target] = sum[j][target-1] + suffix_dp[j][target];
            // printf("%lld, ", sum[j][target]);
        }
        // printf("\n");
    }

    for(int skip = 1; skip <= n; skip++){
        ans[skip - 1] = 0;
        int prev = skip - 1;
        int next = skip + 1;
        for (int target = 0; target <= L - 1; target++) {
            long long prefix_count = prefix_dp[prev][target];
            long long suffix_count = sum[next][R - target] - sum[next][L - 1 - target];

            long long count = prefix_count * suffix_count;
            if(count >= k || count < 0){
                ans[skip - 1] = k;
                break;
            }

            ans[skip - 1] += count;

            if(ans[skip - 1] >= k || ans[skip - 1] < 0){
                ans[skip - 1] = k;
                break;
            }
        }

        for (int target = L; target <= R && ans[skip-1] < k; target++) {
            ans[skip - 1] += prefix_dp[prev][target];
            if(ans[skip - 1] >= k || ans[skip - 1] < 0){
                ans[skip - 1] = k;
                break;
            }
        }
    }

    return ans;
}
