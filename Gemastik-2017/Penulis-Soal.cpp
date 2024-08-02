#include <iostream>
#include <conio.h>

using namespace std;

bool exists(int* arr, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

int main() {
    int T; // banyaknya kasus uji
    cin >> T;

    int* results = new int[T]; // menyimpan hasil untuk setiap kasus uji

    for (int t = 0; t < T; ++t) {
        int N; // banyaknya penulis soal
        cin >> N;

        int* S = new int[N]; // banyaknya soal yang disumbangkan oleh masing-masing penulis
        for (int i = 0; i < N; ++i) {
            cin >> S[i];
        }

        int** C = new int*[N]; // perusahaan-perusahaan tempat penulis bekerja
        int* P = new int[N]; // jumlah perusahaan untuk setiap penulis
        for (int i = 0; i < N; ++i) {
            cin >> P[i];
            C[i] = new int[P[i]];
            for (int j = 0; j < P[i]; ++j) {
                cin >> C[i][j];
            }
        }

        int* pemilik = new int[N * 51]; // alokasi maksimal
        int pemilik_size = 0;

        for (int i = 0; i < N; ++i) {
            if (!exists(pemilik, pemilik_size, -(i + 1))) {
                pemilik[pemilik_size++] = -(i + 1); // menambahkan penulis sebagai pemilik
            }
            for (int j = 0; j < P[i]; ++j) {
                if (!exists(pemilik, pemilik_size, C[i][j])) {
                    pemilik[pemilik_size++] = C[i][j]; // menambahkan perusahaan tempat penulis bekerja sebagai pemilik
                }
            }
        }

        results[t] = pemilik_size; // menyimpan hasil untuk kasus uji ini

        // Deallocate dynamic memory
        delete[] S;
        for (int i = 0; i < N; ++i) {
            delete[] C[i];
        }
        delete[] C;
        delete[] P;
        delete[] pemilik;
    }

    cout << endl;

    // Setelah semua kasus uji diproses, cetak hasilnya
    for (int t = 0; t < T; ++t) {
        cout << results[t] << endl;
    }

    // Deallocate results array
    delete[] results;

    getch();
    return 0;
}

