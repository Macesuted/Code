/**
 * @file 16226.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 300005

using pii = pair<int, int>;

int a[maxn], pos[maxn], fl[maxn], fr[maxn], vl[maxn], vr[maxn];
int64_t ans[maxn];
map<pii, int> f;

void dfs(int p) {
    queue<int> sl, sr;
    int q = vl[p];
    while (q) sl.push(q), q = vr[q];
    q = vr[p];
    while (q) sr.push(q), q = vl[q];

    int l = fl[p], r = fr[p];
    while (!sl.empty() || !sr.empty())
        if (sr.empty() || (!sl.empty() && a[sl.front()] < a[sr.front()])) {
            ans[f[{sl.front(), p}]] += int64_t(sl.front() - l) * (r - p);
            l = sl.front(), sl.pop();
        } else {
            ans[f[{p, sr.front()}]] += int64_t(p - l) * (r - sr.front());
            r = sr.front(), sr.pop();
        }

    if (vl[p]) dfs(vl[p]);
    if (vr[p]) dfs(vr[p]);

    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]] = i;

    stack<int> S;
    S.push(0);
    for (int i = 1; i <= n; i++) {
        while (a[i] < a[S.top()]) vl[i] = S.top(), S.pop();
        fl[i] = S.top();
        S.push(i);
    }

    S = stack<int>();
    S.push(n + 1);
    for (int i = n; i; i--) {
        while (a[i] < a[S.top()]) vr[i] = S.top(), S.pop();
        fr[i] = S.top();
        S.push(i);
    }

    for (int i = 1; i < n; i++) f[{i, i + 1}] = 1;

    for (int i = n; i; i--) {
        int p = pos[i], q = 0;
        if (vl[p] && (!q || a[vl[p]] < a[q])) q = vl[p];
        if (vr[p] && (!q || a[vr[p]] < a[q])) q = vr[p];
        f[{fl[p], fr[p]}] = f[{min(p, q), max(p, q)}] + 1;
    }

    dfs(pos[1]);

    for (int i = 1; i <= n; i++) cout << ans[i] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
