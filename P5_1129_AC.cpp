#include "p2_4.h"

#include <numeric>

void merge(std::vector<int>&ans, int front, int mid, int end){
    std::vector<int> left(ans.begin() + front, ans.begin() + mid + 1);
    std::vector<int> right(ans.begin() + mid + 1, ans.begin() + end + 1);
    int i = 0, j = 0, k = front;
    while(i < left.size() && j < right.size()){
        if(get_result(left[i], right[j])){
            ans[k++] = left[i++];
        }else{
            ans[k++] = right[j++];
        }
    }
    while(i < left.size()){
        ans[k++] = left[i++];
    }
    while(j < right.size()){
        ans[k++] = right[j++];
    }
}
void merge_sort(std::vector<int>&ans, int front, int end){
    if(front < end){
        int mid = (front + end) >> 1;
        merge_sort(ans, front, mid);
        merge_sort(ans, mid+1, end);
        merge(ans, front, mid, end);
    }
    
}

std::vector<int> find_permutation(int n) {

    std::vector<int> ans(n);
    std::iota(ans.begin(), ans.end(), 1);
    merge_sort(ans, 0, n-1);
    return ans;
}
