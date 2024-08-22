/**
 * @file M.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005

typedef pair<int64_t, int> pli;

string a;
pli f[1 << 19];
int64_t pow10[20];

bool mem2;

void solve(void) {
    int64_t y;
    cin >> a;
    cin >> y;
    int n = max(0, (int)a.size() - 18), cnt = 0;
    for (int t = 9; ~t && cnt < n; t--)
        for (int i = 0; i < (int)a.size() && cnt < n; i++)
            if (a[i] - '0' == t) cout << a[i], a[i] = ' ', cnt++;
    n = 0;
    for (int i = 0; i < (int)a.size(); i++)
        if (a[i] != ' ') a[n++] = a[i];
    for (int S = 0; S < (1 << n); S++) {
        int64_t base = pow10[n - 1 - __builtin_popcount(S)];
        for (int i = 0, cnt = 0; i < n; i++)
            if (!(S >> i & 1)) {
                f[S | (1 << i)] = max(f[S | (1 << i)], pli{f[S].first + base * (a[i] - '0') - cnt * y, f[S].second + cnt});
                cnt++;
            }
    }
    int S = (1 << n) - 1;
    f[S].first += f[S].second * y;
    char ans[20];
    for (int i = n - 1; ~i; i--) ans[i] = f[S].first % 10 + '0', f[S].first /= 10;
    for (int i = 0; i < n; i++) cout << ans[i];
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    pow10[0] = 1;
    for (int i = 1; i < 20; i++) pow10[i] = pow10[i - 1] * 10;

    int _ = 1;
    while (_--) solve();

    return 0;
}