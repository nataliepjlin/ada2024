#include "p2_6.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
int solve(int n, int k, std::string v, std::vector<std::string> a) {
	sort(a.begin(), a.end());

    int ans = 0;
    std::vector<bool>skip(n, false);
    for(int i = 0; i < n; i++){
        if(skip[i]) continue;
        bool valid = true, smaller = false;
        // std::cout << "finding max xor with " << i << "th string: " << a[i] << "\n";
        int low = 0, high = n - 1;
        for(int bit = 0; bit < k && valid && !smaller; bit++){
            // std::cout << "check bit: " << bit << ", low = " << low << ", high = " << high << "\n";
            while(low <= high){
                int mid = (low + high) / 2;
                // std::cout << "low = " << low << ", high = " << high << ", a[" << mid << "] = " << a[mid] << "\n";
                if(a[i][bit] != a[mid][bit]){ // xor == 1
                    if(v[bit] == '0'){
                        skip[mid] = true;
                        valid = false;
                    } 
                    else{ // limit search space to a[low][bit] == a[mid][bit] == a[high][bit]
                        if(a[mid][bit] == '0'){
                            while(a[high][bit] == '1' && high > mid){
                                int middle = (mid + high) / 2;
                                if(a[middle][bit] == '0') mid = middle;
                                else high = middle - 1;
                            }
                        }
                        else{// a[mid][bit] == '1'
                            while(a[low][bit] == '0' && low < mid){
                                int middle = (low + mid) / 2;
                                if(a[middle][bit] == '0') low = middle + 1;
                                else mid = middle;
                            }
                        }
                    }
                    break;
                }
                // xor == 0
                else if(low == high){
                    smaller = (v[bit] == '1');
                    break;
                }
                else{ 
                    if(a[mid][bit] == '0') low = mid + 1;
                    else high = mid - 1;
                }
            }
        }
        ans += valid;
        // std::cout << "valid = " << valid << ", smaller = " << smaller << "\n\n";
    }
    return ans;
}
