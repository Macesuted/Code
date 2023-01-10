/**
 * @file 2749.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

vector<int> prime;
bool vis[maxn];
int f[maxn];

void solve(void) {
    int n;
    cin >> n;
    int64_t ans = 0;
    bool fnd = false;
    while (n--) {
        int p, q;
        cin >> p >> q, ans += (int64_t)f[p] * q;
        if (p == 2) fnd = true;
    }
    cout << ans + (!fnd) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    f[1] = 1;
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) prime.push_back(i), f[i] = f[i - 1];
        for (auto j = prime.begin(); i * *j < maxn; j++) {
            vis[i * *j] = true, f[i * *j] = f[i] + f[*j];
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}