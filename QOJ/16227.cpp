/**
 * @file 16227.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 5005

int p[maxn], rp[maxn], fa[maxn];
bool vis[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

int dfs(int l, int r) {
    if (l == r) return 0;

    for (int i = l; i <= r; i++) fa[i] = i, vis[i] = false;

    auto pre = [&](int p) -> int { return p == l ? r : p - 1; };
    auto nxt = [&](int p) -> int { return p == r ? l : p + 1; };

    int ans = INT_MAX, cnt = 0;
    vector<int> pos;
    for (int i = l; i < r; i++) {
        int x = rp[i];

        vis[x] = true, cnt++;
        if (vis[pre(x)]) fa[x] = getfa(pre(x)), cnt--;
        if (vis[nxt(x)]) fa[nxt(x)] = getfa(x), cnt--;

        int tar = (r - getfa(x) + 1) % (r - l + 1);
        if (cnt == 1 && tar <= ans) {
            if (tar < ans) pos.clear(), ans = tar;
            if (tar == ans) pos.push_back(i);
        }
    }

    for (int i = l; i <= r; i++) rp[i] = (rp[i] - l + ans) % (r - l + 1) + l;
    for (int i = l; i <= r; i++) p[rp[i]] = i;

    int lst = l - 1, mxv = 0;
    pos.push_back(r);
    for (auto p : pos) mxv = max(mxv, dfs(lst + 1, p)), lst = p;

    return ans + mxv;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x; i <= n; i++) cin >> x, p[x] = i, rp[i] = x;

    cout << dfs(1, n) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
