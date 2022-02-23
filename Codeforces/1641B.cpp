/**
 * @file 1641B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-23
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

#define maxn 505

typedef pair<int, int> pii;

int a[maxn];
vector<pii> options;
vector<int> answer;

void solve(void) {
    answer.clear(), options.clear();
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>();
    for (int l = 1, delt = 0; l <= n; l += 2) {
        int r = l + 1;
        while (r <= n && a[l] != a[r]) r++;
        if (r > n) return putstr("-1\n");
        int t = 0;
        stack<int> cache;
        for (int i = l + 1; i < r; i++) options.emplace_back(r + t + delt, a[i]), t++, cache.push(a[i]);
        delt += 2 * t, answer.push_back((r - l) * 2);
        while (!cache.empty()) a[r - (int)cache.size() + 1] = cache.top(), cache.pop();
    }
    write((int)options.size()), putch('\n');
    for (auto i : options) write(i.first), putch(' '), write(i.second), putch('\n');
    write((int)answer.size()), putch('\n');
    for (auto i : answer) write(i), putch(' ');
    putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
