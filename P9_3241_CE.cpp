#include "p3_5.h"
#include <vector>
#include <climits>
long long alloc(const std::vector<int>& a, std::vector<long long>&sums, const int sum_idx, const int idx){
    if(idx < 0){
        if(sum_idx == 0) return LONG_MAX;

        long long mx = sums[0], mn = sums[0];
        for(int i = 1; i <= sum_idx; i++){
            mx = std::max(mx, sums[i]);
            mn = std::min(mn, sums[i]);
        }
        return mx-mn;
    }
    //add to current sum
    sums[sum_idx] += a[idx];
    long long cur_sum = alloc(a, sums, sum_idx, idx-1);
    sums[sum_idx] -= a[idx];
    //create new sum
    sums.push_back(a[idx]);
    long long new_sum = alloc(a, sums, sum_idx+1, idx-1);
    sums.pop_back();

    return std::min(cur_sum, new_sum);
}

int minimum_possible_unbalancedness(std::vector<int>& a){
    const int n = a.size();
    if(n == 2) return std::abs(a[0] - a[1]);

    std::vector<long long>sums{a[n-1]};
    return alloc(a, sums, 0, n-2);
}

