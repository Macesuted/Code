/**
 * @file ZJOI2022B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 200005
#define maxsqrtn 500

int a[maxn], va[maxn], pre[maxn], fr[maxsqrtn][maxn], maxCnt, ans[maxn];
vector<int> pos[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], va[i] = a[i], ans[i] = 0;
    sort(va + 1, va + n + 1);
    int cntc = unique(va + 1, va + n + 1) - va - 1;
    for (int i = 1; i <= cntc; i++) pos[i].clear();
    for (int i = 1; i <= n; i++) pos[a[i] = lower_bound(va + 1, va + cntc + 1, a[i]) - va].push_back(i);
    int B = sqrt(n);
    for (int c = 1; c <= cntc; c++) {
        int csiz = pos[c].size();
        if (csiz <= B) continue;
        for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + (a[i] == c);
        for (int oc = 1; oc <= cntc; oc++) {
            if (oc == c) continue;
            int f = 0, siz = pos[oc].size();
            for (int i = 0; i < siz; i++)
                f = max(f, i + 1 - pre[pos[oc][i]]), ans[oc] = max(ans[oc], siz + pre[pos[oc][i]] - i + f);
            ans[oc] = max(ans[oc], csiz + f);
        }
        for (int oc = 1; oc <= cntc; oc++) {
            if (oc == c) continue;
            int f = 0, siz = pos[oc].size();
            for (int i = 0; i < siz; i++)
                f = max(f, pre[pos[oc][i]] - i), ans[c] = max(ans[c], csiz + i + 1 - pre[pos[oc][i]] + f);
            ans[c] = max(ans[c], siz + f);
        }
    }
    for (int i = 1; i <= B; i++)
        for (int j = 1; j <= n; j++) fr[i][j] = n + 1;
    for (int c = 1; c <= cntc; c++) {
        int csiz = pos[c].size();
        if (csiz > B) continue;
        for (int l = 1; l <= csiz; l++)
            for (int i = 0; i + l - 1 < csiz; i++) fr[l][pos[c][i]] = min(fr[l][pos[c][i]], pos[c][i + l - 1]);
    }
    for (int i = 1; i <= B; i++)
        for (int j = n - 1; j; j--) fr[i][j] = min(fr[i][j], fr[i][j + 1]);
    for (int c = 1; c <= cntc; c++) {
        if ((int)pos[c].size() > B) continue;
        {
            auto j = pos[c].begin();
            for (int k = 1; k <= B && fr[k][1] <= n; k++) {
                while (j != pos[c].end() && *j <= fr[k][1]) j++;
                ans[c] = max(ans[c], k + int(pos[c].end() - j));
            }
        }
        for (auto i = pos[c].begin(); i != pos[c].end() && *i < n; i++) {
            auto j = i;
            for (int k = 1; k <= B && fr[k][*i + 1] <= n; k++) {
                while (j != pos[c].end() && *j <= fr[k][*i + 1]) j++;
                ans[c] = max(ans[c], int(i - pos[c].begin() + 1) + k + int(pos[c].end() - j));
            }
        }
    }
    int maxAns = 0;
    for (int i = 1; i <= cntc; i++) maxAns = max(maxAns, ans[i]);
    cout << maxAns << endl;
    for (int i = 1; i <= cntc; i++)
        if (ans[i] == maxAns) cout << va[i] << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    freopen("mode.in", "r", stdin), freopen("mode.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}