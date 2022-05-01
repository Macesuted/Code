/**
 * @file 2728.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-30
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
    __int128 fx = x;
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

#define maxn 4005

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

bool a[maxn][maxn];
int n, m, L, lef[maxn][maxn], rig[maxn][maxn], up[maxn][maxn], dow[maxn][maxn], l[maxn], r[maxn];

int calc(int a1, int b1, int a2, int b2) { return a[a2][b2] - a[a1 - 1][b2] - a[a2][b1 - 1] + a[a1 - 1][b1 - 1]; }

int64_t solve(int x, int y) {
    static vector<pii> nodes;
    nodes.clear();
    int64_t ans = 0;
    for (int i = x, j = y; i <= n && j <= m; i++, j++) {
        l[i] = i - min(j - lef[i][j], i - up[i][j]), r[i] = i + min(rig[i][j] - j, dow[i][j] - i);
        nodes.emplace_back(l[i], i);
    }
    sort(nodes.begin(), nodes.end());
    auto p = nodes.begin();
    for (int i = x; i <= n; i++) {
        while (p != nodes.end() && p->first <= i) FT.add((p++)->second, +1);
        if (i + L - 1 <= r[i]) ans += FT.sum(r[i]) - FT.sum(i + L - 2);
    }
    for (auto i = nodes.begin(); i != p; i++) FT.add(i->second, -1);
    return ans;
}

void solve(void) {
    n = read(), m = read(), L = read();
    for (int i = 1, P = read(); i <= P; i++) {
        int x = read(), y = read();
        a[x][y] = true;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1, l = 1; j <= m; j++) {
            if (a[i][j]) l = j + 1;
            lef[i][j] = l;
        }
    for (int i = 1; i <= n; i++)
        for (int j = m, l = m; j; j--) {
            if (a[i][j]) l = j - 1;
            rig[i][j] = l;
        }
    for (int j = 1; j <= m; j++)
        for (int i = 1, l = 1; i <= n; i++) {
            if (a[i][j]) l = i + 1;
            up[i][j] = l;
        }
    for (int j = 1; j <= m; j++)
        for (int i = n, l = n; i; i--) {
            if (a[i][j]) l = i - 1;
            dow[i][j] = l;
        }
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans += solve(i, 1);
    for (int i = 2; i <= m; i++) ans += solve(1, i);
    return write(ans), putch('\n');
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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