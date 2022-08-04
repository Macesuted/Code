/**
 * @file 524F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-07
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

#define maxn 2000005

int sa[maxn], rk[maxn], ork[maxn << 1], buc[maxn], id[maxn], val[maxn], sum[maxn], lmin[maxn], rmin[maxn];

void solve(void) {
    string ts;
    cin >> ts;
    int tn = ts.size();
    string s = " " + ts + ts;
    ts = " " + ts;
    int n = s.size(), m = max(256, n);
    for (int i = 1; i <= n; i++) buc[rk[i] = s[i]]++;
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
    for (int i = 1; i <= tn; i++) sum[i] = sum[i - 1] + (ts[i] == '(' ? +1 : -1);
    lmin[1] = rmin[tn + 1] = 0x3f3f3f3f;
    for (int i = 1; i <= tn; i++) lmin[i] = min(lmin[i - 1], sum[i]);
    for (int i = tn; i; i--) rmin[i] = min(rmin[i + 1], sum[i]);
    int ark = 0x3f3f3f3f, pos = 0, delt = max(0, -sum[tn]);
    for (int i = 1; i <= tn; i++)
        if (ark > rk[i] && delt + rmin[i] - sum[i - 1] >= 0 && delt + lmin[i - 1] + sum[tn] - sum[i - 1] >= 0)
            ark = rk[pos = i];
    for (int i = 0; i < -sum[tn]; i++) cout << '(';
    for (int i = pos; i <= tn; i++) cout << ts[i];
    for (int i = 1; i < pos; i++) cout << ts[i];
    for (int i = 0; i < sum[tn]; i++) cout << ')';
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