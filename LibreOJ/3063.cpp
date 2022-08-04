/**
 * @file 3063.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-08
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

#define maxn 400005

typedef pair<int64_t, int64_t> pll;
typedef tuple<int64_t, int64_t, int64_t> tlll;
typedef tuple<int, int, int> tiii;

int64_t TIM;

struct Func {
    int64_t a, b;

    int64_t operator()(int64_t x = TIM) const { return a * x + b; }
    bool operator<(const Func& o) const { return (*this)() < o(); }
};

pll a[maxn];
tiii ques[maxn];
set<pair<Func, int64_t>> S;
multiset<pair<int64_t, pair<Func, int64_t>>> near;
int lef[maxn], rig[maxn];

int64_t cross(Func x, Func y) {
    if (x.a <= y.a) return INT64_MAX;
    int64_t t = (y.b - x.b) / (x.a - y.a);
    while (x(t) <= y(t)) t++;
    return t < TIM ? INT64_MAX : t;
}
void insert(Func a, int64_t x) {
    auto p = S.emplace(a, x).first, pl = p, pr = p;
    if (pl != S.begin()) {
        pl--;
        if (++pr != S.end())
            near.erase(near.find({cross(pl->first, pr->first), *pr})), near.emplace(cross(a, pr->first), *pr);
        near.emplace(cross(pl->first, a), *p);
    } else if (++pr != S.end())
        near.emplace(cross(a, pr->first), *pr);
    return;
}
void erase(Func a, int64_t x) {
    auto p = S.find({a, x}), pl = p, pr = p;
    assert(p != S.end());
    if (pl != S.begin()) {
        pl--;
        if (++pr != S.end())
            near.emplace(cross(pl->first, pr->first), *pr), near.erase(near.find({cross(a, pr->first), *pr}));
        near.erase(near.find({cross(pl->first, a), *p}));
    } else if (++pr != S.end())
        near.erase(near.find({cross(a, pr->first), *pr}));
    return S.erase(p), void();
}

void solve(int ans[], int n, int q) {
    S.clear(), near.clear();
    for (int i = 1, j = 0; i <= q; i++) {
        while (!near.empty() && near.begin()->first <= get<0>(ques[i]))
            TIM = near.begin()->first, erase(near.begin()->second.first, near.begin()->second.second);
        TIM = get<0>(ques[i]);
        while (j < n && a[j].first <= TIM) {
            j++;
            Func x;
            x.a = (a[j].second - a[j - 1].second) / (a[j].first - a[j - 1].first), x.b = a[j].second - a[j].first * x.a;
            while (!S.empty() && (S.begin()->first)() < x()) erase(S.begin()->first, S.begin()->second);
            insert(x, -a[j].first);
        }
        auto p = S.lower_bound({Func{0, get<1>(ques[i])}, 0});
        ans[get<2>(ques[i])] = (p == S.end() ? 0 : -p->second);
    }
    return;
}
void solve(void) {
    int n = read(), q = read();
    a[0] = {0, 0};
    for (int i = 1; i <= n; i++) {
        int d = read(), k = read();
        a[i] = {a[i - 1].first + d, a[i - 1].second + 1LL * d * k};
    }
    for (int i = 1; i <= q; i++) get<0>(ques[i]) = read(), get<1>(ques[i]) = read(), get<2>(ques[i]) = i;
    sort(ques + 1, ques + q + 1);
    solve(lef, n, q);
    int L = a[n].first;
    for (int i = 0; i <= n; i++) a[i].first = L - a[i].first;
    for (int i = 1; i <= q; i++) get<0>(ques[i]) = L - get<0>(ques[i]);
    reverse(a, a + n + 1), reverse(ques + 1, ques + q + 1);
    solve(rig, n, q);
    for (int i = 1; i <= q; i++) write(lef[i]), putch(' '), write(L - rig[i]), putch('\n');
    return;
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