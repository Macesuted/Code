/**
 * @file 1583G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-24
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
#define max2n 400005
#define mod 1000000007

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[max2n];

   public:
    void add(int p, int v) {
        for (int i = p; i < max2n; i += i & -i) tree[i] = (tree[i] + v) % mod;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum = (sum + tree[i]) % mod;
        return sum;
    }
} FT;

pii a[maxn];
int f[maxn];
bool mark[max2n];

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[i].second = read<int>(), a[i].first = read<int>();
    int m = read<int>();
    for (int i = 1; i <= m; i++) mark[a[read<int>()].first] = true;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) FT.add(a[i].second, f[i] = (mod + 1LL + FT.sum(2 * n) - FT.sum(a[i].second)) % mod);
    int ans = 0;
    for (int i = n, pl = 0; i; i--) {
        if (mark[a[i].first]) pl = max(pl, a[i].second);
        if (pl >= a[i].second) ans = (ans + f[i]) % mod;
    }
    write((ans) % mod), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
