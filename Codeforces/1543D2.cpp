/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

int ask(int x) {
    cout << x << endl;
    int t;
    cin >> t;
    return t;
}

int Xor(int x, int y, int base) {
    static stack<int> S;
    while (!S.empty()) S.pop();
    while (x || y) {
        int tx = x % base, ty = y % base;
        x /= base, y /= base;
        S.push((tx + ty) % base);
    }
    int ans = 0;
    while (!S.empty()) ans = ans * base + S.top(), S.pop();
    return ans;
}
int Minus(int x, int y, int base) {
    static stack<int> S;
    while (!S.empty()) S.pop();
    while (x || y) {
        int tx = x % base, ty = y % base;
        x /= base, y /= base;
        S.push((tx - ty + base) % base);
    }
    int ans = 0;
    while (!S.empty()) ans = ans * base + S.top(), S.pop();
    return ans;
}

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (register int i = 0, pre = 0, t = 1; i < n; i++, t = -t) {
        int a;
        if (t == 1)
            a = Xor(pre, i, k);
        else
            a = Minus(pre, i, k);
        int ret = ask(a);
        if (ret == 1) return;
        pre = Minus(a, pre, k);
    }
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(8);
    int _ = 1;
    cin >> _;
    while (_--) solve();
    return 0;
}