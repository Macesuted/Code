#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005

long long gcd(long long x, long long y) { return y == 0 ? x : gcd(y, x % y); }

int a[maxn];

bool solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    long long lcm = 1;
    for (int i = 1; i <= n && lcm <= 1e9; i++) {
        lcm = lcm / gcd(lcm, (i + 1)) * (i + 1);
        if (a[i] % lcm == 0) return false;
    }
    return true;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;
    ios::sync_with_stdio(false);

    int _ = 1;
    cin >> _;
    while (_--) cout << (solve() ? "YES" : "NO") << endl;

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}