/**
 * @file 105053G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

double p[maxn], f[maxn];
bool notPrime[maxn];
vector<int> num[maxn], prime;
vector<pii> primeNum[maxn];

void solve(void) {
    int n;
    cin >> n;
    double psum = 0;
    for (int i = 1; i <= n; i++) cin >> p[i], psum += p[i];
    for (int i = 1; i <= n; i++) p[i] /= psum;

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i) num[j].push_back(i);
    for (int i = 1; i <= n; i++) {
        int x = i;
        for (auto j = prime.begin(); *j * *j <= x; j++) {
            int cnt = 1;
            while (x % *j == 0) cnt *= *j, x /= *j;
            if (cnt) primeNum[i].emplace_back(*j, cnt);
        }
        if (x > 1) primeNum[i].emplace_back(x, x);
    }

    for (int x = n; x; x--) {
        double own = 0;
        for (int lcm = x; lcm <= n; lcm += x) {
            int base = 1, extra = 1;
            for (auto i = primeNum[x].begin(), j = primeNum[lcm].begin(); j != primeNum[lcm].end(); j++)
                if (i != primeNum[x].end() && i->first == j->first) {
                    if (i->second < j->second)
                        base *= j->second;
                    else
                        extra *= i->second;
                    i++;
                } else
                    base *= j->second;
            for (auto y : num[extra]) {
                if (base * y > n) break;
                if (lcm == x)
                    own += p[base * y];
                else
                    f[x] += p[base * y] * (f[lcm] + 1);
            }
        }
        f[x] = (own + f[x]) / (1 - own);
    }
    cout << setprecision(10) << fixed << f[1] << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("G.in", "r", stdin);
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxn; i++) {
        if (!notPrime[i]) prime.push_back(i);
        for (auto j = prime.begin(); j != prime.end() && i * *j < maxn; j++) {
            notPrime[i * *j] = true;
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}