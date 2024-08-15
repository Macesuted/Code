/**
 * @file 81605G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache[100];
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 0), void(); }
void putstr(string &s) {
    for (auto c : s) putch(c);
    return;
}
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) return putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) cache[top++] = x % 10, x /= 10;
    while (top) putch(cache[--top] ^ 48);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

const int way[2][4] = {{+1, 0, -1, 0}, {0, +1, 0, -1}};

typedef pair<int, int> pii;

vector<pii> R[maxn], C[maxn];
int n, x[maxn], y[maxn], id[maxn], Rid[maxn], Cid[maxn], dist[maxn][4], nxt[maxn], xsum[maxn], ysum[maxn];
bool trn[maxn], visR[maxn], visC[maxn];

int jump(int p, int d, int t) {
    if (t & 1) {
        int v = Rid[p], tv = v + (t == 1 ? +d : -d);
        if (tv < 0 || tv >= (int)R[x[p]].size() || abs(R[x[p]][tv].first - y[p]) != d) return 0;
        return R[x[p]][tv].second;
    } else {
        int v = Cid[p], tv = v + (t == 0 ? +d : -d);
        if (tv < 0 || tv >= (int)C[y[p]].size() || abs(C[y[p]][tv].first - x[p]) != d) return 0;
        return C[y[p]][tv].second;
    }
}
int jumpWithoutCheck(int p, int d, int t) {
    return (t & 1) ? R[x[p]][Rid[p] + (t == 1 ? +d : -d)].second : C[y[p]][Cid[p] + (t == 0 ? +d : -d)].second;
}

int tot = 0;
int query(int &p, int &t, int lim, int delt) {
    int cnt = 1;
    trn[p] = false, delt = (delt + 4) & 3;

    int hist[4] = {-1, -1, -1, lim};
    auto updateHist = [&](int v) { hist[0] = hist[1], hist[1] = hist[2], hist[2] = hist[3], hist[3] = v; };

    if (!dist[p][t]) updateHist(way[0][t] ? y[p] : x[p]), trn[p] = true, t = (t + delt) & 3;
    while (dist[p][t]) {
        updateHist(way[0][t] ? y[p] : x[p]);
        int tx = x[p] + way[0][t] * dist[p][t], ty = y[p] + way[1][t] * dist[p][t];
        if (hist[0] != -1) {
            int v = hist[0];
            if (t == 0)
                tx = min(tx, v - 1);
            else if (t == 1)
                ty = min(ty, v - 1);
            else if (t == 2)
                tx = max(tx, v + 1);
            else
                ty = max(ty, v + 1);
        }
        int d = max(abs(tx - x[p]), abs(ty - y[p]));
        if (!d) break;
        cnt += d, p = nxt[p] = jumpWithoutCheck(p, d, t), trn[p] = true, t = (t + delt) & 3;
        tot++;
    }
    nxt[p] = 0, trn[p] = false, t = (t + 4 - delt) & 3;
    return cnt;
}

tuple<int, int, int, int> calc(void) {
    int xmin = 1e5, xmax = 0, ymin = 1e5, ymax = 0;
    for (int i = 1; i <= n; i++) R[x[i]].clear(), C[y[i]].clear(), visR[x[i]] = visC[y[i]] = false, xsum[x[i]] = ysum[y[i]] = 0;
    for (int i = 1; i <= n; i++) R[x[i]].emplace_back(y[i], i), C[y[i]].emplace_back(x[i], i), xsum[x[i]]++, ysum[y[i]]++;
    for (int i = 1; i <= n; i++) {
        if (!visR[x[i]]) visR[x[i]] = true, sort(R[x[i]].begin(), R[x[i]].end());
        if (!visC[y[i]]) visC[y[i]] = true, sort(C[y[i]].begin(), C[y[i]].end());
        Rid[i] = lower_bound(R[x[i]].begin(), R[x[i]].end(), pii{y[i], 0}) - R[x[i]].begin(),
        Cid[i] = lower_bound(C[y[i]].begin(), C[y[i]].end(), pii{x[i], 0}) - C[y[i]].begin();
        xmin = min(xmin, x[i]), xmax = max(xmax, x[i]), ymin = min(ymin, y[i]), ymax = max(ymax, y[i]);
    }

    for (int t = 0; t < 4; t++) {
        for (int i = 1; i <= n; i++) id[i] = i, dist[i][t] = 0;
        sort(id + 1, id + n + 1, [&](int a, int b) { return (x[b] - x[a]) * way[0][t] + (y[b] - y[a]) * way[1][t] < 0; });
        for (int i = 1; i <= n; i++) {
            int p = id[i], q = jump(p, 1, t);
            if (q) dist[p][t] = dist[q][t] + 1;
        }
    }

    vector<int> cache;
    for (int i = 1; i <= n; i++) cache.push_back(x[i]);
    sort(cache.begin(), cache.end()), cache.resize(unique(cache.begin(), cache.end()) - cache.begin());
    for (int i = 1; i < (int)cache.size(); i++) xsum[cache[i]] += xsum[cache[i - 1]];

    cache.clear();
    for (int i = 1; i <= n; i++) cache.push_back(y[i]);
    sort(cache.begin(), cache.end()), cache.resize(unique(cache.begin(), cache.end()) - cache.begin());
    for (int i = 1; i < (int)cache.size(); i++) ysum[cache[i]] += ysum[cache[i - 1]];

    for (int p = 1; p <= n; p++) {
        int q = jump(p, 1, 1);
        if (!q) continue;
        int tp, tq, pt, qt;
        if (x[p] == xmin &&
            (query(tp = p, pt = 3, y[q], +1) == ysum[y[p]] && query(tq = q, qt = 1, y[p], -1) == n - ysum[y[p]])) {
            vector<int> pos;
            pos.push_back(p);
            for (int i = q; i; i = nxt[i]) pos.push_back(i);
            for (int i = 1; i < (int)pos.size(); i++) nxt[pos[i]] = pos[i - 1];
            return {tq, tp, qt ^ 2, pt};
        }
        if (x[p] == xmax &&
            (query(tp = p, pt = 3, y[q], -1) == ysum[y[p]] && query(tq = q, qt = 1, y[p], +1) == n - ysum[y[p]])) {
            vector<int> pos;
            pos.push_back(q);
            for (int i = p; i; i = nxt[i]) pos.push_back(i);
            for (int i = 1; i < (int)pos.size(); i++) nxt[pos[i]] = pos[i - 1];
            return {tp, tq, pt ^ 2, qt};
        }
    }

    for (int p = 1; p <= n; p++) {
        int q = jump(p, 1, 0);
        if (!q) continue;
        int tp, tq, pt, qt;
        if (y[p] == ymax &&
            (query(tp = p, pt = 2, x[q], +1) == xsum[x[p]] && query(tq = q, qt = 0, x[p], -1) == n - xsum[x[p]])) {
            vector<int> pos;
            pos.push_back(p);
            for (int i = q; i; i = nxt[i]) pos.push_back(i);
            for (int i = 1; i < (int)pos.size(); i++) nxt[pos[i]] = pos[i - 1];
            return {tq, tp, qt ^ 2, pt};
        }
        if (y[p] == ymin &&
            (query(tp = p, pt = 2, x[q], -1) == xsum[x[p]] && query(tq = q, qt = 0, x[p], +1) == n - xsum[x[p]])) {
            vector<int> pos;
            pos.push_back(q);
            for (int i = p; i; i = nxt[i]) pos.push_back(i);
            for (int i = 1; i < (int)pos.size(); i++) nxt[pos[i]] = pos[i - 1];
            return {tp, tq, pt ^ 2, qt};
        }
    }

    return {0, 0, 0, 0};
}

string getPath(int p) {
    string s;
    s.reserve(2 * n);
    for (int q = nxt[p]; q; p = q, q = nxt[q]) {
        int d = max(abs(x[p] - x[q]), abs(y[p] - y[q]));
        for (int i = 0; i < d; i++) s.push_back('0');
        if (trn[q]) s.push_back('1');
    }
    return s;
}

void solve(void) {
    n = read();
    for (int i = 1; i <= n; i++) x[i] = read(), y[i] = read();
    auto [p, q, pt, qt] = calc();
    if (!p) return write(-1), putch('\n');
    string path = getPath(p);
    write(path.size()), putch('\n'), write(x[p]), putch(' '), write(y[p]), putch(' '), write(pt), putch('\n');
    putstr(path), putch('\n');
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read();
    while (_--) solve();

    cerr << tot << endl;

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}