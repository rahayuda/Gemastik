#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000000007;

int countValidGrids(const string& S, int N, int K) {
    int L = S.length();
    
    // Jika panjang string lebih dari total sel dalam petakata
    if (L > 2 * N) return 0;

    // DP array
    vector<vector<vector<long long>>> dp(2, vector<vector<long long>>(N, vector<long long>(L, 0)));
    
    // Inisialisasi DP untuk panjang substring 1
    for (int j = 0; j < N; ++j) {
        dp[0][j][0] = 1; // Mengisi baris pertama
        dp[1][j][0] = 1; // Mengisi baris kedua
    }

    // Mengisi DP untuk panjang substring 2 hingga L
    for (int len = 1; len < L; ++len) {
        vector<vector<vector<long long>>> new_dp(2, vector<vector<long long>>(N, vector<long long>(L, 0)));
        
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < N; ++j) {
                if (dp[i][j][len - 1] > 0) {
                    // Tentukan karakter yang akan diteruskan
                    char charToMatch = S[len];
                    
                    // Arahkan pergerakan
                    for (int di = -1; di <= 1; ++di) {
                        for (int dj = -1; dj <= 1; ++dj) {
                            if ((di == 0 && dj == 0) || (i + di < 0) || (i + di >= 2) || (j + dj < 0) || (j + dj >= N)) continue;
                            new_dp[i + di][j + dj][len] = (new_dp[i + di][j + dj][len] + dp[i][j][len - 1]) % MOD;
                        }
                    }
                }
            }
        }
        dp = move(new_dp);
    }

    // Hitung total jumlah petakata yang valid
    long long totalCount = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < N; ++j) {
            totalCount = (totalCount + dp[i][j][L - 1]) % MOD;
        }
    }

    return totalCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        string S;
        int N, K;
        cin >> S >> N >> K;
        
        cout << countValidGrids(S, N, K) << '\n';
    }
    
    return 0;
}
