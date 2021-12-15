#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 105

int m[maxn], lef[maxn], rig[maxn];

bool mem2;

int main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    ios::sync_with_stdio(false);
    int n, k;
    while (cin >> n >> k) {
        for (int i = 0; i < k; i++) cin >> m[i];
        for (int i = 0; i < n; i++) lef[i] = i - 1, rig[i] = i + 1;
        rig[n - 1] = 0, lef[0] = n - 1;
        int p = 0;
        for (int t = 1, mp = 0; t < n; p = rig[p], t++, mp = (mp + 1) % k) {
            int x = m[mp] - 1;
            while (x--) p = rig[p];
            lef[rig[lef[p]] = rig[p]] = lef[p];
        }
        cout << p << endl;
    }
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}