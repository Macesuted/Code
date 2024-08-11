/**
 * @file abc366_g.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 65

int64_t F[maxn], G[maxn], a[maxn], lis[maxn];
int pos[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, F[x - 1] |= (int64_t)1 << (y - 1), F[y - 1] |= (int64_t)1 << (x - 1);
    for (int i = 0; i < n; i++) {
        if (a[i]) continue;
        for (int j = 0; j < n; j++)
            if (i != j) {
                int k = j - (j > i);
                G[k] = F[j], lis[k] = (int64_t)1 << j;
            }
        for (int i = 0, c = 0; i < n; i++) {
            pos[i] = -1;
            int p = c;
            while (p < n - 1 && !(G[p] >> i & 1)) p++;
            if (p == n - 1) continue;
            swap(G[c], G[p]), swap(lis[c], lis[p]), pos[i] = c;
            for (int j = 0; j < n - 1; j++)
                if (j != c && G[j] >> i & 1) G[j] ^= G[c], lis[j] ^= lis[c];
            c++;
        }
        int64_t v = F[i], S = (int64_t)1 << i;
        for (int j = 0; j < n - 1; j++) {
            if (!(v >> j & 1)) continue;
            if (pos[j] == -1) return cout << "No" << endl, void();
            v ^= G[pos[j]], S ^= lis[pos[j]];
        }
        for (int j = 0; j < n; j++)
            if (S >> j & 1) a[j] |= (int64_t)1 << i;
    }
    cout << "Yes" << endl;
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << endl;
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