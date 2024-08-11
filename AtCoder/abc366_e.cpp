/**
 * @file abc366_e.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-10
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
#define maxD 1000005

int x[maxn], y[maxn], D;
int Sx[maxD], Sy[maxD];

void solve(int n, int a[], int S[]) {
    int64_t tot = 0;
    for (int i = 1; i <= n; i++) tot += a[i] + 2e6;
    for (int i = -2e6, j = 1, pr = n; i <= 2e6; i++) {
        if (tot <= D) S[tot]++;
        int c = 0;
        while (j <= n && a[j] == i) j++, c++;
        pr -= c, tot -= pr, tot += n - pr;
    }
    return;
}

void solve(void) {
    int n;
    cin >> n >> D;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    sort(x + 1, x + n + 1), sort(y + 1, y + n + 1);
    solve(n, x, Sx), solve(n, y, Sy);
    for (int i = 1; i <= D; i++) Sy[i] += Sy[i - 1];
    int64_t ans = 0;
    for (int i = 0; i <= D; i++) ans += (int64_t)Sx[i] * Sy[D - i];
    cout << ans << endl;
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