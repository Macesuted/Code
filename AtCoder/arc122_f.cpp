/**
 * @file arc122_f.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

#include <atcoder/mincostflow>
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

#define maxn 100005

typedef pair<int, int> pii;

const int inf = numeric_limits<int>::max();

atcoder::mcf_graph<long long, long long> net(5 * maxn);

pii a[maxn], b[maxn];
int X[maxn], Y[maxn], px[maxn], py[maxn];

void solve(void) {
    int n = read<int>(), m = read<int>(), k = read<int>();
    for (int i = 1; i <= n; i++) a[i].first = read<int>(), a[i].second = read<int>();
    for (int i = 1; i <= m; i++) b[i].first = read<int>(), b[i].second = read<int>();
    sort(a + 1, a + n + 1);
    stack<pii> sta;
    for (int i = 1; i <= n; i++) {
        while (!sta.empty() && sta.top().second < a[i].second) sta.pop();
        sta.push(a[i]);
    }
    for (int i = n = sta.size(); i; i--) a[i] = sta.top(), sta.pop();
    for (int i = 1; i <= n; i++) cerr << a[i].first << ' ' << a[i].second << endl;
    for (int i = 1; i <= n; i++) tie(X[i], Y[i]) = a[i];
    int S = n + 2, T = n + 3, tcnt = n + 3;
    net.add_edge(S, 1, inf, 0);
    for (int i = 1; i <= n; i++) net.add_edge(i + 1, i, inf, 0);
    net.add_edge(n + 1, T, inf, 0);
    for (int i = 1; i <= n; i++) net.add_edge(i, px[i] = ++tcnt, inf, 0);
    for (int i = 1; i <= n; i++) net.add_edge(py[i] = ++tcnt, i + 1, inf, 0);
    for (int i = 2; i <= n; i++) net.add_edge(px[i - 1], px[i], inf, Y[i - 1] - Y[i]);
    for (int i = 2; i <= n; i++) net.add_edge(py[i - 1], py[i], inf, X[i] - X[i - 1]);
    for (int i = 1; i <= m; i++) {
        int l = lower_bound(Y + 1, Y + n + 1, b[i].second, greater<int>()) - Y,
            r = upper_bound(X + 1, X + n + 1, b[i].first) - X - 1;
        tcnt += 2;
        net.add_edge(l, tcnt - 1, 1, 0), net.add_edge(tcnt - 1, tcnt, 1, 0), net.add_edge(tcnt, r + 1, 1, 0);
        if (l > 1) net.add_edge(px[l - 1], tcnt - 1, 1, Y[l - 1] - b[i].second);
        if (r < n) net.add_edge(tcnt, py[r + 1], 1, X[r + 1] - b[i].first);
    }
    write(net.flow(S, T, k).second), putch('\n');
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
