/**
 * @file 1171.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

typedef pair<int, int> pii;

void solve(void) {
    int n;
    cin >> n;
    stack<pii> S;
    S.emplace(0x3f3f3f3f, 0);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while (S.top().first <= x) ans += i - S.top().second + 1, S.pop();
        if (S.top().second) ans += i - S.top().second + 1;
        S.emplace(x, i);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
