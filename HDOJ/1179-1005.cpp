/**
 * @file 1179-1005.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 500005

int64_t pre[maxn], dis[maxn], dep[maxn];
int fa[maxn], id[maxn];

void solve(void) {
    int q;
    cin >> q;

    vector<int> path;
    path.push_back(1), path.push_back(2);
    pre[0] = 0, cin >> pre[1];
    dis[1] = dis[2] = 0;
    dep[1] = dep[2] = 0;
    fa[1] = 1, fa[2] = 2;
    id[1] = 0, id[2] = 1;

    int n = 2, m = 2, l = 0, r = m - 1;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            cin >> pre[m], pre[m] += pre[m - 1];
            path.push_back(++n);
            dis[n] = 0;
            dep[n] = 0;
            fa[n] = n;
            r = id[n] = m++;
        } else if (op == 2) {
            int x;
            cin >> x >> dis[++n];
            dis[n] += dis[x];
            int f = fa[n] = fa[x];
            dep[f] = max(dep[f], dis[n]);
            if (dep[f] == pre[id[f]]) l = max(l, id[f]);
            if (dep[f] == pre[m - 1] - pre[id[f]]) r = min(r, id[f]);
        } else
            cout << pre[r] - pre[l] << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}