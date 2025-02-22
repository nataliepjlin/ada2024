#include "p2_6.h"
#include <vector>
#include <string>
#include <algorithm>
struct Node {
	Node *left = nullptr;
	Node *right = nullptr;
};
void destroy_trie(Node *node){
	if(node == nullptr) return;
	destroy_trie(node->left);
	destroy_trie(node->right);
	delete node;
}
int solve(int n, int k, std::string v, std::vector<std::string> a) {
	// build trie
	Node *root = new Node;

	v = std::string(k - std::min(k, (int)v.length()), '0') + v;

	for(int i = 0; i < n; i++){
		Node *cur = root;
		a[i] = std::string(k - std::min(k, (int)a[i].length()), '0') + a[i];
		for(int j = 0; j < k; j++){// k bits
			if(a[i][j] == '0'){
				if(cur->left == nullptr){
					cur->left = new Node;
				}
				cur = cur->left;
			}
			else{
				if(cur->right == nullptr){
					cur->right = new Node;
				}
				cur = cur->right;
			}
		}
	}
	
	int ans = 0;
	Node *cur;
	char bit;
	bool match;
	for(int i = 0; i < n; i++){
		cur = root;
		match = true;
		for(int j = 0; j < k && cur != nullptr; j++){// k bits
			if(a[i][j] == '0'){
				if(cur->right == nullptr){
					cur = cur->left;
					bit = '0';
				}
				else{
					cur = cur->right;
					bit = '1';
				}
			}
			else{
				if(cur->left == nullptr){
					cur = cur->right;
					bit = '0';
				}
				else{
					cur = cur->left;
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

	destroy_trie(root);

	return ans;
}
