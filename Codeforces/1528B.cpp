/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1000005
#define mod 998244353

long long f[maxn], g[maxn];

long long power(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

bool vis[maxn];
int num[maxn], d[maxn];
vector<int> prime;

void init(void) {
    for (register int i = 2; i < maxn; i++) {
        if (!vis[i]) prime.push_back(i), num[i] = 1, d[i] = 2;
        for (vector<int>::iterator j = prime.begin(); i * *j < maxn; j++) {
            vis[i * *j] = true;
            if (i % *j == 0) {
                num[i * *j] = num[i] + 1;
                d[i * *j] = d[i] / (num[i] + 1) * (num[i * *j] + 1);
                break;
            }
            d[i * *j] = d[i] * d[*j];
            num[i * *j] = 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    init();
    f[1] = g[1] = 1;
    for (register int i = 2; i <= n; i++) {
        f[i] = (f[i - 1] + g[i - 1]) % mod, g[i] = f[i] + d[i] - 1;
    }
    cout << g[n] << endl;
    return 0;
}