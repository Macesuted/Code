/**
 * @file 14686.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 500005

int fa[maxn], delt[maxn];
int64_t a[maxn], ans[maxn];
bool cur[maxn];

void calc(int p) {
    int dist = abs(a[p] - a[fa[p]]) * 2;
    if (delt[p] == delt[fa[p]]) return ans[p] = dist + ans[fa[p]], void();
    if (dist < ans[fa[p]] * 2) return ans[p] = dist / 2, void();
    return ans[p] = ans[fa[p]] + dist - ans[fa[p]] * 2, void();
}
void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> fa[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) delt[i] = (a[i] < a[fa[i]] ? +1 : -1);

    for (int i = 1; i <= n; i++) {
        if (ans[i]) continue;

        vector<int> rec;
        int p = i;
        while (!ans[p] && !cur[p]) cur[p] = true, rec.push_back(p), p = fa[p];
        reverse(rec.begin(), rec.end());

        for (auto x : rec) cur[x] = false;

        if (ans[p]) {
            for (auto x : rec) calc(x);
            continue;
        }

        vector<int> ring(1, p);
        for (size_t i = 0; rec[i] != p; i++) ring.push_back(rec[i]);

        int sp = -1, stim = INT_MAX;
        for (auto p : ring) {
            if (delt[fa[p]] == delt[p]) continue;
            int tim = abs(a[p] - a[fa[p]]);
            if (tim < stim) stim = tim, sp = p;
        }

        assert(sp != -1);
        vector<int> nRing;
        size_t spos = 0;
        while (ring[spos] != sp) spos++;
        for (size_t i = spos; i < ring.size(); i++) nRing.push_back(ring[i]);
        for (size_t i = 0; i < spos; i++) nRing.push_back(ring[i]);
        ring = nRing;

        ans[sp] = stim;
        for (size_t i = 1; i < ring.size(); i++) calc(ring[i]);

        for (auto x : rec)
            if (!ans[x]) calc(x);
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
