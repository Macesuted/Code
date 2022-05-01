/**
 * @file 12708.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache1[100], cache2[100];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
char iseoln(char c) { return c == '\n' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il && (fill(), 1), *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 1), void(); }
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
    while (x) cache1[top++] = x % 10, x /= 10;
    while (top) putch(cache1[--top] ^ 48);
    return;
}
template <typename T>
void writeDouble(T x, int dep = 10) {
    if (x < 0) putch('-'), x = -x;
    int64_t fx = x;
    x -= fx;
    for (int i = 0; i < dep; i++) cache2[i] = (x *= 10), x -= int(x);
    if (int(x * 10) > 4) {
        cache2[dep - 1]++;
        for (int i = dep - 1; i; i--)
            if (cache2[i] == 10) cache2[i] = 0, cache2[i - 1]++;
        if (cache2[0] == 10) cache2[0] = 0, fx++;
    }
    write(fx), putch('.');
    for (int i = 0; i < dep; i++) putch(cache2[i] ^ 48);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
    }
    return s;
}
string getline(const string& suf = "") {
    string s = suf;
    while (iseoln(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !iseoln(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
    }
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::getch;
using IO::getline;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;
using IO::writeDouble;

bool mem1;

#define maxn 10000005
#define sqrt3n 220

typedef pair<int, int> pii;

class UnionSet {
   private:
    int fa[maxn];
    uint64_t dist[maxn];

    int getfa(int p) {
        if (fa[p] == p) return p;
        int ffp = getfa(fa[p]);
        return dist[p] ^= dist[fa[p]], fa[p] = ffp;
    }

   public:
    UnionSet(void) {
        for (int i = 0; i < maxn; i++) fa[i] = i, dist[i] = 0;
    }
    bool check(int x, int y) { return getfa(x) == getfa(y); }
    uint64_t getDist(int x) { return getfa(x), dist[x]; }
    bool merge(int x, int y, uint64_t w) {
        int fx = getfa(x), fy = getfa(y);
        if (fx == fy) return false;
        return dist[fx] = getDist(x) ^ getDist(y) ^ w, fa[fx] = fy, true;
    }
} US;
class Basis {
   private:
    uint64_t a[60];

   public:
    Basis(void) { memset(a, 0, sizeof(a)); }
    bool insert(uint64_t x) {
        for (int i = 46; ~i; i--)
            if (x >> i & 1) {
                if (a[i])
                    x ^= a[i];
                else
                    return a[i] = x;
            }
        return false;
    }
    bool query(uint64_t x) {
        for (int i = 46; ~i; i--)
            if (x >> i & 1) {
                if (a[i])
                    x ^= a[i];
                else
                    return false;
            }
        return true;
    }
} basis;

vector<int> prime;
int id[maxn], pre[maxn];

int sqr(int x) { return x * x; }

pair<pii, uint64_t> split(int n) {
    array<int, 2> a = {1, 1};
    uint64_t b = 0;
    int cnt = 0;
    while (n > 1) {
        bool t = false;
        int lst = pre[n];
        while (n > 1 && pre[n] == lst) t = !t, n /= pre[n];
        if (t) lst <= sqrt3n ? b |= (uint64_t)1 << id[lst] : a[cnt++] = lst;
    }
    return {{a[0], a[1]}, b};
}

void solve(void) {
    int n = read(), siz = 0;
    if (sqr(sqrt(n)) == n) return write(n), putch('\n');
    pii na, a;
    uint64_t nb, b;
    tie(na, nb) = split(n);
    for (int ans = n + 1;; ans++) {
        tie(a, b) = split(ans);
        if (!US.merge(a.first, a.second, b) && siz < 47) siz += basis.insert(US.getDist(a.first) ^ US.getDist(a.second) ^ b);
        if (US.check(na.first, na.second) && basis.query(US.getDist(na.first) ^ US.getDist(na.second) ^ nb))
            return write(ans), putch('\n');
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("squ.in", "r", stdin), freopen("squ.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxn; i++) {
        if (!pre[i]) id[i] = prime.size(), pre[i] = i, prime.push_back(i);
        for (auto j = prime.begin(); j != prime.end() && i * *j < maxn; j++) {
            pre[i * *j] = *j;
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
