#include "p1_4.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm> 
using namespace std;
#define pii pair<int, int>
vector<pii> rep_a_to_b(vector<string>&A, int &row, int &col){
    vector<pii>b;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(A[i][j] == '1'){
                b.push_back({i, j});
                // cout << "(" << i << ", " << j << "), ";
            }
        }
    }
    // cout << endl;
    return b;
}
bool compare_polyominoes(std::vector<std::string>& A, std::vector<std::string>& B){
    int row = A.size(), col = A[0].size();
    int b_row = row, b_col = col;
    vector<pii> B_in_B = rep_a_to_b(B, b_row, b_col);
    
    const int to_check = B_in_B.size();
    bool r0 = true, r0_f = true,
    r90 = (row == col), r90_f = r90,
    r180 = true, r180_f = true,
    r270 = r90, r270_f = r90;
    for(int i = 0; i < to_check 
    && (r0 || r0_f || r90 || r90_f || r180 || r180_f || r270 || r270_f); i++){
        int a = B_in_B[i].first, b = B_in_B[i].second;

        r0 = r0 && (A[a][b] == '1');
        r0_f = r0_f && (A[a][col - 1 - b] == '1');

        r90 = r90 && (A[b][row - 1 - a] == '1');
        r90_f = r90_f && (A[b][a] == '1');

        r180 = r180 && (A[row - 1 - a][col - 1 - b] == '1');
        r180_f = r180_f && (A[row - 1 - a][b] == '1');

        r270 = r270 && (A[col - 1 - b][a] == '1');
        r270_f = r270_f && (A[col - 1 - b][row - 1 - a] == '1');
    }

    return (r0 || r0_f || r90 || r90_f || r180 || r180_f || r270 || r270_f);
}

