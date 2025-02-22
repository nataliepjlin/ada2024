#include "p2_6.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
int solve(int n, int k, std::string v, std::vector<std::string> a) {
	sort(a.begin(), a.end());

    int ans = 0;
    for(int i = 0; i < n; i++){

        int low = 0, high = n - 1, prev_low = low, prev_high = high;
        bool valid = true, found = false;
        // std::cout << "finding max xor with " << i << "th string: " << a[i] << "\n";
        for(int j = 0; j < k && valid && !found; j++){
            // std::cout << "comparing " << j << "th bit (" << a[i][j] << ") from low = " << low << ", high = " << high << "\n";
            if(low > high){
                low = prev_low, high = prev_high;
            }

            while(low <= high){
                prev_low = low, prev_high = high;

                int mid = (low + high) >> 1;
                // std::cout << "low = " << low << ", high = " << high << ", a[" << mid << "] = " << a[mid][j] << "\n";
                if(a[i][j] != a[mid][j]){
                    if(v[j] == '0') valid = false;
                    else{
                        if(a[mid][j] == '0') high = std::min(high, i - 1);// a[i][j] = 1, a[mid][j] = 0
                        else low = std::max(low, i + 1);// a[i][j] = 0, a[mid][j] = 1
                    }
                    break;
                }//xor == 1

                else if(low == high){
                    found = (v[j] == '1');//xor == 0, v[j] == 1 -> sure to be valid
                    break;
                }//no further xor possible at this bit
                
                //xor == 0, v[j] == 0
                if(a[i][j] == '0') low = mid + 1;
                else high = mid - 1;
            }
        }
        ans += valid;
        // std::cout << "valid = " << valid << "\n\n";
    }
    return ans;
}
