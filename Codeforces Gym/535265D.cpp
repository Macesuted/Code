/**
 * @file 535265D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-17
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

#define maxlgn 25

class FenwickTree {
   private:
    vector<int> tree;

   public:
    void resize(uint64_t s) { return tree.resize(s + 1); }
    void update(int p, int v) {
        for (int i = p + 1; i < (int)tree.size(); i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p + 1; i; i -= i & -i) sum += tree[i];
        return sum;
    }
    int sum(int l, int r) { return sum(r) - sum(l - 1); }
};

FenwickTree FT[maxlgn];
stack<int> S;

int Mod(int v, int x) { return (v % x + x) % x; }

void solve(void) {
    int q;
    cin >> q;

    S.push(0);
    for (int i = 0; i < 21; i++) FT[i].resize(1 << (i + 1)), FT[i].update(0, +1);

    while (q--) {
        int t, v;
        cin >> t >> v;

        while (t--) {
            int p = S.top();
            S.pop();
            for (int i = 0; i < 21; i++) FT[i].update(Mod(-p, 1 << (i + 1)), -1);
        }

        v += S.top(), S.push(v);

        for (int i = 0; i < 21; i++) FT[i].update(Mod(-v, 1 << (i + 1)), +1);

        int ans = 0;
        for (int i = 0; i < 21; i++) {
            int mod = 1 << (i + 1), l = (1 << i) - Mod(v, mod), r = mod - 1 - Mod(v, mod), cnt = 0;
            if (l < 0) l += mod, r += mod;
            if (r < mod)
                cnt = FT[i].sum(l, r);
            else
                cnt = FT[i].sum(l, mod - 1) + FT[i].sum(0, r - mod);
            if (cnt & 1) ans |= 1 << i;
        }
        cout << ans << endl;
    }
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