/**
 * @file 1750E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

class FenwickTree {
   private:
    int64_t tree[maxn << 1];

   public:
    void add(int p, int v) {
        p += maxn;
        for (int i = p; i < int(maxn << 1); i += i & -i) tree[i] += v;
        return;
    }
    int64_t query(int p) {
        p += maxn;
        int64_t sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

int a[maxn], b[maxn], c[maxn];
stack<int> pos;

void solve(void) {
    int n;
    string s;
    cin >> n >> s, s = " " + s;
    for (int i = 1; i <= n; i++) a[i] = a[i - 1] + (s[i] == '(' ? +1 : -1);
    int64_t ans = 0, sum = 0;
    for (int i = n; i; i--) {
        FT.add(a[i], 1);
        ans += int64_t(a[i - 1]) * FT.query(a[i - 1]);
    }
    for (int i = 1; i <= n; i++) FT.add(a[i], -1);
    for (int i = 1; i <= n; i++) {
        FT.add(a[i - 1], 1);
        ans += int64_t(a[i]) * FT.query(a[i] - 1);
    }
    for (int i = 1; i <= n; i++) FT.add(a[i - 1], -1);
    while (!pos.empty()) pos.pop();
    pos.push(n), sum = 0;
    for (int i = 0; i < n; i++) a[i] = min(a[i], a[i + 1]);
    for (int l = n - 1; ~l; l--) {
        while (pos.top() < n && a[l] <= a[pos.top()]) {
            int p = pos.top();
            pos.pop();
            sum -= int64_t(a[p]) * (pos.top() - p);
        }
        sum += int64_t(a[l]) * (pos.top() - l), pos.push(l);
        ans -= sum;
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}