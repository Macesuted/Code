/**
 * @file 696681I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-06-06
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005
#define B 500

int64_t buc[B], a[maxn], sum[B];

void solve(void) {
    int q;
    cin >> q;

    while (q--) {
        char op;
        cin >> op;
        if (op == '?') {
            int t;
            cin >> t, t--;
            int ans = 0;
            for (int i = 1; i < B; i++)
                if (t / i % 2 == 0) ans += buc[i];
            int x = -1;
            while (x + B <= t) x += B, ans += sum[x / B];
            while (x < t) ans += a[++x];
            cout << ans << endl;
        } else {
            int x, k;
            cin >> x >> k;
            if (op == '-') x = -x;
            if (k < B)
                buc[k] += x;
            else
                for (int i = 0; i < maxn; i += k, x = -x) a[i] += x, sum[i / B] += x;
        }
    }

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
