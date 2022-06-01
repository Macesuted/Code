/**
 * @file 2083.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 30005
#define maxlgn 20

class SuffixArray {
   private:
    int sa[maxn], rk[maxn], ork[maxn << 1], id[maxn], val[maxn], buc[maxn], hei[maxn], lg[maxn], st[maxlgn][maxn], n;

   public:
    int LCP(int l, int r) {
        if (l == r) return n - l + 1;
        int pl = rk[l], pr = rk[r], len = lg[abs(pl - pr)];
        if (pl > pr) swap(pl, pr);
        return min(st[len][pl + 1], st[len][pr - (1 << len) + 1]);
    }

    void build(string s) {
        int m = max(256, n = s.size());
        for (int i = 1; i <= m; i++) buc[i] = 0;
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
            for (int i = 1; i <= n; i++)
                rk[sa[i]] = m += (ork[sa[i]] != ork[sa[i - 1]] || ork[sa[i] + l] != ork[sa[i - 1] + l]);
        }
        for (int i = 1; i <= n; i++) ork[i] = 0;
        s.push_back('#');
        for (int i = 1; i <= n; i++) {
            if (rk[i] == 1) continue;
            hei[rk[i]] = max(0, hei[rk[i - 1]] - 1);
            while (s[sa[rk[i] - 1] + hei[rk[i]] - 1] == s[i + hei[rk[i]] - 1]) hei[rk[i]]++;
        }
        for (int i = 2; i < maxn; i++) lg[i] = lg[i >> 1] + 1;
        for (int i = 1; i <= n; i++) st[0][i] = hei[i];
        for (int i = 1; i < maxlgn; i++)
            for (int j = 1; j + (1 << i) - 1 <= n; j++) st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        return;
    }
} SA[2];

string s;

int f[maxn], g[maxn];

void solve(void) {
    cin >> s;
    int n = s.size();
    reverse(s.begin(), s.end()), SA[0].build(s), reverse(s.begin(), s.end()), SA[1].build(s);
    for (int i = 1; i <= n; i++) f[i] = g[i] = 0;
    for (int len = 1; len * 2 <= n; len++)
        for (int l = 1, r = len + 1; r <= n; l += len, r += len) {
            int xl = min(len, SA[0].LCP(n - l + 1, n - r + 1)), xr = min(len, SA[1].LCP(l, r));
            if (xl + xr < len) continue;
            int pl = l - xl + 1, pr = l + xr - len;
            f[pl + 2 * len - 1]++, f[pr + 2 * len]--, g[pl]++, g[pr + 1]--;
        }
    for (int i = 1; i <= n; i++) f[i] += f[i - 1], g[i] += g[i - 1];
    int64_t ans = 0;
    for (int i = 1; i < n; i++) ans += 1LL * f[i] * g[i + 1];
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}