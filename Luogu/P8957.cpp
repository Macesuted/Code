/**
 * @file P8957.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-19
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

#define maxn 1000005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

tiii a[maxn], b[maxn];
vector<pii> op;

void solve(void) {
    int n, m = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> get<0>(a[i]);
    for (int i = 1; i <= n; i++) cin >> get<1>(a[i]), get<2>(a[i]) = i;
    sort(a + 1, a + n + 1), get<1>(b[0]) = INT_MAX;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++)
        if (get<1>(a[i]) >= get<1>(b[m]))
            ans += get<0>(a[i]) + get<1>(a[i]), op.emplace_back(get<2>(a[i]), get<2>(b[m]));
        else
            b[++m] = a[i];
    for (int i = 1; i < m; i++) ans += get<1>(b[i]) + get<0>(b[i + 1]), op.emplace_back(get<2>(b[i]), get<2>(b[i + 1]));
    cout << ans << endl;
    for (auto i : op) cout << i.first << ' ' << i.second << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}