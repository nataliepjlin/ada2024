#include "p2_6.h"
#include <vector>
#include <string>
struct Node {
	int val;
	Node *left = nullptr;
	Node *right = nullptr;
	Node(int c){
		val = c;
	}
};
void destroy_trie(Node *node){
	if(node == nullptr) return;
	destroy_trie(node->left);
	destroy_trie(node->right);
	delete node;
}
int solve(int n, int k, std::string v, std::vector<std::string> a) {
	// build trie
	Node *root = new Node(-1);
	for(int i = 0; i < n; i++){
		Node *cur = root;
		for(int j = 0; j < k; j++){// k bits
			if(a[i][j] == '0'){
				if(cur->left == nullptr){
					cur->left = new Node(0);
				}
				cur = cur->left;
			}
			else{
				if(cur->right == nullptr){
					cur->right = new Node(1);
				}
				cur = cur->right;
			}
		}
	}
	
	int ans = 0;
	for(int i = 0; i < n; i++){
		Node *cur = root;
		std::string res = "";
		for(int j = 0; j < k; j++){// k bits
			if(a[i][j] == '0'){
				if(cur->right == nullptr){
					cur = cur->left;
					res += '0';
				}
				else{
					cur = cur->right;
					res += '1';
				}
			}
			else{
				if(cur->left == nullptr){
					cur = cur->right;
					res += '0';
				}
				else{
					cur = cur->left;
					res += '1';
				}
			}
		}

		if(res <= v){
			ans++;
		}
	}

	destroy_trie(root);

	return ans;
}
