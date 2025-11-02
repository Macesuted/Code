/**
 * @file 9326.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 300005
#define maxlgn 20

class STList {
   private:
    int64_t a[maxlgn][maxn];
    int lg[maxn], n;

   public:
    void build(int _n) {
        n = _n;
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        return;
    }
    void modi(int p, int64_t v) {
        a[0][p] = v;
        for (int t = 1; p + (1 << t) - 1 <= n; t++) a[t][p] = min(a[t - 1][p], a[t - 1][p + (1 << (t - 1))]);
        return;
    }
    int64_t query(int l, int r) {
        int t = lg[r - l + 1];
        return min(a[t][l], a[t][r - (1 << t) + 1]);
    }
} STLg, STLf;

int64_t f[maxn], a[maxn];
int ql[maxn], qr[maxn];

void solve(void) {
    int n, c;
    cin >> n >> c;
    for (int i = 1; i <= n; i++) cin >> ql[i];
    for (int i = 1; i <= n; i++) cin >> qr[i];
    for (int i = 1; i <= n; i++) cin >> a[i];

    STLf.build(n), STLg.build(n);

    for (int i = n; i; i--) {
        if (i + ql[i] <= n) {
            f[i] = STLf.query(max(i + 1, i + ql[i] - c), i + ql[i]);
            if (i + qr[i] > n) qr[i] = n - i, f[i] = max(f[i], (int64_t)0);
            if (qr[i] > c) f[i] = max(f[i], -STLg.query(i + max(ql[i], c + 1), i + qr[i]));
        } else
            f[i] = 0;
        STLf.modi(i, f[i] += a[i]);
        if (i + c <= n) STLg.modi(i + c, -STLf.query(i, i + c));
    }

    cout << f[1] - a[1] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
