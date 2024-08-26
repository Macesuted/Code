/**
 * @file G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 200005

class UnionSet {
   private:
    int fa[maxn], siz[maxn];
    int64_t sum;

    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }
    int64_t calc(int64_t v) { return v * (v - 1) / 2; }

   public:
    void resize(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
        sum = 0;
        return;
    }
    void merge(int x, int y) {
        x = getfa(x), y = getfa(y);
        if (x == y) return;
        sum -= calc(siz[x]) + calc(siz[y]);
        siz[x] += siz[y], fa[y] = x;
        sum += calc(siz[x]);
        return;
    }
    int64_t query(void) { return sum; }
} US;

set<int> S;
int a[maxn], pos[maxn], n, k;

void insert(int v) {
    auto p = S.insert(v).first, pl = prev(p), pr = next(p);
    if (*pl != 0 && *p - *pl <= k) US.merge(*p, *pl);
    if (*pr != n + 1 && *pr - *p <= k) US.merge(*p, *pr);
    return;
}

void solve(void) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], pos[i] = i;
    US.resize(n);
    sort(pos + 1, pos + n + 1, [&](int x, int y) { return a[x] > a[y]; });
    S.insert(0), S.insert(n + 1);
    int64_t lst = 0, ans = 0;
    for (int i = 1; i <= n; i++) ans += a[i];
    for (int i = 1; i <= n; i++) insert(pos[i]), ans += a[pos[i]] * (US.query() - lst), lst = US.query();
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}