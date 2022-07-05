/**
 * @file 2133.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-04
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

#define maxn 300005

typedef pair<int64_t, int64_t> pll;

int a[maxn], rk[maxn], ork[maxn << 1], buc[maxn], id[maxn], val[maxn], sa[maxn], h[maxn], fa[maxn], siz[maxn];
pll ht[maxn];
multiset<int> maxVal[maxn], minVal[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void solve(void) {
    int n;
    string s;
    cin >> n >> s;
    int m = max(n, 256);
    for (int i = 1; i <= n; i++) buc[rk[i] = s[i - 1]]++;
    for (int i = 1; i <= m; i++) buc[i] += buc[i - 1];
    for (int i = n; i; i--) sa[buc[rk[i]]--] = i;
    for (int l = 1; l == 1 || n != m; l <<= 1) {
        for (int i = n - l + 1; i <= n; i++) id[i + l - n] = i;
        for (int i = 1, j = l; i <= n; i++)
            if (sa[i] > l) id[++j] = sa[i] - l;
        for (int i = 1; i <= m; i++) buc[i] = 0;
        for (int i = 1; i <= n; i++) buc[val[i] = rk[id[i]]]++;
        for (int i = 1; i <= m; i++) buc[i] += buc[i - 1];
        for (int i = n; i; i--) sa[buc[val[i]]--] = id[i];
        for (int i = 1; i <= n; i++) ork[i] = rk[i];
        m = 0;
        for (int i = 1; i <= n; i++) {
            if (ork[sa[i]] != ork[sa[i - 1]] || ork[sa[i] + l] != ork[sa[i - 1] + l]) m++;
            rk[sa[i]] = m;
        }
    }
    s.push_back('#');
    for (int i = 1; i <= n; i++) {
        if (rk[i] == 1) continue;
        h[rk[i]] = max(h[rk[i - 1]] - 1, 0);
        while (s[sa[rk[i] - 1] + h[rk[i]] - 1] == s[i + h[rk[i]] - 1]) h[rk[i]]++;
    }
    for (int i = 1; i <= n; i++) cin >> a[rk[i]];
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1, maxVal[i].insert(a[i]), minVal[i].insert(a[i]);
    for (int i = 2; i <= n; i++) ht[i] = {h[i], i};
    sort(ht + 2, ht + n + 1, greater<pll>());
    int64_t ans1 = 0, ans2 = 0;
    stack<pll> ans;
    for (int i = n - 1, j = 2; ~i; i--) {
        while (j <= n && ht[j].first >= i) {
            int x = ht[j++].second, f1 = getfa(x - 1), f2 = getfa(x);
            if (!ans1)
                ans2 = max((int64_t)*maxVal[f1].rbegin() * *maxVal[f2].rbegin(),
                           (int64_t)*minVal[f1].begin() * *minVal[f2].begin());
            ans1 += 1LL * siz[f1] * siz[f2];
            ans2 = max({ans2, (int64_t)*maxVal[f1].rbegin() * *maxVal[f2].rbegin(),
                        (int64_t)*minVal[f1].begin() * *minVal[f2].begin()});
            for (auto i : maxVal[f2]) maxVal[f1].insert(i);
            for (auto i : minVal[f2]) minVal[f1].insert(i);
            maxVal[f2].clear(), minVal[f2].clear();
            while (maxVal[f1].size() > 2) maxVal[f1].erase(maxVal[f1].begin());
            while (minVal[f1].size() > 2) minVal[f1].erase(--minVal[f1].end());
            siz[f1] += siz[f2], fa[f2] = f1;
        }
        ans.emplace(ans1, ans2);
    }
    while (!ans.empty()) cout << ans.top().first << ' ' << ans.top().second << endl, ans.pop();
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