#include "p1_5.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#define pii pair<int, int>
enum DIR{UP, RIGHT, DOWN, LEFT};
const string new_content[] = {"0010", "0001", "1000", "0100"};
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};
const int parent_location[] = {DOWN, LEFT, UP, RIGHT};


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
bool is_polyomino(vector<string> &board, vector<bool>&row_check, vector<bool>&col_check, const int n, const int K){
	for(int i = 0; i < K; i++){
		if(!row_check[i] || !col_check[i]) return false;
	}

	vector<vector<bool>>visited(K, vector<bool>(K, false));
	for(int r = 0; r < K; r++){
		for(int c = 0; c < K; c++){
			if(board[r][c] == '1'){
				int count = 0;
				visited[r][c] = true;
				dfs(count, board, r, c, K, visited);
				return count == n;
			}
		}
	}
	return false;
}
void fill_board(vector<vector<string>>&boards, vector<string> &board, 
vector<bool>&row_check, vector<bool>&col_check,
vector<string>&s, int to_fill, const int n, int idx, const int K){
	if(!to_fill && is_polyomino(board, row_check, col_check, n, K)){
		boards.push_back(board);
		return;
	}
	if(idx + to_fill > K * K || idx == K * K) return;

	const int r = idx / K, c = idx % K;
	if(s[r][c] == '.'){
		board[r][c] = '1';
		bool prev_row = row_check[r];
		bool prev_col = col_check[c];
		row_check[r] = true;
		col_check[c] = true;
		fill_board(boards, board, row_check, col_check, s, to_fill - 1, n, idx + 1, K);
		row_check[r] = prev_row;
		col_check[c] = prev_col;
	}
	board[r][c] = '0';
	fill_board(boards, board, row_check, col_check, s, to_fill, n, idx + 1, K);
}

#define pii pair<int, int>
vector<pii> rep_a_to_b(vector<string> &board, int &row, int &col){
    vector<pii>b;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(board[i][j] == '1'){
                b.push_back({i, j});
            }
        }
    }
    return b;
}
bool compare_polyominoes(vector<string> &A, vector<pii>&B, const int K){
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
	vector<string> board(K, string(K, '0'));
	vector<vector<string>>boards;
	vector<bool>row_check(K), col_check(K);
	fill_board(boards, board, row_check, col_check, s, n, n, 0, K);

	int count = boards.size();
	const int boards_size = count;
	// cout << "boards_size = " << boards_size << endl;

	vector<bool>skip(boards_size, false);
	for(int i = 0; i < boards_size; i++){
		if(skip[i]) continue;
		vector<pii> b = rep_a_to_b(boards[i], K, K);
		const int to_check = b.size();
		for(int j = i + 1; j < boards_size; j++){
			if(skip[j]) continue;
			if(compare_polyominoes(boards[j], b, K)){
				count--;
				skip[j] = true;
			}
		}
	}

	// for(int i = 0; i < boards_size; i++){
	// 	if(!skip[i]){
	// 		for(int r = 0; r < K; r++){
	// 			cout << boards[i][r] << endl;
	// 		}
	// 		cout << endl;
	// 	}
	// }

	return count;
}
