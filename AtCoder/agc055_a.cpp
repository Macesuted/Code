/**
 * @file agc055_a.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-04
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

#define maxn 200005

typedef pair<int, int> pii;

vector<int> a[3][3];
int ans[3 * maxn];

void solve(void) {
    int n = read<int>();
    for (int i = 0; i < 3; i++)
        for (int j = 1; j <= n; j++) {
            char c = getch();
            while (c != 'A' && c != 'B' && c != 'C') c = getch();
            a[i][c - 'A'].push_back(i * n + j);
        }
#define set(i, j, c) ans[a[i][j].back()] = c, a[i][j].pop_back()
    while (a[0][0].size() && a[1][1].size() && a[2][2].size()) set(0, 0, 1), set(1, 1, 1), set(2, 2, 1);
    while (a[0][0].size() && a[1][2].size() && a[2][1].size()) set(0, 0, 2), set(1, 2, 2), set(2, 1, 2);
    while (a[0][1].size() && a[1][0].size() && a[2][2].size()) set(0, 1, 3), set(1, 0, 3), set(2, 2, 3);
    while (a[0][1].size() && a[1][2].size() && a[2][0].size()) set(0, 1, 4), set(1, 2, 4), set(2, 0, 4);
    while (a[0][2].size() && a[1][0].size() && a[2][1].size()) set(0, 2, 5), set(1, 0, 5), set(2, 1, 5);
    while (a[0][2].size() && a[1][1].size() && a[2][0].size()) set(0, 2, 6), set(1, 1, 6), set(2, 0, 6);
#undef set
    for (int i = 1; i <= 3 * n; i++) write(ans[i]);
    putch('\n');
    return;
}

bool mem2;

int main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}