/**
 * @file 332.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-18
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

#define maxn 400005

int64_t a[maxn], b[maxn];
deque<int> que;

void solve(void) {
    int n;
    int64_t C;
    cin >> n >> C;
    for (int i = 1; i <= 2 * n - 1; i++) cin >> a[i], a[i] += a[i - 1];
    for (int i = 1, j = 1; i <= n; i++) {
        while (!que.empty() && b[que.back() - 1] - a[2 * que.back() - 2] <= b[i - 1] - a[2 * i - 2]) que.pop_back();
        que.push_back(i);
        while (j <= i && a[2 * i - 1] - a[2 * j - 2] >= C) j++;
        while (!que.empty() && que.front() < j) que.pop_front();
        if (!que.empty()) b[i] = b[que.front() - 1] + a[2 * i - 1] - a[2 * que.front() - 2];
        if (j > 1) b[i] = max(b[i], b[j - 2] + C);
    }
    cout << b[n] << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("shirt.in", "r", stdin), freopen("shirt.out", "w", stdout);
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