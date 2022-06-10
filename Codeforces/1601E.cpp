/**
 * @file 1601E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-10
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

#define maxn 300005
#define maxlgn 20

typedef pair<int, int> pii;

int K, a[maxn], lg2[maxn];
int64_t f[maxn];
pii mn[maxlgn][maxn];

pii minVal(int l, int r) {
    int lglen = lg2[(r - l + 1) / K];
    return min(mn[lglen][l + (K << lglen) - K], mn[lglen][r]);
}

void solve(void) {
    int n, q;
    cin >> n >> q >> K;
    for (int i = 0; i < n; i++) cin >> a[i];
    static deque<int> que;
    for (int i = 0; i < K; i++) {
        while (!que.empty() && a[que.back()] >= a[i]) que.pop_back();
        que.push_back(i);
    }
    for (int i = K; i < n; i++) {
        while (!que.empty() && que.front() < i - K) que.pop_front();
        while (!que.empty() && a[que.back()] >= a[i]) que.pop_back();
        que.push_back(i), mn[0][i] = {a[que.front()], i};
    }
    for (int i = 1; i < maxlgn && (K << i) < n; i++)
        for (int j = (K << i); j < n; j++) mn[i][j] = min(mn[i - 1][j], mn[i - 1][j - (K << (i - 1))]);
    for (int i = 0; i < K; i++) {
        int r = i;
        while (r + K < n) r += K;
        int64_t sum = 0;
        static stack<int> S;
        while (!S.empty()) S.pop();
        S.push(r + K);
        for (int i = r; i >= K; i -= K) {
            while (S.top() <= r && mn[0][S.top()] >= mn[0][i]) {
                int p = S.top();
                S.pop(), sum -= 1LL * mn[0][p].first * (S.top() - p) / K;
            }
            f[i] = (sum += 1LL * mn[0][i].first * (S.top() - i) / K), S.push(i);
        }
    }
    for (int i = 0, l, r; i < q; i++) {
        cin >> l >> r, l--, r--, r = l + (r - l) / K * K;
        if (l == r) {
            cout << a[l] << endl;
            continue;
        }
        int p = minVal(l + K, r).second;
        cout << a[l] + f[l + K] - f[p] + 1LL * mn[0][p].first * ((r - p) / K + 1) << endl;
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}