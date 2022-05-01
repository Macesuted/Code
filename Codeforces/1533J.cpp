/**
 * @file 1533J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-25
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

#define maxn 500005

vector<int> rec[maxn];
vector<int> f[maxn], g[maxn];

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>();
        rec[y].push_back(x);
    }
    for (int i = 0; i < maxn; i++)
        if (!rec[i].empty())
            rec[i].push_back(0), rec[i].push_back(maxn), sort(rec[i].begin(), rec[i].end()), f[i].resize(rec[i].size()),
                g[i].resize(rec[i].size());
    int ans = 0;
    for (int i = 1; i + 1 < maxn; i++) {
        if (rec[i].empty()) continue;
        int siz = rec[i].size(), siz_ = rec[i - 1].size();
        if (i & 1) {
            for (int j = 0, k = 0; j < siz; j++) {
                while (k < siz_ && rec[i - 1][k] < rec[i][j]) k++;
                f[i][j] = j + ((k == siz_) ? 0 : f[i - 1][k]);
            }
            f[i].back()--;
            for (int j = 1; j < siz; j++) f[i][j] = max(f[i][j], f[i][j - 1]);
        } else {
            for (int j = siz - 1, k = siz_ - 1; ~j; j--) {
                while (~k && rec[i - 1][k] > rec[i][j]) k--;
                f[i][j] = siz - j - 1 + ((k == -1) ? 0 : f[i - 1][k]);
            }
            f[i].front()--;
            for (int j = siz - 2; ~j; j--) f[i][j] = max(f[i][j], f[i][j + 1]);
        }
        if (rec[i + 1].empty()) {
            int maxVal = 0;
            for (int j = 1; j + 1 < siz; j++) maxVal = max(maxVal, f[i][j]);
            ans += maxVal;
        }
    }
    for (int i = 1; i + 1 < maxn; i++) {
        if (rec[i].empty()) continue;
        int siz = rec[i].size(), siz_ = rec[i - 1].size();
        if (i & 1) {
            for (int j = siz - 1, k = siz_ - 1; ~j; j--) {
                while (~k && rec[i - 1][k] > rec[i][j]) k--;
                g[i][j] = siz - j - 1 + ((k == -1) ? 0 : g[i - 1][k]);
            }
            g[i].front()--;
            for (int j = siz - 2; ~j; j--) g[i][j] = max(g[i][j], g[i][j + 1]);
        } else {
            for (int j = 0, k = 0; j < siz; j++) {
                while (k < siz_ && rec[i - 1][k] < rec[i][j]) k++;
                g[i][j] = j + ((k == siz_) ? 0 : g[i - 1][k]);
            }
            g[i].back()--;
            for (int j = 1; j < siz; j++) g[i][j] = max(g[i][j], g[i][j - 1]);
        }
        if (rec[i + 1].empty()) {
            int maxVal = 0;
            for (int j = 1; j + 1 < siz; j++) maxVal = max(maxVal, g[i][j]);
            ans += maxVal;
        }
    }
    write(ans - n), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
