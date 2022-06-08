/**
 * @file 625E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

typedef tuple<int, int, int> tiii;

tiii a[maxn];
int lef[maxn], rig[maxn];
set<tiii> S;
int n, m;

int dist(tiii a, tiii b) {
    if (a == b) return 0x3f3f3f3f;
    int v = get<1>(a) - get<1>(b), d = (get<0>(b) + m - get<0>(a)) % m - (get<2>(a) < get<2>(b)) * get<1>(a);
    if (d <= 0) return 1;
    if (v == 0) return 0x3f3f3f3f;
    if (v < 0) return 0x3f3f3f3f;
    return (get<2>(a) < get<2>(b)) + d / v + (d % v > 0);
}

tiii val(int p) { return {dist(a[p], a[rig[p]]), get<2>(a[p]), p}; }

void solve(void) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> get<0>(a[i]) >> get<1>(a[i]), get<2>(a[i]) = i;
    sort(a, a + n);
    for (int i = 0; i < n; i++) S.emplace(dist(a[lef[(i + 1) % n] = i], a[rig[i] = (i + 1) % n]), get<2>(a[i]), i);
    int lastp = get<2>(*S.begin()), lastt = get<0>(*S.begin()), lastc = 0;
    auto finish = [&](void) {
        if (lef[lastp] != lastp) S.erase(val(lef[lastp]));
        S.erase(val(lastp));
        lastc = min(lastc, get<1>(a[lastp]));
        get<0>(a[lastp]) = (get<0>(a[lastp]) + lastt * lastc) % m, get<1>(a[lastp]) -= lastc;
        if (lef[lastp] != lastp) S.insert(val(lef[lastp]));
        S.insert(val(lastp));
        lastp = get<2>(*S.begin()), lastt = get<0>(*S.begin()), lastc = 0;
        return;
    };
    while (get<0>(*S.begin()) != 0x3f3f3f3f) {
        int p = get<2>(*S.begin()), x = rig[p];
        S.erase(val(p)), S.erase(val(x)), rig[lef[x]] = rig[x], lef[rig[x]] = lef[x], S.insert(val(p));
        lastc++;
        if (get<2>(*S.begin()) != lastp || get<0>(*S.begin()) != lastt) finish();
    }
    vector<int> ans;
    for (auto i : S) ans.push_back(get<1>(i) + 1);
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i : ans) cout << i << ' ';
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}