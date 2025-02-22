#include "p1_5.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};
 
struct Board{
	vector<string>cells;
	vector<pair<int, int>>selected;
};
int count_fillable(vector<string>&s, const int K){
	int fillable = 0;
	for (int r = 0; r < K; r++) {
        for (int c = 0; c < K; c++) {
			fillable += (s[r][c] == '.');
		}
	}
	return fillable;
}

bool in(const int r, const int c, const int K){
	return r >= 0 && r < K && c >= 0 && c < K;
}

void dfs(int &count, vector<string> &board, int r, int c, const int K, vector<vector<bool>>&visited){
	count++;
	for(int i = 0; i < 4; i++){
		int nr = r + dr[i], nc = c + dc[i];
		if(in(nr, nc, K) && board[nr][nc] == '1' && !visited[nr][nc]){
			visited[nr][nc] = true;
			dfs(count, board, nr, nc, K, visited);
		}
	}
}

bool check(vector<bool>&row_check, vector<bool>&col_check, const int K, vector<string>&board, const int n, const pair<int, int>&start) {
    for (int i = 0; i < K; i++) {
        if (!row_check[i] || !col_check[i]) return false;
    }

	int count = 0;
	vector<vector<bool>>visited(K, vector<bool>(K, false));
	const int r = start.first, c = start.second;
	visited[r][c] = true;
	dfs(count, board, r, c, K, visited);
    return count == n;
}

void print_board(vector<string>&board){
	for(string &row: board){
		cout << row << endl;
	}
	cout << endl;
}

void fill_neighbor(vector<Board>&boards, vector<string>&board, vector<vector<int>> &num_board, 
 vector<pair<int, int>>&nums_loc, const int cur_num, const int upperleft,
 vector<pair<int, int>>&list, vector<bool>&row_check, vector<bool>&col_check, 
 vector<string>s, int fillable, const int to_fill, const int n, const int K) {
	const int r = nums_loc[cur_num].first, c = nums_loc[cur_num].second;
	int num = nums_loc.size();
 
	if(!to_fill){
		if (check(row_check, col_check, K, board, n, list[0])){
			// print_board(board);
			boards.push_back({board, list});
		}
		return;
    }
 
	if(fillable < to_fill) return;
	
	for(int d = 0; d < 4; d++){//mark adjacent cells
		int nr = r + dr[d], nc = c + dc[d];
		if(in(nr, nc, K) && nr * K + nc > upperleft 
		&& s[nr][nc] == '.' && num_board[nr][nc] == -1){
			num_board[nr][nc] = num;
			num++;
			nums_loc.push_back({nr, nc});
		}
	}
 
	for(int i = cur_num + 1; i < num; i++){//visit next
		int a = nums_loc[i].first, b = nums_loc[i].second;
 
		list.push_back(nums_loc[i]);
		bool prev_row = row_check[a];
		bool prev_col = col_check[b];
		row_check[a] = true;
		col_check[b] = true;
		board[a][b] = '1';
		fillable--;
 
		fill_neighbor(boards, board, num_board, nums_loc, i, upperleft, list, row_check, col_check, s, fillable, to_fill - 1, n, K);
 
		board[a][b] = '0';
		row_check[a] = prev_row;
		col_check[b] = prev_col;
		list.pop_back();
	}
}
 
 
void find_first(vector<Board>&boards, vector<string>&board, 
 vector<string>&s, const int n, const int K, int fillable) {
 
	vector<bool>row_check(K, false), col_check(K, false);
	const int kk = K * K;
	int index = 0;
 
    for (int r = 0; r < K; r++) {
        for (int c = 0; c < K; c++, index++) {
			if(index + n > kk || fillable < n) return;
 
            if (s[r][c] == '.') {
                // cout << "start from (" << r << ", " << c << ")\n";
 
				vector<vector<int>> num_board(K, vector<int>(K, -1));
				num_board[r][c] = 0;
				board[r][c] = '1';
 
				row_check[r] = true;
				col_check[c] = true;
 
				vector<pair<int, int>>list{{r, c}};
				vector<pair<int, int>>nums_loc{{r, c}};
				fillable--;
				fill_neighbor(boards, board, num_board, nums_loc, 0, index, list, row_check, col_check, s, fillable, n - 1, n, K);
 
				board[r][c] = '0';
                row_check[r] = false;
				col_check[c] = false;
				// cout << "leave (" << r << ", " << c << ")\n";
            }
        }
    }
}
 
bool compare_polyominoes(vector<string> &A, vector<pair<int, int>>&B, const int K){
    const int to_check = B.size();
    bool r0 = true, r0_f = true,
    r90 = true, r90_f = true,
    r180 = true, r180_f = true,
    r270 = true, r270_f = true;
 
    for(int i = 0; i < to_check 
    && (r0 || r0_f || r90 || r90_f || r180 || r180_f || r270 || r270_f); i++){
        int a = B[i].first, b = B[i].second;
 
		r0 = r0 && (A[a][b] == '1');
        r0_f = r0_f && (A[a][K - 1 - b] == '1');
 
        r90 = r90 && (A[b][K - 1 - a] == '1');
        r90_f = r90_f && (A[b][a] == '1');
 
        r180 = r180 && (A[K - 1 - a][K - 1 - b] == '1');
        r180_f = r180_f && (A[K - 1 - a][b] == '1');
 
        r270 = r270 && (A[K - 1 - b][a] == '1');
        r270_f = r270_f && (A[K - 1 - b][K - 1 - a] == '1');
 
    }
    return (r0 || r0_f || r90 || r90_f || r180 || r180_f || r270 || r270_f);
}
 
int count_polyominoes(int n, int K, std::vector<std::string> s) {
	int fillable = count_fillable(s, K);
	if(fillable < n)
		return 0;
 
	vector<string> board(K, string(K, '0'));
	vector<Board>boards;
 
	find_first(boards, board, s, n, K, fillable);
 
	int count = boards.size();
	const int boards_size = count;
	// cout << "boards_size = " << boards_size << endl;
 
	vector<bool>skip(boards_size, false);
	for(int i = 0; i < boards_size; i++){
		if(skip[i]) continue;
 
		for(int j = i + 1; j < boards_size; j++){
			if(skip[j]) continue;
			if(compare_polyominoes(boards[j].cells, boards[i].selected, K)){
				count--;
				skip[j] = true;
			}
		}
	}
 
	return count;
}