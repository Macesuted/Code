/**
 * @file 1738F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1005

typedef pair<int, int> pii;

pii a[maxn];
int fa[maxn], deg[maxn], cnt[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first, a[i].second = fa[i] = i, deg[i] = a[i].first, cnt[i] = 1;
    sort(a + 1, a + n + 1, greater<pii>());
    for (int i = 1; i <= n; i++) {
        int p = a[i].second;
        if (getfa(p) != p) continue;
        while ((int64_t)cnt[p] * cnt[p] < deg[p]) {
            cout << "? " << p << endl;
            int x;
            cin >> x;
            int px = getfa(x);
            if (p == px) continue;
            cnt[p] += cnt[px], deg[p] += deg[px], fa[px] = p;
        }
    }
    cout << "!";
    for (int i = 1; i <= n; i++) cout << ' ' << getfa(i);
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}