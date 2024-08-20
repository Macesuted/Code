/**
 * @file I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 19
#define maxl 50005

typedef pair<int64_t, int64_t> pll;

const int64_t base1 = 1331, base2 = 13331, mod1 = 1e9 + 7, mod2 = 1e9 + 9;

int64_t pow1[maxl], pow2[maxl];

class Hash {
   private:
    vector<int64_t> v1, v2;
    int n;

   public:
    void build(string s) {
        n = s.size();
        v1.resize(n + 1), v2.resize(n + 1);
        v1[0] = v2[0] = 1;
        for (int i = 1; i <= n; i++)
            v1[i] = (v1[i - 1] * base1 + s[i - 1]) % mod1, v2[i] = (v2[i - 1] * base2 + s[i - 1]) % mod2;
        return;
    }
    pll getHash(int l, int r) {
        return {(v1[r] - v1[l - 1] * pow1[r - l + 1] % mod1 + mod1) % mod1,
                (v2[r] - v2[l - 1] * pow2[r - l + 1] % mod2 + mod2) % mod2};
    }
};

string a[maxn];
Hash h[maxn];
int len[maxn], sam[maxn][maxn], f[1 << maxn][maxn], fa[1 << maxn][maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i], h[i].build(a[i]), len[i] = a[i].size();
    for (int i = 0; i < n; i++) {
        bool chk = false;
        for (int j = 0; j < n && !chk; j++) {
            if (i == j) continue;
            for (int l = 1, r = len[i]; r <= len[j] && !chk; l++, r++) chk |= (h[i].getHash(1, len[i]) == h[j].getHash(l, r));
        }
        if (chk) n--, swap(a[i], a[n]), swap(h[i], h[n]), swap(len[i], len[n]), i--;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            sam[j][i] = 0;
            int l = 1, r = len[i], m = len[j];
            while (r <= m) l++, r++;
            while (l <= m) {
                if (h[i].getHash(1, m - l + 1) == h[j].getHash(l, m)) {
                    sam[j][i] = m - l + 1;
                    break;
                }
                l++, r++;
            }
        }
    for (int i = 0; i < (1 << n); i++)
        for (int j = 0; j < n; j++) f[i][j] = INT_MAX;
    for (int i = 0; i < n; i++) f[1 << i][i] = len[i];
    for (int S = 1; S < (1 << n); S++)
        for (int i = 0; i < n; i++) {
            if (f[S][i] == INT_MAX) continue;
            for (int j = 0; j < n; j++)
                if (!(S >> j & 1) && f[S][i] + len[j] - sam[i][j] < f[S | (1 << j)][j])
                    f[S | (1 << j)][j] = f[S][i] + len[j] - sam[i][j], fa[S | (1 << j)][j] = i;
        }
    int p = 0, S = (1 << n) - 1;
    for (int i = 1; i < n; i++)
        if (f[S][i] < f[S][p]) p = i;
    vector<int> ans;
    while (S) {
        ans.push_back(p);
        tie(S, p) = make_pair(S ^ (1 << p), fa[S][p]);
    }
    reverse(ans.begin(), ans.end());
    cout << a[ans.front()];
    for (int i = 1; i < (int)ans.size(); i++)
        for (int j = sam[ans[i - 1]][ans[i]]; j < (int)a[ans[i]].size(); j++) cout << a[ans[i]][j];
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    pow1[0] = pow2[0] = 1;
    for (int i = 1; i < maxl; i++) pow1[i] = pow1[i - 1] * base1 % mod1, pow2[i] = pow2[i - 1] * base2 % mod2;

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}