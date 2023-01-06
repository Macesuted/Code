/**
 * @file 1246.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-17
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

#define maxn 2005

typedef pair<int, int> pii;

int n, a[maxn], b[maxn], ans[maxn];
pii upd[maxn];
set<int> Sl, Sr;

bool chk(int i, int p, int q) {
    return a[i] * int64_t(abs(p - i)) + (a[p] - a[i]) * int64_t(abs(q - i)) <= a[q] * int64_t(abs(p - i));
}
void recalc(int i) {
    Sl.clear(), Sr.clear();
    for (int j = i - 1; j; j--)
        if (Sl.empty() || chk(i, *Sl.begin(), j)) Sl.insert(j);
    for (int j = i + 1; j <= n; j++)
        if (Sr.empty() || chk(i, *Sr.rbegin(), j)) Sr.insert(j);
    return;
}

void solve(void) {
    int q;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> b[i];
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> upd[i].first >> upd[i].second;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) a[j] = b[j];
        recalc(i), ans[0] += Sr.size();
        for (int j = 1; j <= q; j++) {
            int p = upd[j].first;
            a[p] += upd[j].second;
            if (p == i)
                ans[j] -= Sl.size() + Sr.size(), recalc(i);
            else if (p > i) {
                if (chk(i, *--Sr.upper_bound(p), p)) {
                    ans[j]++;
                    auto it = ++Sr.insert(p).first;
                    while (it != Sr.end() && !chk(i, p, *it)) it = Sr.erase(it), ans[j]--;
                }
            } else {
                if (chk(i, *Sl.lower_bound(p), p)) {
                    ans[j]++;
                    auto it = Sl.insert(p).first;
                    while (it != Sl.begin() && !chk(i, p, *--it)) it = Sl.erase(it);
                }
            }
        }
    }
    for (int i = 1; i <= q; i++) cout << (ans[i] += ans[i - 1]) << endl;
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