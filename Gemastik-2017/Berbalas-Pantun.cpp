#include <iostream>
#include <conio.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    int A[100000], B[100000];

    // Membaca input untuk array A
    for(int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    // Membaca input untuk array B
    for(int i = 0; i < N; ++i) {
        cin >> B[i];
    }

    long totalTime = 0;

    // Menghitung total waktu untuk semua pasangan
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            totalTime = totalTime + A[i] + B[j];
        }
    }

    cout << totalTime << endl;

    getch();
}

