/**
 * @file 105481G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005
#define maxlgn 22

int k;
int st[maxlgn][maxn], a[maxn], lgLen[maxn];
vector<vector<int>> pos;

int getMax(int l, int r) {
    int t = lgLen[r - l + 1];
    return max(st[t][l], st[t][r - (1 << t) + 1]);
}

int64_t solve(int l, int r) {
    if (l > r) return 0;

    int v = getMax(l, r);

    vector<int> p;
    p.push_back(l - 1);
    for (auto it = lower_bound(pos[v].begin(), pos[v].end(), l); it != pos[v].end() && *it <= r; it++) p.push_back(*it);
    p.push_back(r + 1);

    int64_t ans = 0;
    for (int l = 1, r = k; r + 1 < (int)p.size(); l++, r++) ans += int64_t(p[l] - p[l - 1]) * int64_t(p.back() - p[r]);

    for (int i = 1; i < (int)p.size(); i++) ans += solve(p[i - 1] + 1, p[i] - 1);

    return ans;
}

void solve(void) {
    int n;
    cin >> n >> k;

    pos = vector<vector<int>>(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i], st[0][i] = a[i], pos[a[i]].push_back(i);
    for (int i = 1; i < maxlgn; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++) st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);

    cout << solve(1, n) << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxn; i++) lgLen[i] = lgLen[i >> 1] + 1;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}