/**
 * @file 1442D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-09
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

#define maxn 3005

int64_t ans = 0;
vector<int> a[maxn];
int64_t sum[maxn], siz[maxn];
vector<int64_t> f;

void dfs(int l, int r) {
    if (l == r) {
        int64_t sum = 0;
        ans = max(ans, f.back());
        for (int i = (int)f.size() - 2, j = 0; ~i && j < (int)a[l].size(); i--, j++)
            ans = max(ans, f[i] + (sum += a[l][j]));
        return;
    }
    int mid = (l + r) >> 1;
    vector<int64_t> g = f;
    for (int i = mid + 1; i <= r; i++)
        for (int j = (int)f.size() - 1; j - siz[i] >= 0; j--) f[j] = max(f[j], f[j - siz[i]] + sum[i]);
    dfs(l, mid);
    f = g;
    for (int i = l; i <= mid; i++)
        for (int j = (int)f.size() - 1; j - siz[i] >= 0; j--) f[j] = max(f[j], f[j - siz[i]] + sum[i]);
    dfs(mid + 1, r);
    return;
}

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> siz[i], a[i].resize(siz[i]);
        for (int j = 0; j < siz[i]; j++) cin >> a[i][j], sum[i] += a[i][j];
    }
    f.resize(k + 1), dfs(1, n);
    cout << ans << endl;
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