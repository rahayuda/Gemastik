#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int MOD = 1000000007;
const int MAX_R = 50;
const int MAX_C = 50;

// Menghitung jarak minimum dari setiap meja mahasiswa ke semua stop kontak di baris pertama
vector<vector<int>> calculateMinDistances(const vector<vector<int>>& G, int R, int C) {
    vector<vector<int>> minDist(R, vector<int>(C, INT_MAX));
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    queue<pair<int, int>> q;

    // Initialize queue with all stop contacts in the first row
    for (int j = 0; j < C; ++j) {
        minDist[0][j] = 0;
        q.push({0, j});
    }

    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        for (auto& dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;
            if (newRow >= 0 && newRow < R && newCol >= 0 && newCol < C) {
                int diff = abs(G[row][col] - G[newRow][newCol]);
                if (minDist[newRow][newCol] > minDist[row][col] + 1 + diff) {
                    minDist[newRow][newCol] = minDist[row][col] + 1 + diff;
                    q.push({newRow, newCol});
                }
            }
        }
    }

    return minDist;
}

// Menghitung tingkat kesemrawutan untuk seluruh kemungkinan konfigurasi
int calculateDisorderLevel(const vector<vector<int>>& G, int R, int C, const vector<pair<int, int>>& students) {
    vector<vector<int>> minDist = calculateMinDistances(G, R, C);
    vector<int> distToContacts(students.size());
    
    // Menghitung jarak minimum ke setiap stop kontak
    for (int i = 0; i < students.size(); ++i) {
        int row = students[i].first;
        int col = students[i].second;
        int minEff = INT_MAX;
        for (int j = 0; j < C; ++j) {
            minEff = min(minEff, minDist[row][j]);
        }
        distToContacts[i] = minEff;
    }

    sort(distToContacts.begin(), distToContacts.end());
    int result = 0;

    // Menghitung tingkat kesemrawutan untuk semua konfigurasi teratur
    do {
        int maxDist = 0;
        for (int i = 0; i < distToContacts.size(); ++i) {
            maxDist = max(maxDist, distToContacts[i]);
        }
        result = (result + maxDist) % MOD;
    } while (next_permutation(distToContacts.begin(), distToContacts.end()));

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int R, C, N;
        cin >> R >> C >> N;

        vector<vector<int>> G(R, vector<int>(C));
        vector<pair<int, int>> students;

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> G[i][j];
                if (G[i][j] < 0) {
                    students.push_back({i, j});
                }
            }
        }

        cout << calculateDisorderLevel(G, R, C, students) << '\n';
    }

    return 0;
}
