#include <iostream>
#include <stdio.h>
#include <vector>
#include <omp.h>
#include <math.h>
#include <algorithm>
#include <time.h>
using namespace std;

void sortRow(vector<vector<int>>& M, int row, bool ascending) {
    sort(M[row].begin(), M[row].end());
    if (ascending) sort(M[row].begin(), M[row].end());
    else sort(M[row].rbegin(), M[row].rend());
}

void sortColumn(vector<vector<int>>& M, int col) {
    int n = M.size();
    vector<int> tmp(n);
    for (int i = 0; i < n; ++i){
        tmp[i] = M[i][col];
    } 
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < n; ++i){
        M[i][col] = tmp[i];
    }
}


void shearSortParallel(vector<vector<int>>& M) {
    int n = M.size();
    int rounds = log2(n) + 1;

    for (int r = 0; r < rounds; ++r) {
        #pragma omp parallel for
        for (int i = 0; i < n; ++i)
            sortRow(M, i, i % 2 == 0);

        #pragma omp parallel for
        for (int j = 0; j < n; ++j)
            sortColumn(M, j);
    }
}



int main() {
    int n = 4,numi,i,j;
    vector<vector<int>> M(n, vector<int>(n));
    
    vector<int> nums(100);
    for (int i = 0; i < 100; i++) nums[i] = i;

    srand(time(0));
    random_shuffle(nums.begin(), nums.end());

    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = nums[k++];
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
    double start = omp_get_wtime();
    shearSortParallel(M);
    double end = omp_get_wtime();

    cout << "\nTiempo total (paralelo): " << (end - start) << " segundos\n\n";
    cout << endl;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}
