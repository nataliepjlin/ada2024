#include "p2_6.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
int solve(const int n, const int k, std::string v, std::vector<std::string> a) {
	sort(a.begin(), a.end());
    int ans = 0;
    std::vector<bool>skip(n, false);
    
    for(int i = 0; i < n; i++){
        if(skip[i]) continue;
        int low = 0, high = n - 1;
        bool valid = true, smaller = false;
        // std::cout << "i: " << i << std::endl;
        for(int j = 0; j < k && valid && !smaller; j++){//bit
            int prev_low = low, prev_high = high;
            while(low <= high){
                int mid = (low + high) >> 1;
                if(a[i][j] != a[mid][j]){//xor at this bit can be 1
                    if(v[j] == '0'){//fail
                        valid = false;
                        skip[mid] = true;
                    }
                    else{//limit search space to a[low][j] == a[mid][j] == a[high][j]
                        if(a[mid][j] == '0'){
                            while(a[high][j] == '1' && high > mid){
                                int middle = (mid + high) >> 1;
                                if(a[middle][j] == '0') mid = middle;
                                else high = middle - 1;
                            }
                        }
                        else{
                            while(a[low][j] == '0' && low < mid){
                                int middle = (low + mid) >> 1;
                                if(a[middle][j] == '0') low = middle + 1;
                                else mid = middle;
                            }
                        }
                    }
                    break;//finish search at this bit
                }
                else if(low == high && v[j] == '1'){
                    smaller = true;
                    break;
                }
                else{
                    if(a[i][j] == '0') low = mid + 1;
                    else high = mid - 1;
                }
            }
            // std::cout << "j: " << j << ", low: " << low << " high: " << high << ", valid: " << valid << ", smaller = " << smaller << "\n";
            if(low > high){//the whole array has the same bit
                low = prev_low;
                high = prev_high;
            }
        }
        // std::cout << "\n";
        ans += valid;
    }

    return ans;
}
