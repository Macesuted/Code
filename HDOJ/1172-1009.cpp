/**
 * @file 1172-1009.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 2000005

namespace FastIO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Ir = Ibuf, *Il = Ibuf;
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
int read(void) {
    int x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
}  // namespace FastIO
using FastIO::read;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int ans = 0;
        for (int i = p; i; i -= i & -i) ans += tree[i];
        return ans;
    }
} FT;

int a[maxn], pos[maxn];

void solve(void) {
    int n = read();

    for (int i = 1; i <= n; i++) pos[a[i] = read()] = i;

    auto calc = [&](int l, int r) -> int {
        if (l > r) return 0;
        return FT.sum(r) - FT.sum(l - 1) + 1;
    };

    int ans = 1;
    for (int v = 1, l = 1, r = n; v < n; v++) {
        while (a[l] <= v) l++;
        while (a[r] <= v) r--;
        int p = pos[v];
        FT.add(p, +1);
        ans = max({ans, calc(l, p), calc(p, r)});
    }

    for (int v = 1; v < n; v++) FT.add(pos[v], -1);

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = read();
    while (_--) solve();

    return 0;
}
