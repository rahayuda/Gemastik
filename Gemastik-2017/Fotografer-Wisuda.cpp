#include <iostream>
#include <conio.h>
#include <cstring> // Untuk strcpy

#define MAX_RESULTS 100 // Asumsi bahwa jumlah kasus uji tidak melebihi 100
#define MAX_LENGTH 1000 // Asumsi bahwa panjang string tidak melebihi 1000 karakter

using namespace std;

void solve(int A, int B, int K, char results[][MAX_LENGTH], int& resultCount) {
    // Cek kondisi mustahil
    if (A > 2 * (B + 1) || B > K * (A + 1)) {
        strcpy(results[resultCount], "mustahil");
        ++resultCount;
        return;
    }

    // Jika tidak ada teman laki-laki
    if (A == 0) {
        if (B <= K) {
            for (int i = 0; i < B; ++i) {
                results[resultCount][i] = 'P';
            }
            results[resultCount][B] = '\0'; // Null-terminate string
            ++resultCount;
        } else {
            strcpy(results[resultCount], "mustahil");
            ++resultCount;
        }
        return;
    }

    // Jika tidak ada teman perempuan
    if (B == 0) {
        if (A <= 2) {
            for (int i = 0; i < A; ++i) {
                results[resultCount][i] = 'L';
            }
            results[resultCount][A] = '\0'; // Null-terminate string
            ++resultCount;
        } else {
            strcpy(results[resultCount], "mustahil");
            ++resultCount;
        }
        return;
    }

    int R=0, total = A + B;
    char* result = new char[total + 1]; // +1 untuk null-terminator
    int index = 0;
    result[total] = '\0'; // Null-terminate string

    if (A>=B && A<=(2*(B + 1)))
    {
	 	R = 2; 
		K = 1; 
    }

    if (B>=A && B<=(K * A))
    {
		R = 1; 
		K = K; 
    }

    if (B>A && B<=(K * A) && (A-(B/3))>2)
    {
		R = 1; 
		K = 2; 
    }

    while (A > 0 || B > 0) {
        int countL = 0;
        int countP = 0;

        // Tambahkan hingga 2 L laki-laki jika memungkinkan
        while (A > 0 && countL < R) {
            result[index++] = 'L';
            A--;
            countL++;
        }

        // Tambahkan hingga K P perempuan jika memungkinkan
        while (B > 0 && countP < K) {
            result[index++] = 'P';
            B--;
            countP++;
        }

        // Jika masih ada L dan tidak ada P yang ditambahkan, tambahkan satu L jika perlu
        if (countP == 0 && countL > 0 && A > 0) {
            result[index++] = 'L';
            A--;
        }

        // Jika masih ada P dan tidak ada L yang ditambahkan, tambahkan satu P jika perlu
        if (countL == 0 && countP > 0 && B > 0) {
            result[index++] = 'P';
            B--;
        }
    }

    // Periksa apakah semua A dan B sudah digunakan
    if (A == 0 && B == 0) {
        for (int i = 0; i < total; ++i) {
            results[resultCount][i] = result[i];
        }
        results[resultCount][total] = '\0'; // Null-terminate string
    } else {
        strcpy(results[resultCount], "mustahil");
    }
    ++resultCount;

    delete[] result;
}

int main() {
    int T;
    cin >> T;

    char results[MAX_RESULTS][MAX_LENGTH];
    int resultCount = 0;

    for (int i = 0; i < T; ++i) {
        int A, B, K;
        cin >> A >> B >> K;
        solve(A, B, K, results, resultCount);
    }

    // Output semua hasil
    for (int i = 0; i < resultCount; ++i) {
        cout << results[i] << endl;
    }

    getch();
}
