/**
 * @file 11106.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 500005
#define maxlgn 22

int64_t a[maxn], val[maxlgn][maxn], mxVal[maxlgn][maxn], gl[maxn], gr[maxn];
int nxt[maxlgn][maxn], lg[maxn];
bool cl[maxn], cr[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int64_t sum = 0;
    gl[0] = 0;
    for (int i = 1; i <= n; i++) {
        if ((sum += a[i]) < 0) sum = 0;
        gl[i] = max(gl[i - 1], sum);
    }
    gr[n + 1] = sum = 0;
    for (int i = n; i; i--) {
        if ((sum += a[i]) < 0) sum = 0;
        gr[i] = max(gr[i + 1], sum);
    }

    a[0] = 0;
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];

    for (int i = 0; i <= n; i++) mxVal[0][i] = a[i];
    for (int t = 1; t < maxlgn; t++)
        for (int i = 0; i + (1 << t) - 1 <= n; i++) mxVal[t][i] = max(mxVal[t - 1][i], mxVal[t - 1][i + (1 << (t - 1))]);

    auto getMxVal = [&](int l, int r) {
        int t = lg[r - l + 1];
        return max(mxVal[t][l], mxVal[t][r - (1 << t) + 1]);
    };

    int64_t cur = a[0];
    cl[1] = false;
    for (int i = 2; i <= n; i++) cur = min(cur, a[i - 2]), cl[i] = (a[i - 1] - cur >= 0);
    cur = a[n];
    cr[n] = false;
    for (int i = n - 1; i; i--) cur = max(cur, a[i + 1]), cr[i] = (cur - a[i] >= 0);

    stack<int> S;
    S.push(n + 1);
    a[n + 1] = -1e18;
    nxt[0][n + 1] = n + 1;
    for (int i = n; i >= 0; i--) {
        while (a[S.top()] > a[i]) S.pop();
        nxt[0][i] = S.top(), val[0][i] = getMxVal(i, S.top() - 1);
        S.push(i);
    }
    for (int t = 1; t < maxlgn; t++)
        for (int i = 0; i <= n + 1; i++) {
            int j = nxt[t - 1][i];
            nxt[t][i] = nxt[t - 1][j], val[t][i] = max(val[t - 1][i], val[t - 1][j] + a[i] - a[j]);
        }

    while (q--) {
        int l, r;
        cin >> l >> r;
        int64_t xxans = max({(int64_t)0, gl[l - 1], gr[r + 1]});
        if (cl[l] || cr[r]) {
            cout << -1 << endl;
            continue;
        }
        int p = l - 1;
        if (nxt[0][p] > r) {
            int64_t ans = max((int64_t)0, getMxVal(l - 1, r - 1) + 1 - a[r]);
            cout << ans + max((int64_t)0, xxans - (ans + a[r] - a[l - 1]) + 1) << endl;
            continue;
        }
        p = nxt[0][p];
        int64_t delt = a[l - 1] - a[p] + 1, curMxVal = a[l - 1];
        if (l < p) curMxVal = max(curMxVal, getMxVal(l, p - 1));
        for (int t = maxlgn - 1; ~t; t--)
            if (nxt[t][p] <= r) {
                curMxVal = max(curMxVal, delt + val[t][p]);
                delt += a[p] - a[nxt[t][p]];
                p = nxt[t][p];
            }
        if (p < r) curMxVal = max(curMxVal, delt + getMxVal(p, r - 1));
        int64_t ans = delt + max((int64_t)0, curMxVal + 1 - (a[r] + delt));
        cout << ans + max((int64_t)0, xxans - (ans + a[r] - a[l - 1]) + 1) << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    for (int i = 2; i < maxn; i++) lg[i] = lg[i >> 1] + 1;

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}