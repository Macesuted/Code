/**
 * @file 7533.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int64_t read() {
    int64_t res = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') {
        res = res * 10 + ch - '0';
        ch = getchar();
    }
    return res;
}

void solve(void) {
    bool a[2] = {false, false};
    int64_t k = read(), x = read(), y = read();
    if (x > y) swap(x, y);
    int64_t n = (k - 1) / y + 1;
    int t = n & 1;
    a[!t] = true;
    if (n * x < k) a[t] = true;
    for (int i = 0; i < 2; i++) cout << (a[i] ? "Yes" : "No") << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = read();
    while (_--) solve();

    return 0;
}