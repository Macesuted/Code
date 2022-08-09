/**
 * @file 2626.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 250005

int f[2][maxn], pf[2][maxn], g[2][maxn], pg[2][maxn], sum[maxn];
string s;
int n, a, b;

int getSum(int l, int r) { return sum[r] - sum[l - 1]; };

void buildf(int lim) {
    for (int i = 0; i <= n; i++) f[0][i] = f[1][i] = INT_MAX;
    f[0][0] = f[1][0] = 0;
    static deque<int> que[2];
    que[0].clear(), que[1].clear(), que[0].push_back(0), que[1].push_back(0);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0') que[1].clear();
        if (s[i] == '1') que[0].clear();
        while (!que[0].empty() && i - que[0].front() > lim) que[0].pop_front();
        while (!que[1].empty() && i - que[1].front() > lim) que[1].pop_front();
        int p[2] = {(que[0].empty() ? -1 : que[0].front()), (que[1].empty() ? -1 : que[1].front())};
        for (int t = 0; t < 2; t++)
            if ((s[i] == '?' || s[i] == '0' + t) && ~p[t]) {
                f[t][i] = f[!t][pf[t][i] = p[t]];
                if (!t) f[t][i] += getSum(que[t].front() + 1, i);
                while (!que[!t].empty() && (t ? (f[t][que[!t].back()] + getSum(que[!t].back() + 1, i) > f[t][i])
                                              : (f[t][que[!t].back()] > f[t][i])))
                    que[!t].pop_back();
                que[!t].push_back(i);
            }
    }
    return;
}
void buildg(int lim) {
    for (int i = 0; i <= n; i++) g[0][i] = g[1][i] = INT_MIN;
    g[0][0] = g[1][0] = 0;
    static deque<int> que[2];
    que[0].clear(), que[1].clear(), que[0].push_back(0), que[1].push_back(0);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0') que[1].clear();
        if (s[i] == '1') que[0].clear();
        while (!que[0].empty() && i - que[0].front() > lim) que[0].pop_front();
        while (!que[1].empty() && i - que[1].front() > lim) que[1].pop_front();
        int p[2] = {(que[0].empty() ? -1 : que[0].front()), (que[1].empty() ? -1 : que[1].front())};
        for (int t = 0; t < 2; t++)
            if ((s[i] == '?' || s[i] == '0' + t) && ~p[t]) {
                g[t][i] = g[!t][pg[t][i] = p[t]];
                if (!t) g[t][i] += getSum(que[t].front() + 1, i);
                while (!que[!t].empty() && (t ? (g[t][que[!t].back()] + getSum(que[!t].back() + 1, i) < g[t][i])
                                              : (g[t][que[!t].back()] < g[t][i])))
                    que[!t].pop_back();
                que[!t].push_back(i);
            }
    }
    return;
}
void buildgr(int lim) {
    for (int i = 1; i <= n + 1; i++) g[0][i] = g[1][i] = INT_MIN;
    g[0][n + 1] = g[1][n + 1] = 0;
    static deque<int> que[2];
    que[0].clear(), que[1].clear(), que[0].push_back(n + 1), que[1].push_back(n + 1);
    for (int i = n; i; i--) {
        if (s[i] == '0') que[1].clear();
        if (s[i] == '1') que[0].clear();
        while (!que[0].empty() && que[0].front() - i > lim) que[0].pop_front();
        while (!que[1].empty() && que[1].front() - i > lim) que[1].pop_front();
        int p[2] = {(que[0].empty() ? -1 : que[0].front()), (que[1].empty() ? -1 : que[1].front())};
        for (int t = 0; t < 2; t++)
            if ((s[i] == '?' || s[i] == '0' + t) && ~p[t]) {
                g[t][i] = g[!t][pg[t][i] = p[t]];
                if (!t) g[t][i] += getSum(i, que[t].front() - 1);
                while (!que[!t].empty() && (t ? (g[t][que[!t].back()] + getSum(i, que[!t].back() - 1) < g[t][i])
                                              : (g[t][que[!t].back()] < g[t][i])))
                    que[!t].pop_back();
                que[!t].push_back(i);
            }
    }
    return;
}

void solve(void) {
    cin >> n >> a >> b >> s, s = " " + s;
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (s[i] == '?');
    int l = 0, r = n;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        buildf(mid), buildg(mid);
        ((min(f[0][n], f[1][n]) <= a && a <= max(g[0][n], g[1][n])) ? r : l) = mid;
    }
    cout << r << endl;
    buildf(r), buildgr(r);
    for (int i = 0; i <= n; i++)
        for (int t = 0; t < 2; t++)
            if (f[t][i] != INT_MAX && g[!t][i + 1] != INT_MIN && f[t][i] + g[!t][i + 1] == a) {
                string ans;
                ans.resize(n);
                for (int p = i, c = t; p; p = pf[c][p], c = !c)
                    for (int i = pf[c][p] + 1; i <= p; i++) ans[i - 1] = '0' + c;
                for (int p = i + 1, c = !t; p <= n; p = pg[c][p], c = !c)
                    for (int i = p; i < pg[c][p]; i++) ans[i - 1] = '0' + c;
                cout << ans << endl;
                return;
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}