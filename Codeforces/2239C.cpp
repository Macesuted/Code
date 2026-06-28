/**
 * @file 2239C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
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
    vector<int> a;
    int n;

   public:
    void resize(int _n) { return a.resize((n = _n) + 1); }
    void add(int p, int v) {
        for (int i = p; i <= n; i += i & -i) a[i] += v;
        return;
    }
    int sum(int p) {
        int ans = 0;
        for (int i = p; i; i -= i & -i) ans += a[i];
        return ans;
    }
};

int64_t a[maxn];
int p[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c >> a[i];
        if (c == 'p') a[i] = -a[i];
    }

    FenwickTree FT, tmp;
    FT.resize(n), tmp.resize(n);
    for (int i = 1; i <= n; i++) FT.add(i, +1);

    int r = n;
    while (r && a[r] < 0) FT.add(p[r] = -a[r], -1), r--;

    while (r) {
        int l = r - 1;
        while (l && a[l] < 0) l--;

        int64_t delt = a[r] - a[l];
        for (int i = r - 1; i > l; i--) delt -= i + 1 - FT.sum(p[i] = -a[i]), FT.add(-a[i], -1);

        vector<int> vals;
        for (int i = r - 1; i > l; i--) FT.add(p[i], +1), vals.push_back(p[i]);

        vals.push_back(0), vals.push_back(n + 1);
        sort(vals.begin(), vals.end());

        for (size_t t = 0; t + 1 < vals.size(); t++, delt++) {
            int vl = vals[t], vr = vals[t + 1] - 1;

            if (r - FT.sum(vr) > delt) continue;
            if (r - FT.sum(vl) <= delt) continue;

            while (vl + 1 < vr) {
                int mid = (vl + vr) >> 1;
                (r - FT.sum(mid) > delt ? vl : vr) = mid;
            }

            p[r] = vr;
            break;
        }

        FT.add(p[r], -1);
        for (int i = r - 1; i > l; i--) FT.add(p[i], -1), tmp.add(p[i], -1);

        r = l;
    }

    for (int i = 1; i <= n; i++) cout << p[i] << ' ';
    cout << endl;

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
