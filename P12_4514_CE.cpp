#include "p4_5.h"
#include <vector>

std::vector<long long> count_sets(int n, long long k,
		int L, int R, std::vector<int> c)
{
	std::vector<long long> ans(n);

	std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(R+1, 0));

	for(int i = 0; i <= n; i++)
		dp[i][0] = 1;
	if(c[0] <= R) dp[1][c[0]] = 1;

    for(int i = 2; i <= n; i++){
        for(int target = 1; target <= R; target++){
            dp[i][target] = dp[i-1][target] + ((c[i-1] <= target) ? dp[i-1][target-c[i-1]]: 0);
            printf("%lld, ", dp[i][target]);
        }
        printf("\n");
    }

	return ans;
}
