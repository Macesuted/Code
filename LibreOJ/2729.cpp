/**
 * @file 2729.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-07
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

#define maxn 200005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class FenwickTree {
   private:
    int tree[maxn * 2];

   public:
    void upd(int p, int v) {
        for (int i = p; i < maxn * 2; i += i & -i) tree[i] = max(tree[i], v);
        return;
    }
    int maxVal(int p) {
        int maxVal = 0;
        for (int i = p; i; i -= i & -i) maxVal = max(maxVal, tree[i]);
        return maxVal;
    }
} FT;

pii a[maxn];
tiii ques[maxn];
int ans[maxn], t[maxn * 2];

void solve(void) {
    int n = read(), q = read(), tcnt = 0;
    for (int i = 1; i <= n; i++) a[i].first = read(), t[++tcnt] = a[i].second = read();
    sort(a + 1, a + n + 1, [](pii a, pii b) { return a.first != b.first ? a.first > b.first : a.second < b.second; });
    for (int i = 1; i <= q; i++) get<0>(ques[i]) = read(), t[++tcnt] = get<1>(ques[i]) = read(), get<2>(ques[i]) = i;
    sort(ques + 1, ques + q + 1, [](tiii a, tiii b) { return get<0>(a) > get<0>(b); });
    sort(t + 1, t + tcnt + 1), tcnt = unique(t + 1, t + tcnt + 1) - t;
    for (int i = 1; i <= n; i++) a[i].second = lower_bound(t + 1, t + tcnt, a[i].second) - t;
    for (int i = 1; i <= q; i++) get<1>(ques[i]) = lower_bound(t + 1, t + tcnt, get<1>(ques[i])) - t;
    a[n + 1].first = 0;
    for (int i = 1, j = 1; i <= n + 1; i++) {
        while (j <= q && get<0>(ques[j]) > a[i].first) ans[get<2>(ques[j])] = FT.maxVal(get<1>(ques[j])), j++;
        if (i == n + 1) break;
        FT.upd(a[i].second, FT.maxVal(a[i].second) + 1);
    }
    for (int i = 1; i <= q; i++) write(ans[i]), putch('\n');
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}