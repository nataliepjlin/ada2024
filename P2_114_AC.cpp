#include "p1_4.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm> 
using namespace std;
#define pii pair<int, int>
void rotate_90(vector<string>&A, int &row, int &col){
    vector<string>rotated;
    for(int i = 0; i < col; i++){
        string new_row = "";
        for(int j = row - 1; j >= 0; j--){
            new_row += A[j][i];
        }
        // cout << new_row << endl;
        rotated.push_back(new_row);
    }
    A = rotated;
    return;
}
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
void flip(vector<string>&A, int &row, int &col){
    for(int i = row - 1; i >= 0; i--){
        reverse(A[i].begin(), A[i].end()); 
    }
    return;
}
bool compare_polyominoes(std::vector<std::string>& A, std::vector<std::string>& B){
    int row = A.size(), col = A[0].size();
    int b_row = row, b_col = col;
    vector<pii> B_in_B = rep_a_to_b(B, b_row, b_col);
    for(int i = 0; i < 4; i++){
        if(b_row == row){
            vector A_in_B = rep_a_to_b(A, row, col);
            if(A_in_B == B_in_B) return true;
        }
        rotate_90(A, row, col);
        swap(row, col);
    }
    flip(A, row, col);
    for(int i = 0; i < 4; i++){
        if(b_row == row){
            vector A_in_B = rep_a_to_b(A, row, col);
            if(A_in_B == B_in_B) return true;
        }
        rotate_90(A, row, col);
        swap(row, col);
    }
    return false;
}

