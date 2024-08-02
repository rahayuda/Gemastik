#include <iostream>
#include <vector>
#include <climits> // Menambahkan header ini untuk LLONG_MAX

using namespace std;

// Fungsi untuk menghitung nilai minimum dari f(i, j)
long long computeMinValue(const vector<int>& A, const vector<int>& B, const vector<int>& C, int N, int M) {
    long long minValue = LLONG_MAX; // Inisialisasi dengan nilai maksimum
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            long long product = static_cast<long long>(A[i]) * B[j];
            int modIndex = product % M;
            long long f_ij = product + C[modIndex];
            minValue = min(minValue, f_ij);
        }
    }
    
    return minValue;
}

int main() {
    int T;
    cin >> T;
    
    vector<long long> results; // Menyimpan hasil untuk setiap kasus uji
    
    while (T--) {
        int N, M;
        cin >> N >> M;
        
        vector<int> A(N), B(N), C(M);
        
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        
        for (int i = 0; i < N; ++i) {
            cin >> B[i];
        }
        
        for (int i = 0; i < M; ++i) {
            cin >> C[i];
        }
        
        long long result = computeMinValue(A, B, C, N, M);
        results.push_back(result); // Menyimpan hasil ke dalam vector results
    }
    
    // Menampilkan semua hasil setelah semua kasus uji selesai
    for (const long long& result : results) {
        cout << result << endl;
    }
    
    return 0;
}