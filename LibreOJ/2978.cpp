/**
 * @file 2978.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 7005
#define maxp 455
#define maxv 10000005
#define mod 998244353

class Basis {
   private:
    bitset<maxp> a[maxp];
    map<int, bitset<maxp>> b;

   public:
    int cnt;

    Basis(void) { cnt = 0; }
    void insert(bitset<maxp> x, int y) {
        if (y != 1) {
            if (!b.count(y)) {
                b[y] = x;
                return;
            }
            x ^= b[y];
        }
        for (int i = 0; i < maxp; i++)
            if (x[i]) {
                if (a[i].any()) {
                    x ^= a[i];
                    continue;
                }
                a[i] = x;
                return;
            }
        cnt++;
        return;
    }
};

bool notp[maxv];
int bef[maxv], id[maxv];
vector<int> prime;
bitset<maxp> a[maxn];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int f(int l, int r, int64_t a) { return r / a - (l - 1) / a; }

void solve(void) {
    int l, r;
    cin >> l >> r;
    if (r - l + 1 > 7000) {
        int cnt = r - l + 1;
        for (auto i : prime)
            if (f(l, r, i) && (1LL * i * i > r || f(l, r, i) != f(l, r, i * i))) cnt--;
        cout << Pow(2, cnt) << endl;
        return;
    }
    Basis basis;
    for (int i = l; i <= r; i++) {
        bitset<maxp> x;
        int y = 1, t = i;
        if (1LL * bef[t] * bef[t] > r) y = bef[t], t /= bef[t];
        while (t > 1) x.flip(id[bef[t]]), t /= bef[t];
        basis.insert(x, y);
    }
    cout << Pow(2, basis.cnt) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxv; i++) {
        if (!notp[i]) prime.push_back(i), id[i] = prime.size() - 1, bef[i] = i;
        for (auto j = prime.begin(); i * *j < maxv; j++) {
            notp[i * *j] = true, bef[i * *j] = bef[i];
            if (i % *j == 0) break;
        }
    }

    int _;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}