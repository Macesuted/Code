/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 100005

bool use[maxn];

string a, b;

void work(void) {
    int n;
    cin >> n >> a >> b;
    a = ' ' + a, b = ' ' + b;
    int answer = 0;
    for (register int i = 1; i <= n; i++) use[i] = false;
    for (register int i = 1; i <= n; i++)
        if (a[i] != b[i]) answer += 2, use[i] = true;
    for (register int i = 1; i < n; i++) {
        if (use[i] || use[i + 1]) continue;
        if (a[i] != a[i + 1]) use[i] = use[i + 1] = true, answer += 2;
    }
    for (register int i = 1; i <= n; i++)
        if (!use[i] && a[i] == '0') answer++;
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}