/**
 * @file 1444D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
inline void putch(char x) {
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
    for (register int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
inline T read() {
    register T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
inline void write(const T& t) {
    register T x = t;
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

#define maxn 1005

vector<int> a[2], b[2];
int f[maxn * maxn], del[maxn];
int len[2];

bool solve(int n, vector<int>& x, vector<int>& y) {
    int sum = 0;
    for (auto i : x) sum += i;
    if (sum & 1) return false;
    sum >>= 1;
    for (int i = 1; i <= sum; i++) f[i] = -1;
    f[0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = sum; j >= x[i]; j--)
            if (f[j] < 0 && f[j - x[i]] >= 0) f[j] = j - x[i];
    if (f[sum] < 0) return false;
    int p = sum;
    while (p) y.push_back(f[p] - p), del[p - f[p]]++, p = f[p];
    vector<int> cache;
    for (auto i : x)
        if (del[i])
            del[i]--;
        else
            cache.push_back(i);
    x = cache;
    return true;
}

void solve(void) {
    a[0].clear(), a[1].clear(), b[0].clear(), b[1].clear();
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[0].push_back(read<int>());
    int m = read<int>();
    for (int i = 1; i <= m; i++) b[0].push_back(read<int>());
    if (n != m || !solve(n, a[0], a[1]) || !solve(m, b[0], b[1])) return putstr("NO\n");
    putstr("YES\n");
    int p = 0;
    if (a[0].size() <= b[0].size()) {
        cerr << "???" << endl;
        sort(a[0].begin(), a[0].end(), greater<int>()), sort(a[1].begin(), a[1].end());
        sort(b[0].begin(), b[0].end()), sort(b[1].begin(), b[1].end(), greater<int>());
    } else {
        p = 1;
        sort(a[0].begin(), a[0].end()), sort(a[1].begin(), a[1].end(), greater<int>());
        sort(b[0].begin(), b[0].end(), greater<int>()), sort(b[1].begin(), b[1].end());
    }
    a[0].insert(a[0].end(), a[1].begin(), a[1].end());
    b[0].insert(b[0].end(), b[1].begin(), b[1].end());
    reverse(a[0].begin(), a[0].end()), reverse(b[0].begin(), b[0].end());
    for (auto x = 0, y = 0; n; n--)
        if (!p) {
            x += a[0].back(), a[0].pop_back();
            write(x), putch(' '), write(y), putch('\n');
            y += b[0].back(), b[0].pop_back();
            write(x), putch(' '), write(y), putch('\n');
        } else {
            y += b[0].back(), b[0].pop_back();
            write(x), putch(' '), write(y), putch('\n');
            x += a[0].back(), a[0].pop_back();
            write(x), putch(' '), write(y), putch('\n');
        }
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    int _ = read<int>();
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}