/**
 * @file arc120_d-2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-17
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

#define maxn 400005

using pii = pair<int, int>;

pii a[maxn];
bool plu[maxn];
char ans[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= 2 * n; i++) cin >> a[i].first, a[i].second = i;
    sort(a + 1, a + 2 * n + 1);
    for (int i = n + 1; i <= 2 * n; i++) plu[a[i].second] = true;
    for (int i = 1, pre = 0; i <= 2 * n; i++) {
        if (plu[i])
            ans[i] = "()"[pre > 0], pre--;
        else
            ans[i] = "()"[pre < 0], pre++;
    }
    for (int i = 1; i <= 2 * n; i++) cout << ans[i];
    cout << endl;
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