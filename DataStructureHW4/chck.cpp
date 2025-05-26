#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<string> v[5];
const string filenames[5] = {
    "bubble_sort.out",
    "insert_sort.out",
    "quick_sort.out",
    "merge_sort.out",
    "heap_sort.out"
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 파일에서 데이터 읽기
    for (int k = 0; k < 5; k++) {
        ifstream fin(filenames[k]);

        string s;
        for (int i = 0; i < 50000; i++) {
            fin >> s;
            v[k].push_back(s);
        }
        fin.close();
    }

    int error = 0;
    for (int i = 0; i < 50000; i++) {
        for (int j = 0; j < 4; j++) {
            if (v[j][i] != v[j + 1][i]) {
                cout << "Wrong with " << j << " " << i << "\n";
                error++;
            }
        }
        if (i != 49999) {
            for (int j = 0; j < 5; j++) {
                if (v[j][i] > v[j][i + 1]) {
                    cout << "Wrong Sort with " << j << " " << i << "\n";
                    error++;
                }
            }
        }
    }

    if (!error) cout << "Good\n";
    return 0;
}
