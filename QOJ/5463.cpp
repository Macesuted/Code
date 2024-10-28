/**
 * @file 5463.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache[100];
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 0), void(); }
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
using IO::read;
using IO::write;

bool mem1;

#define maxn 250005
#define maxlgv 28
#define B 500

typedef pair<int, int> pii;

pii a[maxn];

int64_t sqr(int64_t v) { return v * v; }
int64_t dist(int x, int y) { return sqr(a[x].first - a[y].first) + sqr(a[x].second - a[y].second); }

class Block {
   private:
    int n;
    int64_t a[maxn], b[maxn];

   public:
    Block(void) {
        for (int i = 0; i < maxn; i++) a[i] = b[i] = INT64_MAX;
    }

    void resize(int _n) { return n = _n, void(); }
    void add(int p, int64_t v) { return a[p] = min(a[p], v), b[p / B] = min(b[p / B], v), void(); }
    int64_t query(int p) {
        int64_t ans = INT64_MAX;
        int q = p;
        while (q / B == p / B) ans = min(ans, a[q++]);
        while (q / B <= n / B) ans = min(ans, b[q / B]), q += B;
        return ans;
    }
} BLK;

class Dime {
   private:
    int64_t lim;
    unordered_map<int64_t, vector<int>> list;
    queue<int> all;

    static int64_t _(int64_t x, int64_t y) { return x * int64_t(1e9) + y; }

   public:
    void setLim(int64_t v) { return lim = v, void(); }
    void insert(int p) {
        int x = a[p].first / lim / 2, y = a[p].second / lim / 2, del = 0;
        for (int tx = x - 1; tx <= x + 1; tx++)
            for (int ty = y - 1; ty <= y + 1; ty++)
                if (list.find(_(tx, ty)) != list.end())
                    for (auto q : list[_(tx, ty)]) {
                        int64_t d = dist(p, q);
                        BLK.add(q, d);
                        if (d < lim * lim) del = max(del, q);
                    }

        while (!all.empty() && all.front() <= del) {
            int q = all.front();
            all.pop();
            int tx = a[q].first / lim / 2, ty = a[q].second / lim / 2;
            vector<int> tmp;
            for (auto i : list[_(tx, ty)])
                if (i > del) tmp.push_back(i);
            if (tmp.empty())
                list.erase(_(tx, ty));
            else
                list[_(tx, ty)] = tmp;
        }

        list[_(x, y)].push_back(p), all.push(p);
        return;
    }
};

Dime dims[maxlgv];
vector<pii> ques[maxn];
int64_t ans[maxn];

void solve(void) {
    int n = read(), q = read();
    for (int i = 1; i <= n; i++) a[i].first = read(), a[i].second = read();
    for (int i = 1, l, r; i <= q; i++) l = read(), r = read(), ques[r].emplace_back(l, i);

    for (int i = 0; i < maxlgv; i++) dims[i].setLim((int64_t)1 << i);
    BLK.resize(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < maxlgv; j++) dims[j].insert(i);
        for (auto [l, id] : ques[i]) ans[id] = BLK.query(l);
    }

    for (int i = 1; i <= q; i++) write(ans[i]), putch('\n');
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}