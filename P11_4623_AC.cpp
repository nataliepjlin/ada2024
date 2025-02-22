#include "p4_4.h"
#include <vector>
int maximum_dishes(std::vector<int>& dishes, int A, int B, long long T){
    if(T < A) return 0;

    const int n = dishes.size();
    std::vector<std::vector<long long>>dp(n+1, std::vector<long long>(n+1, T+1));// i: last dish's value, j: number of dishes

    dp[0][1] = A;
    dp[dishes[0]][1] = A;

    int max_dishes = 1;
    const long long best_case = T / A;


    for(int i = 2; i <= n; i++){
        // printf("%lld, ", dp[i][1]);
        long long prev_val = A; int prev_size = 1;
        for(int j = 2; j <= std::min((long long)i, best_case); j++){

            long long diff_prev = dp[0][j-1] + A + B;
            // printf("diff_prev = %lld\n", diff_prev);
            if(diff_prev > T || diff_prev < 0) diff_prev = T+1;

            long long same_prev = (dp[ dishes[i-1] ][j-1] == T+1) ? (T+1) : (dp[ dishes[i-1] ][j-1] + A);
            // printf("same_prev = %lld\n", same_prev);
            
            if(same_prev > T || same_prev < 0) same_prev = T+1;

            dp[ dishes[i-1] ][prev_size] = prev_val;
            if(dp[0][prev_size] > dp[ dishes[i-1] ][prev_size]){// min at `prev_size`
                dp[0][prev_size] = dp[ dishes[i-1] ][prev_size];
            }
            if(dp[ dishes[i-1] ][prev_size] <= T && max_dishes < prev_size){
                max_dishes = prev_size;
                // if(max_dishes == best_case) return max_dishes;
            }

            prev_val = std::min(diff_prev, same_prev);
            prev_size = j;
        }
        dp[ dishes[i-1] ][prev_size] = prev_val;
        if(dp[0][prev_size] > dp[ dishes[i-1] ][prev_size]){// min at `prev_size`
            dp[0][prev_size] = dp[ dishes[i-1] ][prev_size];
        }
        if(dp[ dishes[i-1] ][prev_size] <= T && max_dishes < prev_size){
            max_dishes = prev_size;
            // if(max_dishes == best_case) return max_dishes;
        }
        // printf("\n");
    }


    // for(int i = 0; i <= n; i++){
    //     for(int j = 1; j <= n; j++){
    //         printf("%lld, ", dp[i][j]);
    //     }
    //     printf("\n");
    // }

    return max_dishes;
}