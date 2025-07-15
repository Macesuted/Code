/**
 * @file 108298H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

namespace FastIO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf;
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
using namespace FastIO;

class SegmentTree {
   private:
    bool tree[maxn];

   public:
    void flip(int p) {
        for (int i = p; i < maxn; i += i & -i) tree[i] ^= true;
        return;
    }
    bool query(int p) {
        bool ans = false;
        for (int i = p; i; i -= i & -i) ans ^= tree[i];
        return ans;
    }
} ST;

bool a[maxn];

void solve(void) {
    int n = read(), q = read();
    for (int i = 1; i <= n; i++) {
        char c = getch();
        while (c != '0' && c != '1') c = getch();
        a[i] = (c == '1');
    }
    for (int i = n; i >= 1; i--) {
        a[i] = a[i] ^ a[i - 1];
        if (a[i]) ST.flip(i);
    }

    while (q--) {
        int op = read();
        if (op == 1) {
            int l = read(), r = read();
            a[l] = !a[l], a[r + 1] = !a[r + 1];
            ST.flip(l), ST.flip(r + 1);
        } else {
            int l = read(), x = read(), y = read();
            bool pre = ST.query(x - 1) ^ ST.query(y - 1) ^ true;
            int64_t ans = 0, cur = 0;
            for (int i = 1; i <= l; i++) {
                pre ^= a[x + i - 1] ^ a[y + i - 1];
                cur += pre;
                cur *= pre;
                ans += cur;
            }
            cout << ans << endl;
        }
    }
    cerr << clock() << endl;

    return;
}

int main() {
    int _ = 1;
    while (_--) solve();

    return 0;
}
