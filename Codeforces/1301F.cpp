/**
 * @file 1301F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-23
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

#define maxn 1005
#define maxk 45

typedef pair<int, int> pii;

const int way[2][4] = {{0, 1, 0, -1}, {1, 0, -1, 0}};

int a[maxn][maxn], dist[maxk][maxn][maxn], distc[maxk][maxk];

int distp(pii x, pii y) { return abs(x.first - y.first) + abs(x.second - y.second); }

void solve(void) {
    int n = read<int>(), m = read<int>(), K = read<int>();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a[i][j] = read<int>();
    memset(distc, 0x3f, sizeof(distc));
    for (int c = 1; c <= K; c++) {
        distc[c][c] = 0;
        static queue<pii> que;
        while (!que.empty()) que.pop();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (a[i][j] == c)
                    que.emplace(i, j), dist[c][i][j] = 0;
                else
                    dist[c][i][j] = 0x3f3f3f3f;
        while (!que.empty()) {
            pii p = que.front();
            que.pop();
            for (int i = 0; i < 4; i++) {
                int tx = p.first + way[0][i], ty = p.second + way[1][i];
                if (!(1 <= tx && tx <= n && 1 <= ty && ty <= m && dist[c][tx][ty] == 0x3f3f3f3f)) continue;
                dist[c][tx][ty] = dist[c][p.first][p.second] + 1, que.emplace(tx, ty);
            }
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) distc[c][a[i][j]] = min(distc[c][a[i][j]], dist[c][i][j]);
    }
    for (int k = 1; k <= K; k++)
        for (int i = 1; i <= K; i++)
            for (int j = 1; j <= K; j++) distc[i][j] = min(distc[i][j], distc[i][k] + 1 + distc[k][j]);
    int q = read<int>();
    while (q--) {
        int r1 = read<int>(), c1 = read<int>(), r2 = read<int>(), c2 = read<int>(),
            ans = distp(pii{r1, c1}, pii{r2, c2});
        for (int k = 1; k <= K; k++) ans = min(ans, dist[k][r1][c1] + 1 + dist[k][r2][c2]);
        for (int k1 = 1; k1 <= K; k1++)
            for (int k2 = 1; k2 <= K; k2++) ans = min(ans, dist[k1][r1][c1] + 1 + distc[k1][k2] + 1 + dist[k2][r2][c2]);
        write(ans), putch('\n');
    }
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
