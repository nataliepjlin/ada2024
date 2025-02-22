#include "p1_5.h"
#include <vector>
#include <string>
#include <iostream>
#include <set>
using namespace std;
using pii = pair<int, int>;
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};
bool in(const int r, const int c, const int K){
	return r >= 0 && r < K && c >= 0 && c < K;
}
bool check(vector<int>&row_check, vector<int>&col_check, const int K, vector<vector<pii>>lists, set<vector<pii>>&boards) {
    for (int i = 0; i < K; i++) {
        if (!row_check[i] || !col_check[i]) return false;
    }

	for(int i = 0; i < 8; i++){
		sort(lists[i].begin(), lists[i].end());
		if(boards.find(lists[i]) != boards.end()) return false;
	}
	
	boards.insert(lists[0]);
    return true;
}

void print_board(vector<string>&board){
	for(string &row: board){
		cout << row << endl;
	}
	cout << endl;
}

void fill_neighbor(set<vector<pii>>&boards, vector<string> &board, 
 vector<vector<pii>>&lists, vector<int>&row_check, vector<int>&col_check, 
 vector<string>s, int fillable, const int to_fill, const int K) {
	if(!to_fill){
		check(row_check, col_check, K, lists, boards);
		return;
    }

	if(fillable < to_fill)
		return;

	int len = lists[0].size();
	for(int i = 0; i < len; i++){
		int r = lists[0][i].first, c = lists[0][i].second;
		for(int d = 0; d < 4; d++){
			int nr = r + dr[d], nc = c + dc[d];
			if(in(nr, nc, K) && s[nr][nc] == '.' && board[nr][nc] == '0'){
				lists[0].push_back({nr, nc});
				lists[1].push_back({nr, K-1-nc});
				lists[2].push_back({nc, K-1-nr});
				lists[3].push_back({nc, nr});
				lists[4].push_back({K-1-nr, K-1-nc});
				lists[5].push_back({K-1-nr, nc});
				lists[6].push_back({K-1-nc, nr});
				lists[7].push_back({K-1-nc, K-1-nr});

				board[nr][nc] = '1';
				bool prev_row = row_check[nr];
				bool prev_col = col_check[nc];
				row_check[nr] = true;
				col_check[nc] = true;
				fillable--;

				fill_neighbor(boards, board, lists, row_check, col_check, s, fillable, to_fill - 1, K);
				
				row_check[nr] = prev_row;
				col_check[nc] = prev_col;
				board[nr][nc] = '0';
				lists[0].pop_back();
				lists[1].pop_back();
				lists[2].pop_back();
				lists[3].pop_back();
				lists[4].pop_back();
				lists[5].pop_back();
				lists[6].pop_back();
				lists[7].pop_back();
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

void find_first(set<vector<pii>>&boards, vector<string> &board, 
 vector<string>&s, const int n, const int K, int fillable) {

	vector<int>row_check(K, 0), col_check(K, 0);
	const int kk = K * K;

	for (int c = 0; c < K; c++) {
		if(c + n > kk || fillable < n) 
			return;
		if (s[0][c] == '.') {
			// cout << "start from (" << r << ", " << c << ")\n";
			board[0][c] = '1';
			row_check[0] = true;
			col_check[c] = true;

			vector<vector<pii>>lists{ {{0,c}},{{0,K-1-c}}, {{c,K-1}},{{c,0}}, {{K-1,K-1-c}},{{K-1,c}}, {{K-1-c,0}},{{K-1-c,K-1}} };
			fillable--;
			fill_neighbor(boards, board, lists, row_check, col_check, s, fillable, n - 1, K);

			board[0][c] = '0';
			row_check[0] = false;
			col_check[c] = false;
			s[0][c] = 'x';
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
	vector<string> board(K, string(K, '0'));
	set<vector<pii>>boards;

	int fillable = count_fillable(s, K);
	if(fillable < n)
		return 0;
	else if(n == 1)
		return 1;
	
	find_first(boards, board, s, n, K, fillable);

	int count = boards.size();
	const int boards_size = count;
	// cout << "boards_size = " << boards_size << endl

	return count;
}
