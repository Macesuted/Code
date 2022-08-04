/**
 * @file 2478.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-19
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

#define maxn 300005

typedef pair<int, int> pii;
typedef pair<long long, int> pli;

vector<vector<pii>> graph;

pli f[maxn][3];
int k;

inline pli operator+(const pli& a, const pli& b) { return pli{a.first + b.first, a.second + b.second}; }

void dfs(int p, long long limit, int pre = -1) {
    tie(f[p][0], f[p][1], f[p][2]) = make_tuple(pli{0, 0}, pli{0, 0}, pli{limit, 1});
    for (auto i : graph[p]) {
        int x = i.first;
        if (x == pre) continue;
        dfs(x, limit, p);
        tie(f[p][0], f[p][1], f[p][2]) =
            make_tuple(f[p][0] + f[x][0], max({f[p][1] + f[x][0], f[p][0] + f[x][1] + pli{i.second, 0}}),
                       max({f[p][2] + f[x][0], f[p][1] + f[x][1] + pli{i.second + limit, 1}}));
    }
    f[p][0] = max({f[p][0], f[p][1] + pli{limit, 1}, f[p][2]});
    return;
}

inline bool check(long long limit) { return dfs(1, limit), f[1][0].second <= k; }

void solve(void) {
    int n = read<int>();
    k = read<int>() + 1;
    graph.resize(n + 1);
    long long sum = 0;
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>(), d = read<int>();
        graph[x].emplace_back(y, d), graph[y].emplace_back(x, d);
        sum += abs(d);
    }
    // for (int i = -sum; i <= +sum; i++) check(i), cerr << i << ' ' << f[1][0].second << endl;
    long long l = -sum, r = +sum, ans = 0;
    while (l <= r) {
        long long mid = (l + r) >> 1;
        check(mid) ? (l = mid + 1, ans = mid) : r = mid - 1;
    }
    // cerr << "!" << l << endl;
    check(l), write(f[1][0].first - k * l), putch('\n');
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << t2 - t1 << "ms" << endl;
    return 0;
}