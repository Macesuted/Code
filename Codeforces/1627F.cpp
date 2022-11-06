/**
 * @file 1627F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-01
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

#define maxk 505

typedef pair<int, int> pii;

int dow[maxk][maxk], rig[maxk][maxk];

int dist[maxk * maxk];
bool vis[maxk * maxk];
vector<vector<pii>> graph;

void solve(void) {
    int n = read<int>(), k = read<int>();
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++) dow[i][j] = rig[i][j] = 0;
    for (int i = 1; i <= n; i++) {
        int r1 = read<int>(), c1 = read<int>(), r2 = read<int>(), c2 = read<int>();
        if (r1 > r2 || c1 > c2) swap(r1, r2), swap(c1, c2);
        if (r1 == r2)
            rig[r1][c1]++;
        else
            dow[r1][c1]++;
        tie(r1, c1) = MP(k - r1 + 1, k - c1 + 1), tie(r2, c2) = MP(k - r2 + 1, k - c2 + 1);
        if (r1 > r2 || c1 > c2) swap(r1, r2), swap(c1, c2);
        if (r1 == r2)
            rig[r1][c1]++;
        else
            dow[r1][c1]++;
    }
    graph.clear(), graph.resize((k + 1) * (k + 1) + 1);
#define _(x, y) (((x)-1) * (k + 1) + (y))
    for (int i = 1; i <= k; i++) graph[_(1, i)].emplace_back(_(1, i + 1), 0), graph[_(1, i + 1)].emplace_back(_(1, i), 0);
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
            graph[_(i + 1, j)].emplace_back(_(i + 1, j + 1), dow[i][j]),
                graph[_(i + 1, j + 1)].emplace_back(_(i + 1, j), dow[i][j]);
    for (int i = 1; i <= k; i++) {
        graph[_(i, 1)].emplace_back(_(i + 1, 1), 0), graph[_(i + 1, 1)].emplace_back(_(i, 1), 0);
        for (int j = 1; j <= k; j++)
            graph[_(i, j + 1)].emplace_back(_(i + 1, j + 1), rig[i][j]),
                graph[_(i + 1, j + 1)].emplace_back(_(i, j + 1), rig[i][j]);
    }
    static priority_queue<pii, vector<pii>, greater<pii>> que;
    while (!que.empty()) que.pop();
    for (int i = 1; i <= (k + 1) * (k + 1); i++) dist[i] = 0x3f3f3f3f, vis[i] = false;
    que.emplace(dist[1] = 0, 1);
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto i : graph[p])
            if (dist[i.first] > dist[p] + i.second) que.emplace(dist[i.first] = dist[p] + i.second, i.first);
    }
    cout << n - dist[_(k / 2 + 1, k / 2 + 1)] << endl;
#undef _
    return;
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
