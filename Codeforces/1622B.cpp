/**
 * @file 1622B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

int a[maxn], p[maxn];
bool s[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        s[i] = (c == '1');
    }
    priority_queue<pii, vector<pii>, greater<pii>> S;
    for (int i = 1; i <= n; i++)
        if (s[i]) S.emplace(a[i], i);
    for (int i = n - (int)S.size() + 1; i <= n; i++) p[S.top().second] = i, S.pop();
    for (int i = 1; i <= n; i++)
        if (!s[i]) S.emplace(a[i], i);
    for (int i = 1, ts = S.size(); i <= ts; i++) p[S.top().second] = i, S.pop();
    for (int i = 1; i <= n; i++) cout << p[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
