#include "p1_5.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#define pii pair<int, int>
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

struct Board{
	vector<string>cells;
	vector<pii>selected;
};

bool in(const int r, const int c, const int K){
	return r >= 0 && r < K && c >= 0 && c < K;
}
bool check(vector<int>&row_check, vector<int>&col_check, const int K) {
    for (int i = 0; i < K; i++) {
        if (!row_check[i] || !col_check[i]) return false;
    }
    return true;
}

void fill_neighbor(vector<Board>&boards, vector<string> &board, 
 vector<pii>&list, vector<int>&row_check, vector<int>&col_check, 
 vector<string>s, int fillable, const int to_fill, const int K) {
	if(!to_fill){
		if (check(row_check, col_check, K)){
			// print_board(board);
			boards.push_back({board, list});
		}
		return;
    }

	if(fillable < to_fill)
		return;

	int len = list.size();
	for(int i = 0; i < len; i++){
		int r = list[i].first, c = list[i].second;
		for(int d = 0; d < 4; d++){
			int nr = r + dr[d], nc = c + dc[d];
			if(in(nr, nc, K) && s[nr][nc] == '.' && board[nr][nc] == '0'){
				list.push_back({nr, nc});
				board[nr][nc] = '1';
				bool prev_row = row_check[nr];
				bool prev_col = col_check[nc];
				row_check[nr] = true;
				col_check[nc] = true;
				fillable--;
				fill_neighbor(boards, board, list, row_check, col_check, s, fillable, to_fill - 1, K);
				row_check[nr] = prev_row;
				col_check[nc] = prev_col;
				board[nr][nc] = '0';
				list.pop_back();
				s[nr][nc] = 'x';
			}
		}
	}
}

int count_fillable(vector<string>&s, const int K){
	int fillable = 0;
	for (int r = 0; r < K; r++) {
        for (int c = 0; c < K; c++) {
			fillable += (s[r][c] == '.');
		}
	}
	return fillable;
}

void find_first(vector<Board>&boards, vector<string> &board, 
 vector<string>&s, const int n, const int K) {
	int fillable = count_fillable(s, K);
	if(fillable < n)
		return;

	vector<int>row_check(K, 0), col_check(K, 0);
	const int kk = K * K;
	int index = 0;
    for (int r = 0; r < K; r++) {
        for (int c = 0; c < K; c++, index++) {
			if(index + n > kk || fillable < n) 
				return;
            if (s[r][c] == '.') {
                // cout << "start from (" << r << ", " << c << ")\n";
				board[r][c] = '1';
                bool prev_row = row_check[r];
				bool prev_col = col_check[c];
				row_check[r] = true;
				col_check[c] = true;

				vector<pii>list{{r, c}};
				fillable--;
				fill_neighbor(boards, board, list, row_check, col_check, s, fillable, n - 1, K);

                board[r][c] = '0';
                row_check[r] = prev_row;
				col_check[c] = prev_col;
				// cout << "leave (" << r << ", " << c << ")\n\n";
				s[r][c] = 'x';
            }
        }
    }
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
	vector<Board>boards;

	find_first(boards, board, s, n, K);

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
