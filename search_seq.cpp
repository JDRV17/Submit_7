#include<vector>
#include<iostream>
#include <omp.h>

using namespace std;

int binarySearch(vector<int>& arr, int x) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == x) return mid;
        else if (arr[mid] < x) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    int n = 1000000; 
    int x = 500000; 
    vector<int> arr(n);

    for (int i = 0; i < n; i++) arr[i] = i;  

    double start = omp_get_wtime();  
    int result = binarySearch(arr, x);
    double end = omp_get_wtime();    

    if (result != -1)
        cout << "Elemento encontrado en índice: " << result << endl;
    else
        cout << "Elemento no encontrado." << endl;

    cout << "Tiempo total (secuencial): " << (end - start) << " segundos\n";

    
    return 0;
}