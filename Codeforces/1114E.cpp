/**
 * @file 1114E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1000005

vector<int> a;
bool vis[maxn];

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

void solve(void) {
    int n;
    cin >> n;
    int l = 0, r = 1e9, cnt = 60, d = 0, tot = 0;
    while (l < r) {
        int mid = (l + r) >> 1, ret;
        cout << "> " << mid << endl, cin >> ret, cnt--;
        if (ret)
            l = mid + 1;
        else
            r = mid;
    }
    mt19937 rnd(114514);
    while (cnt && tot < n) {
        int p = rnd() % n + 1, v;
        while (vis[p]) p = rnd() % n + 1;
        cnt--, tot++, vis[p] = true, cout << "? " << p << endl, cin >> v, a.push_back(v);
    }
    sort(a.begin(), a.end());
    for (int i = 1; i < (int)a.size(); i++) d = gcd(a[i] - a[i - 1], d);
    cout << "! " << l - d * (n - 1) << ' ' << d << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}