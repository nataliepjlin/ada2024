#include "p3_5.h"
#include <vector>
#define MAX 1000000009
int alloc(const std::vector<int>& a, std::vector<long long>&sums, const int tail, const int idx){
    if(idx < 0){
        if(tail == 0) return MAX;

        long long mx = sums[0], mn = sums[0];
        for(int i = 1; i <= tail; i++){
            mx = std::max(mx, sums[i]);
            mn = std::min(mn, sums[i]);
        }
        return mx-mn;
    }
    //add to current sum
    sums[tail] += a[idx];
    int cur_sum = alloc(a, sums, tail, idx-1);
    sums[tail] -= a[idx];
    //create new sum
    sums.push_back(a[idx]);
    int new_sum = alloc(a, sums, tail+1, idx-1);
    sums.pop_back();

    return std::min(cur_sum, new_sum);
}

int minimum_possible_unbalancedness(std::vector<int>& a){
    const int n = a.size();
    std::vector<long long>sums{a[n-1]};
    return alloc(a, sums, 0, n-2);
}

