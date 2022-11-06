/**
 * @file 1718D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#ifndef LOCAL
#define end '\n'
#endif

#define maxn 300005
#define maxlgn 20

typedef pair<int, int> pii;

int a[maxn], b[maxn], c[maxn], v[maxn], id[maxn], lg2[maxn];
pii ST[maxlgn][maxn], ques[maxn];
priority_queue<int, vector<int>, greater<int>> que;

pii getMax(int l, int r) {
    int lgLen = lg2[r - l + 1];
    return max(ST[lgLen][l], ST[lgLen][r - (1 << lgLen) + 1]);
}

bool chk;
int build(int l, int r, int up = INT_MAX) {
    if (l > r) return 0;
    int p = getMax(l, r).second;
    if (a[p] == 0) return ques[id[p]] = {max(build(l, p - 1, up), build(p + 1, r, up)) + 1, up - 1}, ques[id[p]].first - 1;
    if (a[p] < up) return build(l, p - 1, a[p]), build(p + 1, r, a[p]), a[p];
    return chk = false, -1;
}

int need;
bool match(int m, int x) {
    int n = m - 1;
    for (int i = 1; i <= n; i++) v[i] = c[i];
    if (x != -1) v[++n] = x;
    for (int i = n - 1; i; i--)
        if (v[i] > v[i + 1]) swap(v[i], v[i + 1]);
    while (!que.empty()) que.pop();
    int j = 1;
    for (int i = 1; i <= n; i++) {
        while (j <= m && ques[j].first <= v[i]) que.push(ques[j].second), j++;
        while (!que.empty() && que.top() < v[i])
            if (x == -1)
                need = que.top(), que.pop(), x = 0;
            else
                return false;
        if (que.empty()) return false;
        que.pop();
    }
    while (j <= m) que.push(ques[j].second), j++;
    if (!que.empty()) need = que.top();
    return true;
}

void solve(void) {
    int n, m = 0, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> b[i], ST[0][i] = {b[i], i};
    for (int i = 1; i <= n; i++) cin >> a[i], id[i] = (m += (a[i] == 0));
    for (int i = 1; i < m; i++) cin >> c[i];
    for (int i = 1; i < maxlgn; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++) ST[i][j] = max(ST[i - 1][j], ST[i - 1][j + (1 << (i - 1))]);
    chk = true, build(1, n), sort(ques + 1, ques + m + 1), sort(c + 1, c + m), chk &= match(m, -1);
    int L = need, R = need;
    if (match(m, 1))
        L = 1;
    else {
        int l = 1, &r = L;
        while (int64_t(l) + 1 < r) {
            int mid = (int64_t(l) + r) >> 1;
            (match(m, mid) ? r : l) = mid;
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << (chk && L <= x && x <= R ? "YES" : "NO") << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxn; i++) lg2[i] = lg2[i >> 1] + 1;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}