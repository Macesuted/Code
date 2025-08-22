/**
 * @file H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 300005
#define maxlgn 20

using tiii = tuple<int, int, int>;

int nxt[maxn], ans[maxn], jmp[maxlgn][maxn];
vector<vector<tiii>> ques;

void solve(void) {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s, s = ' ' + s;

    nxt[n] = n;
    for (int i = n - 1; i; i--) nxt[i] = (s[i] == '1' ? nxt[i + 1] : i);

    int B = sqrt(q / log(n));
    ques.resize(B + 1);
    for (int i = 1, x, y, k; i <= q; i++) {
        cin >> x >> y >> k;
        if (x > y) swap(x, y);
        if (k <= B)
            ques[k].emplace_back(x, y, i);
        else {
            x = nxt[x];
            while (x < y) ans[i]++, x = nxt[min(x + k, n)];
        }
    }

    for (int k = 1; k <= B; k++) {
        if (ques[k].empty()) continue;

        for (int i = 1; i <= n; i++) jmp[0][i] = nxt[min(n, nxt[i] + k)];
        for (int t = 1; t < maxlgn; t++)
            for (int i = 1; i <= n; i++) jmp[t][i] = jmp[t - 1][jmp[t - 1][i]];

        for (auto [l, r, id] : ques[k]) {
            l = nxt[l];
            if (l >= r) {
                ans[id] = 0;
                continue;
            }
            ans[id] = 1;
            for (int t = maxlgn - 1; ~t; t--)
                if (jmp[t][l] < r) l = jmp[t][l], ans[id] += 1 << t;
        }
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}