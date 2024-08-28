/**
 * @file E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-26
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

#define maxn 1000005

typedef pair<int, int> pii;

class Hash {
   private:
    const int64_t base[2] = {1331, 13331}, mod[2] = {1000000007, 1000000009};

    vector<int64_t> val[2], pw[2];

   public:
    void build(string s) {
        int n = s.size();
        for (int t = 0; t < 2; t++) {
            val[t].resize(n + 1), pw[t].resize(n + 1), pw[t][0] = 1;
            for (int i = 1; i <= n; i++)
                val[t][i] = (val[t][i - 1] * base[t] + s[i - 1]) % mod[t], pw[t][i] = pw[t][i - 1] * base[t] % mod[t];
        }
        return;
    }
    pii query(int l, int r) {
        return {(val[0][r] + mod[0] - val[0][l - 1] * pw[0][r - l + 1] % mod[0]) % mod[0],
                (val[1][r] + mod[1] - val[1][l - 1] * pw[1][r - l + 1] % mod[1]) % mod[1]};
    }
};

Hash hsh;
int n, a[maxn], rig[maxn];
vector<int> pos[30];

int LCP(int p, int q) {
    int l = 0, r = min(n - p + 1, n - q + 1) + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (hsh.query(p, p + mid - 1) == hsh.query(q, q + mid - 1) ? l : r) = mid;
    }
    return l;
}

char comp(array<int, 28> l, array<int, 28> r) {
    queue<pii> ql, qr;

    for (int i = 0; i < 26; i++)
        if (l[i]) ql.emplace(i, l[i]);
    if (l[27]) ql.emplace(-l[26], l[27]);
    for (int i = 0; i < 26; i++)
        if (r[i]) qr.emplace(i, r[i]);
    if (r[27]) qr.emplace(-r[26], r[27]);

    while (!ql.empty() && !qr.empty()) {
        pii &vl = ql.front(), &vr = qr.front();
        int len = min(vl.second, vr.second);
        if (vl.first >= 0 && vr.first >= 0) {
            if (vl.first != vr.first) return vl.first < vr.first ? '<' : '>';
        } else if (vl.first >= 0) {
            int l = (a[-vr.first] == vl.first ? rig[-vr.first] : 0);
            if (l < len) return vl.first < a[-vr.first + l] ? '<' : '>';
        } else if (vr.first >= 0) {
            int l = (a[-vl.first] == vr.first ? rig[-vl.first] : 0);
            if (l < len) return a[-vl.first + l] < vr.first ? '<' : '>';
        } else {
            int l = LCP(-vl.first, -vr.first);
            if (l < len) return a[-vl.first + l] < a[-vr.first + l] ? '<' : '>';
        }
        vl.second -= len, vr.second -= len;
        if (vl.first < 0) vl.first -= len;
        if (vr.first < 0) vr.first -= len;
        if (!ql.front().second) ql.pop();
        if (!qr.front().second) qr.pop();
    }

    if (ql.empty() && qr.empty()) return '=';
    return ql.empty() ? '<' : '>';
}

array<int, 28> getStr(int ql, int qr, int len) {
    array<int, 28> ans;
    for (int i = 0; i < 28; i++) ans[i] = 0;
    ans[27] = len;
    for (int t = 0, cl = ql, cr = qr; t < 26 && qr - cr < ans[27]; t++) {
        int l = lower_bound(pos[t].begin(), pos[t].end(), cl) - pos[t].begin() - 1,
            r = upper_bound(pos[t].begin(), pos[t].end(), cr) - pos[t].begin(), xl = l + 1;

        auto chk = [&](int p) { return (p - xl + 1) <= ans[27] - (qr - cr) && (p - xl + 1) + (qr - pos[t][p]) >= ans[27]; };

        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            (chk(mid) ? l : r) = mid;
        }

        if (l >= xl) ans[t] = l - xl + 1, ans[27] -= ans[t], cl = pos[t][l] + 1;
        if (r < (int)pos[t].size()) cr = min(cr, pos[t][r] - 1);
    }
    ans[26] = qr - ans[27] + 1;
    return ans;
}

void solve(void) {
    string s;
    cin >> s;
    n = s.size();
    hsh.build(s);

    for (int i = 1; i <= n; i++) pos[a[i] = s[i - 1] - 'A'].push_back(i);

    rig[n] = 1;
    for (int i = n - 1; i; i--) rig[i] = (a[i] == a[i + 1] ? rig[i + 1] + 1 : 1);

    int q;
    cin >> q;

    while (q--) {
        int l1, r1, k1, l2, r2, k2;
        cin >> l1 >> r1 >> k1 >> l2 >> r2 >> k2;
        auto ret1 = getStr(l1, r1, k1), ret2 = getStr(l2, r2, k2);
        cout << comp(ret1, ret2) << endl;
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