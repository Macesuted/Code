#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 105

int m[maxn], lef[maxn], rig[maxn];

bool mem2;

int main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n) {
        int len = 2 * n - 1;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < i; j++) cout << ' ';
            cout << 'V';
            for (int j = i + 1; j + i <= len; j++) cout << ' ';
            cout << 'V' << endl;
        }
        for (int i = 1; i < n; i++) cout << ' ';
        cout << 'V' << endl;
    }
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}