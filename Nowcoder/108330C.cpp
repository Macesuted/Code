/**
 * @file 108330C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

using tiii = tuple<int, int, int>;

int a[maxn], pre[maxn], nxt[maxn];
set<int> pos[30];
set<tiii> rec[30];

void solve(void) {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s, s = ' ' + s;
    for (int i = 1; i <= n; i++) a[i] = s[i] - 'a';

    auto link = [&](int c, int x, int y) -> void { return rec[c].emplace(y - x - 1, x, y), nxt[x] = y, pre[y] = x, void(); };
    auto unlink = [&](int c, int x, int y) -> void { return rec[c].erase({y - x - 1, x, y}), void(); };

    for (int i = 0; i < 26; i++) pos[i].insert(0);
    for (int i = 1; i <= n; i++) link(a[i], *pos[a[i]].rbegin(), i), pos[a[i]].insert(i);
    for (int i = 0; i < 26; i++) link(i, *pos[i].rbegin(), n + 1), pos[i].insert(n + 1);

    auto calc = [&](int l, int r) -> int {
        if ((r - l + 1) & 1) return r - l + 1;

        int cl = l, cr = r;
        while (nxt[cl] > r) cl++;
        while (pre[cr] < l) cr--;

        int len = r - l - min(cl - l, r - cr);
        return len - !(len & 1);
    };

    auto solve = [&](void) -> int {
        int cnt = 0;
        for (int i = 0; i < 26; i++) cnt += (pos[i].size() > 2);

        if (cnt & 1) return calc(1, n);

        tiii mxv = {0, 0, 0};
        for (int i = 0; i < 26; i++)
            if (pos[i].size() > 2) mxv = max(mxv, *rec[i].rbegin());

        auto [len, l, r] = mxv;
        if (len & 1) return len;

        for (int l = 0, r = len + 1; r <= n + 1; l++, r++)
            if ((l >= 1 && nxt[l] != r) || (r <= n && pre[r] != l)) return len - 1;

        return max(calc(1, len), calc(n - len + 1, n));
    };

    cout << solve() << endl;

    while (q--) {
        int x;
        char c;
        cin >> x >> c;
        int v = c - 'a';

        auto p = pos[a[x]].find(x);
        unlink(a[x], *prev(p), x), unlink(a[x], x, *next(p)), link(a[x], *prev(p), *next(p));
        pos[a[x]].erase(p), p = pos[a[x] = v].insert(x).first;
        unlink(a[x], *prev(p), *next(p)), link(a[x], *prev(p), x), link(a[x], x, *next(p));

        cout << solve() << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
