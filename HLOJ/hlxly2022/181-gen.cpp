/**
 * @file 181-gen.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-20
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

#define eps 1e-9

typedef pair<int, int> pii;

double k[100], b[100];
pii LP[100], RP[100];

void solve(void) {
    mt19937 mt(time(0));
    int maxV = 20, L = mt() % maxV, R = mt() % maxV, n = 5;
    if (L > R) swap(L, R);
    cout << L << ' ' << R << ' ' << n << endl;
    for (int i = 1; i <= n; i++)
        while (true) {
            int lx = mt() % maxV, ly = mt() % maxV, rx = mt() % maxV, ry = mt() % maxV;
            if (lx == rx || ly == ry) continue;
            if (lx > rx) swap(lx, rx), swap(ly, ry);
            LP[i] = {lx, ly}, RP[i] = {rx, ry};
            if (ly > ry) swap(LP[i], RP[i]);
            k[i] = 1. * (ry - ly) / (rx - lx), b[i] = ly - k[i] * lx;
            bool chk = true;
            for (int j = 1; j < i && chk; j++) {
                if (fabs(k[i] - k[j]) < eps) continue;
                double x = (b[i] - b[j]) / (k[j] - k[i]);
                if (x < lx || x > rx) continue;
                chk = false;
            }
            if (chk) break;
        }
    for (int i = 1; i <= n; i++)
        cout << LP[i].first << ' ' << LP[i].second << ' ' << RP[i].first << ' ' << RP[i].second << endl;
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