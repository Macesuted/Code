/**
 * @file 9325.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005
#define maxlgn 20
#define mod 998244353

class STList {
   private:
    int a[maxlgn][maxn], lg[maxn];

   public:
    void build(int n, int v[]) {
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        for (int i = 1; i <= n; i++) a[0][i] = v[i];
        for (int t = 1; t <= lg[n]; t++)
            for (int l = 1; l + (1 << t) - 1 <= n; l++) a[t][l] = min(a[t - 1][l], a[t - 1][l + (1 << (t - 1))]);
        return;
    }
    int query(int l, int r) {
        int t = lg[r - l + 1];
        return min(a[t][l], a[t][r - (1 << t) + 1]);
    }
} STL;

int a[maxn], p[maxn];
vector<int> fl[maxn], gl[maxn], fr[maxn], gr[maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }

void solve(int l, int r) {
    if (l > r) return;

    int x = p[STL.query(l, r)];
    solve(l, x - 1), solve(x + 1, r);

    fl[x].resize(x - l + 1), fr[x].resize(r - x + 1);
    for (int i = l; i < x; i++) {
        int y = p[STL.query(i, x - 1)];
        fl[x][x - i] = Mod(gl[y][y - i] + gr[y][x - 1 - y] + 1);
    }
    for (int i = x + 1; i <= r; i++) {
        int y = p[STL.query(x + 1, i)];
        fr[x][i - x] = Mod(gl[y][y - x - 1] + gr[y][i - y] + 1);
    }

    gl[x] = fl[x];
    for (size_t i = 1; i < gl[x].size(); i++) gl[x][i] = Mod(gl[x][i] + gl[x][i - 1]);
    gr[x] = fr[x];
    for (size_t i = 1; i < gr[x].size(); i++) gr[x][i] = Mod(gr[x][i] + gr[x][i - 1]);

    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], p[a[i]] = i;

    STL.build(n, a);
    for (int i = 1; i <= n; i++) fl[i] = gl[i] = fr[i] = gr[i] = vector<int>();
    solve(1, n);

    int x = p[STL.query(1, n)];
    cout << Mod(gl[x][x - 1] + gr[x][n - x] + 1) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
