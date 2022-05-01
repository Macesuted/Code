/**
 * @file arc132_a.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

int r[maxn], c[maxn], cnt[maxn];
vector<pii> ask[maxn];
int ans[maxn];
pii rec[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> r[i], cnt[r[i]]++;
    for (int i = 1; i <= n; i++) cin >> c[i], rec[i] = {c[i], i};
    sort(rec + 1, rec + n + 1);
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        ask[r[x]].emplace_back(y, i);
    }
    set<int> S;
    for (int i = 1; i <= n; i++)
        if (c[i]) S.insert(i);
    for (int i = n, sum = 0, p = 1; i; i--) {
        for (auto j : ask[i]) ans[j.second] = S.count(j.first);
        sum += cnt[i];
        while (p <= n && rec[p].first <= sum) S.erase(rec[p++].second);
    }
    for (int i = 1; i <= q; i++) cout << ".#"[ans[i]];
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
