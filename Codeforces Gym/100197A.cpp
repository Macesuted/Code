/**
 * @file 100197A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 65
#define maxk 1005

typedef vector<int8_t> bigInt;

int jmp[maxk][30], inq[maxk];
bool tgt[maxk], cont[maxk][30], vis[maxk];
bigInt f[maxn][maxk];

void add(bigInt& a, const bigInt& b) {
    if (a.size() < b.size()) a.resize(b.size());
    for (int i = 0; i < (int)b.size(); i++) a[i] += b[i];
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] < 10) continue;
        if (i + 1 == (int)a.size()) a.push_back(0);
        a[i + 1]++, a[i] -= 10;
    }
    return;
}

void solve(void) {
    string sigma;
    cin >> sigma;
    int m = sigma.size();

    int k;
    cin >> k;

    int S, Tcnt;
    cin >> S >> Tcnt;
    for (int t = 1, x; t <= Tcnt; t++) cin >> x, tgt[x] = true;

    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= m; j++) cin >> jmp[i][j];
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= m; j++) cin >> cont[i][j];
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= k; i++) vis[i] = !cont[i][j];
        for (int i = 1; i <= k; i++) {
            if (vis[i]) continue;
            stack<int> S;
            S.push(i), inq[i]++;
            while (!vis[S.top()] && inq[S.top()] == 1) S.push(jmp[S.top()][j]), inq[S.top()]++;
            if (!vis[S.top()]) jmp[S.top()][j] = 0;
            int ans = jmp[S.top()][j];
            while (!S.empty()) inq[S.top()]--, jmp[S.top()][j] = ans, vis[S.top()] = true, S.pop();
        }
    }

    int n;
    cin >> n;

    f[0][S].push_back(1);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++) {
            if (f[i - 1][j].empty()) continue;
            for (int c = 1; c <= m; c++)
                if (jmp[j][c]) add(f[i][jmp[j][c]], f[i - 1][j]);
        }

    bigInt ans;
    ans.push_back(0);
    for (int i = 1; i <= k; i++)
        if (tgt[i]) add(ans, f[n][i]);

    reverse(ans.begin(), ans.end());
    for (auto x : ans) cout << (int)x;
    cout << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("dfa.in", "r", stdin), freopen("dfa.out", "w", stdout);
#endif
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