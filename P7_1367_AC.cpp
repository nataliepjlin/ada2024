#include "p2_6.h"
#include <vector>
#include <string>
#include <algorithm>
struct Node {
	int left = -1, right = -1;
};
int solve(int n, int k, std::string v, std::vector<std::string> a) {
	// build trie
	std::vector<Node> trie(1);
	for(int i = 0; i < n; i++){
		int index = 0;
		// a[i] = std::string(k - std::min(k, (int)a[i].length()), '0') + a[i];
		for(int j = 0; j < k; j++){// k bits
			if(a[i][j] == '0'){
				if(trie[index].left == -1){
					trie.emplace_back();
					trie[index].left = trie.size() - 1;
				}
				index = trie[index].left;
			}
			else{
				if(trie[index].right == -1){
					trie.emplace_back();
					trie[index].right = trie.size() - 1;
				}
				index = trie[index].right;
			}
		}
	}
	
	int ans = 0;
	for(int i = 0; i < n; i++){
		int cur = 0;
		bool match = true;
		char bit;
		for(int j = 0; j < k; j++){// k bits
			if(a[i][j] == '0'){
				if(trie[cur].right == -1){
					cur = trie[cur].left;
					bit = '0';
				}
				else{
					cur = trie[cur].right;
					bit = '1';
				}
			}
			else{
				if(trie[cur].left == -1){
					cur = trie[cur].right;
					bit = '0';
				}
				else{
					cur = trie[cur].left;
					bit = '1';
				}
			}

			if(bit != v[j]){
				ans += (bit < v[j]);
				match = false;
				break;
			}
		}
		ans += match;
	}

	return ans;
}
