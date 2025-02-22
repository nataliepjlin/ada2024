#include "p3_5.h"
#include <vector>
#define MAX 1000000009
int alloc(const std::vector<int>& a, std::vector<long long>&sums, const int sum_size, const int idx){
    if(idx < 0){
        if(sum_size == 0) return MAX;

        long long mx = sums[0], mn = sums[0];
        for(int i = 1; i <= sum_size; i++){
            mx = std::max(mx, sums[i]);
            mn = std::min(mn, sums[i]);
        }
        return mx-mn;
    }
    //add to current sum
    sums[sum_size] += a[idx];
    long long cur_sum = alloc(a, sums, sum_size, idx-1);
    sums[sum_size] -= a[idx];
    //create new sum
    sums.push_back(a[idx]);
    long long new_sum = alloc(a, sums, sum_size+1, idx-1);
    sums.pop_back();

    return std::min(cur_sum, new_sum);
}

int minimum_possible_unbalancedness(std::vector<int>& a){
    const int n = a.size();
    std::vector<long long>sums{a[n-1]};
    return alloc(a, sums, 0, n-2);
}

