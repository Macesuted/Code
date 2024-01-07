/**
 * @file 4002.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-12-24
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

typedef pair<int, int> pii;

int fa[2 * maxn + 10], val[maxn];

int getfa(int p) { return fa[p] == p ? p : (fa[p] = getfa(fa[p])); }

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) val[i] = i;
    for (int i = 1; i <= 2 * n + 3; i++) fa[i] = i;
    int D = n + 1;
    for (int i = 1; i <= m; i++) {
        char c;
        cin >> c;
        if (c == '+') {
            int x, y;
            cin >> x >> y;
            val[x] = val[y];
        } else if (c == '-') {
            int x, y;
            cin >> x >> y;
            val[x] = -val[y];
        } else {
            int x;
            cin >> x;
            if (c == 'T') val[x] = n + 1;
            if (c == 'U') val[x] = 0;
            if (c == 'F') val[x] = -n - 1;
        }
    }
    for (int i = 1; i <= n; i++) fa[D + i] = getfa(D + val[i]), fa[D - i] = getfa(D - val[i]);
    for (int i = 1; i <= n; i++)
        if (getfa(D + i) == getfa(D - i)) fa[getfa(D + i)] = getfa(D);
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += (getfa(i) == getfa(D));
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("tribool.in", "r", stdin), freopen("tribool.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int c, _;
    cin >> c >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}