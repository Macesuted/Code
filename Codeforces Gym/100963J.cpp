/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = getchar()) x = x * 10 + (c & 15);
    return x * f;
}

#define int long long

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) return x = 1, y = 0, a;
    int g = exgcd(b, a % b, x, y);
    return tie(x, y) = make_tuple(y, x - a / b * y), g;
}
bool getAns(int a, int b, int c, int &x, int &y) {
    int g = exgcd(abs(a), abs(b), x, y);
    if (g == 0 || c % g) return false;
    x *= c / g, y *= c / g;
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}

int solve(int n, int m, int a, int k) {
    if (m == 0 && a == 0) {
        if (n == k) return n;
        return -1;
    }
    if (m == 0) {
        if (n > k && (n - k) % a == 0) return n;
        return -1;
    }
    if (a == 0) {
        if (k >= n && (k - n) % m == 0) return k;
        return -1;
    }
    int x, y;
    bool ret = getAns(m, -a, k - n, x, y);
    if (!ret) return -1;
    int da = m / gcd(m, a), dm = a / gcd(m, a), p = -x / dm;
    while (x + dm * p < 0) p++;
    while (y + da * p <= 0) p++;
    x += dm * p, y += da * p;
    return n + m * x;
}

signed main() {
    ios::sync_with_stdio(false);
    int n = read<int>(), m = read<int>(), a = read<int>(), k = read<int>();
    while (n + m + a + k) {
        int ret = solve(n, m, a, k);
        if (ret == -1)
            cout << "Impossible" << endl;
        else
            cout << ret << endl;
        n = read<int>(), m = read<int>(), a = read<int>(), k = read<int>();
    }
    return 0;
}