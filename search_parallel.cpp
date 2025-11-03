#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int parallelBinarySearch(vector<int>& arr, int x, int num_threads) {
    int n = arr.size();
    int found_index = -1;
    bool found = false;

    #pragma omp parallel num_threads(num_threads) shared(found_index, found)
    {
        int tid = omp_get_thread_num();
        int chunk = n / num_threads;
        int start = tid * chunk;
        int end = (tid == num_threads - 1) ? n - 1 : start + chunk - 1;

        if (x >= arr[start] && x <= arr[end]) {
            int l = start, r = end;
            while (l <= r && !found) {
                int mid = l + (r - l) / 2;
                if (arr[mid] == x) {
                    found = true;
                    found_index = mid;
                } else if (arr[mid] < x) l = mid + 1;
                else r = mid - 1;
            }
        }
    }
    return found_index;
}

int main() {
    int n = 1000000; 
    int x = 500000;    
    int num_threads = 4;
    vector<int> arr(n);

    for (int i = 0; i < n; i++) arr[i] = i;  

    double start = omp_get_wtime();  
    int result = parallelBinarySearch(arr, x, num_threads);
    double end = omp_get_wtime();   

    if (result != -1)
        cout << "Elemento encontrado en índice: " << result << endl;
    else
        cout << "Elemento no encontrado." << endl;

    cout << "Tiempo total (secuencial): " << (end - start) << " segundos\n";

    return 0;
}