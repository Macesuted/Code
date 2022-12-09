/**
 * @file 3148.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 2005
#define mod 1000000007

int f[maxn][maxn];

int Mod(int a) { return a >= mod ? a - mod : a; }
int Add(int &a, int b) { return a = Mod(a + b); }

void solve(void) {
    int n, S, T;
    cin >> n >> S >> T;
    f[1][1] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j < i; j++) {
            int64_t v = f[i - 1][j], cnt = (i > S) + (i > T);
            if (!v) continue;
            if (i == S || i == T)
                Add(f[i][j + 1], v), Add(f[i][j], v);
            else
                Add(f[i][j + 1], v * (j + 1 - cnt) % mod), Add(f[i][j - 1], v * (j - 1) % mod);
        }
    cout << f[n][1] << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}