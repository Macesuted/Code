/**
 * @file 2042D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

pii a[maxn];
int ans[maxn];
bool ban[maxn];
int n;

void calc(void) {
    vector<tiii> rec;

    for (int i = 1; i <= n; i++) rec.emplace_back(a[i].first, -a[i].second, i);
    sort(rec.begin(), rec.end());

    stack<pii> S;
    S.emplace(0, INT_MAX);
    for (auto [l, r, id] : rec) {
        r = -r;
        while (S.top().second < r) S.pop();
        if (!ban[id] && S.size() > 1) ans[id] += l - S.top().first;
        S.emplace(l, r);
    }

    return;
}

void solve(void) {
    cin >> n;

    vector<vector<pii>> lef(n + 1), rig(n + 1);
    map<pii, int> cnt;

    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second, ans[i] = 0, cnt[a[i]]++;
    for (int i = 1; i <= n; i++) ban[i] = (cnt[a[i]] > 1);

    calc();

    for (int i = 1; i <= n; i++) tie(a[i].first, a[i].second) = make_pair(-a[i].second, -a[i].first);

    calc();

    for (int i = 1; i <= n; i++) cout << (ans[i]) << endl;

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