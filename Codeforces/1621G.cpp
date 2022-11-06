/**
 * @file 1621G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
}
string getstr(void) {
    string s = "";
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) s.push_back(c), c = getch();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
    T x = t;
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putch(qu[qr--]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

bool mem1;

#define maxn 200005
#define mod 1000000007

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & (-i)) tree[i] = (tree[i] + v) % mod;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & (-i)) sum = (sum + tree[i]) % mod;
        return sum;
    }
} FT;

int a[maxn], f[maxn], g[maxn], r[maxn];
pii b[maxn];

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) b[i] = {a[i] = read<int>(), i};
    sort(b + 1, b + n + 1, [](pii a, pii b) { return a.first < b.first || (a.first == b.first && a.second > b.second); });
    for (int i = 1; i <= n; i++) FT.add(b[i].second, f[b[i].second] = (FT.sum(b[i].second) + 1) % mod);
    for (int i = 1; i <= n; i++) FT.add(i, -f[i]);
    sort(b + 1, b + n + 1, [](pii a, pii b) { return a.first > b.first || (a.first == b.first && a.second < b.second); });
    for (int i = 1; i <= n; i++) FT.add(b[i].second, g[b[i].second] = (FT.sum(n) + mod - FT.sum(b[i].second) + 1) % mod);
    for (int i = 1; i <= n; i++) FT.add(i, -g[i]);
    vector<pii> sta;
    for (int i = n, last = 0; i; i--)
        if (a[i] > last) last = a[i], sta.emplace_back(a[i], i);
    for (int i = 1; i <= n; i++) r[i] = lower_bound(sta.begin(), sta.end(), pii{a[i], 0})->second;
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + 1LL * f[i] * g[i]) % mod;
    stack<pii> cache;
    for (int i = 1, p = 0; i <= n; i++) {
        if (r[b[i].second] != p && b[i].second == r[b[i].second]) {
            while (!cache.empty()) FT.add(cache.top().first, -cache.top().second), cache.pop();
            p = r[b[i].second];
            FT.add(p, 1), cache.emplace(p, 1);
            ans = (ans + mod - f[b[i].second] % mod) % mod;
        } else {
            int cnt = (FT.sum(n) + mod - FT.sum(b[i].second)) % mod;
            if (b[i].second > p) cnt = 1;
            FT.add(b[i].second, cnt), cache.emplace(b[i].second, cnt),
                ans = (ans + mod - 1LL * cnt * f[b[i].second] % mod) % mod;
        }
    }
    while (!cache.empty()) FT.add(cache.top().first, -cache.top().second), cache.pop();
    return write(ans), putch('\n');
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
