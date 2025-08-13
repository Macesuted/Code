/**
 * @file 108306L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

int a[maxn], b[maxn], ans[maxn];

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i], ans[i] = 0;
    sort(b + 1, b + n + 1, greater<int>());

    queue<int> que;
    for (int i = 2; i <= n; i++) que.push(i);

    int cur = 1, cnt = 0, lst = 0;
    while (k && ((++lst <= 2 * n) || !(a[cur] == b[2] && a[que.front()] == b[1]))) {
        int p = que.front();
        que.pop();
        ans[cur]++, ans[p]++, cnt++, k--;
        if (a[cur] < a[p] || cnt == n) swap(cur, p), cnt = 1;
        que.push(p);
    }

    int x = k / (2 * (n - 1));
    k -= 2 * (n - 1) * x;
    for (int i = 1; i <= n; i++) ans[i] += x * 2;
    ans[cur] += x * (n - 2), ans[que.front()] += x * (n - 2);

    while (k) {
        int p = que.front();
        que.pop();
        ans[cur]++, ans[p]++, cnt++, k--;
        if (a[cur] < a[p] || cnt == n) swap(cur, p), cnt = 1;
        que.push(p);
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}