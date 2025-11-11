/**
 * @file 5474.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005
#define mod 998244353

using pii = pair<int, int>;

int Mod(int x) { return x >= mod ? x - mod : x; }

class FenwickTree {
   private:
    vector<int> a, v;
    int n;

   public:
    void insVal(int x) { return a.push_back(x); }
    void build(void) {
        sort(a.begin(), a.end()), a.resize(unique(a.begin(), a.end()) - a.begin());
        v.resize((n = a.size()) + 1);
        return;
    }
    void add(int p, int val) {
        p = lower_bound(a.begin(), a.end(), p) - a.begin() + 1;
        for (int i = p; i <= n; i += i & -i) v[i] = Mod(v[i] + val);
        return;
    }
    int sum(int p) {
        int ans = 0;
        p = lower_bound(a.begin(), a.end(), p) - a.begin() + 1;
        for (int i = p - 1; i; i -= i & -i) ans = Mod(ans + v[i]);
        return ans;
    }
};

int a[maxn], pre[maxn][4];
int64_t f[maxn];

void solve(void) {
    string s;
    cin >> s;
    int n = s.size();

    for (int i = 1; i <= n; i++) a[i] = (s[i - 1] == 'I' ? 1 : s[i - 1] == 'C' ? 2 : 3);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 3; j++) pre[i][j] = pre[i - 1][j];
        pre[i][a[i]]++;
    }

    map<int, FenwickTree> c12, c13, c23;

    auto Add = [&](int64_t &x, int64_t v) -> int64_t { return x = Mod(x + v); };

    for (int i = 0; i <= n; i++) {
        c12[pre[i][1] - pre[i][2]].insVal(pre[i][3] - pre[i][1]);
        c13[pre[i][1] - pre[i][3]].insVal(pre[i][2] - pre[i][1]);
        c23[pre[i][2] - pre[i][3]].insVal(pre[i][1] - pre[i][2]);
    }

    for (auto &[v, T] : c12) T.build();
    for (auto &[v, T] : c13) T.build();
    for (auto &[v, T] : c23) T.build();

    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        c12[pre[i - 1][1] - pre[i - 1][2]].add(pre[i - 1][3] - pre[i - 1][1], f[i - 1]);
        c13[pre[i - 1][1] - pre[i - 1][3]].add(pre[i - 1][2] - pre[i - 1][1], f[i - 1]);
        c23[pre[i - 1][2] - pre[i - 1][3]].add(pre[i - 1][1] - pre[i - 1][2], f[i - 1]);

        Add(f[i], c12[pre[i][1] - pre[i][2]].sum(pre[i][3] - pre[i][1]));
        Add(f[i], c13[pre[i][1] - pre[i][3]].sum(pre[i][2] - pre[i][1]));
        Add(f[i], c23[pre[i][2] - pre[i][3]].sum(pre[i][1] - pre[i][2]));
    }

    cout << f[n] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}