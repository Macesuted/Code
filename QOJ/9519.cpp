/**
 * @file 9519.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 105

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

vector<pii> graph[maxn];
vector<tiii> links;
int cnt = 0;

void solve(int dep, int l, int r, int ql, int qr, int fa, bool pre, bool lst) {
    if (ql <= l && r <= qr) return links.emplace_back(fa, dep, lst), void();
    int mid = (l + r) >> 1;
    if (!pre) graph[fa].emplace_back(++cnt, lst), fa = cnt;
    if (ql <= mid) solve(dep - 1, l, mid, ql, qr, fa, pre, 0);
    if (qr > mid) solve(dep - 1, mid + 1, r, ql, qr, fa, false, 1);
    return;
}

void solve(void) {
    int L, R;
    cin >> L >> R;
    solve(20, 0, (1 << 20) - 1, L, R, ++cnt, true, 0);
    cnt++;
    int maxv = 0;
    for (auto i : links) maxv = max(maxv, get<1>(i));
    for (int i = 1; i <= maxv; i++) graph[cnt + i].emplace_back(cnt + i - 1, 0), graph[cnt + i].emplace_back(cnt + i - 1, 1);
    for (auto [x, d, w] : links) graph[x].emplace_back(cnt + d, w);
    cnt += maxv;
    cout << cnt << endl;
    for (int i = 1; i <= cnt; i++) {
        cout << graph[i].size();
        for (auto [x, d] : graph[i]) cout << ' ' << x << ' ' << d;
        cout << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}