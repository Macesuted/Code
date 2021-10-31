#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 100005

long long gcd(long long x, long long y) { return y == 0 ? x : gcd(y, x % y); }

int a[maxn];

void solve(void) {
    int x, y;
    cin >> x >> y;
    if (x > y)
        cout << x + y << endl;
    else if (x == y)
        cout << x << endl;
    else
        cout << y - y % x / 2 << endl;
    return;
}

bool mem2;

signed main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;
    ios::sync_with_stdio(false);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}