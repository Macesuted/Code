/**
 * @file 8251.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = (x % 10) ^ 48, x /= 10;
    while (top) putch(stack[--top]);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
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
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

bool mem1;

#define maxn 500005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        p++;
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        p++;
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

pii a[maxn];
int p[maxn], ans[maxn];
tiii ques[maxn * 2];

void solve(void) {
    int n = read<int>(), q = read<int>();
    for (int i = 1; i <= n; i++) a[i].first = read<int>();
    for (int i = 1; i <= n; i++) a[i].second = read<int>();
    static stack<int> S;
    while (!S.empty()) S.pop();
    for (int i = 1; i <= n; i++) {
        while (!S.empty() && (a[S.top()].first == a[i].first || a[S.top()].second <= a[i].second)) S.pop();
        p[i] = (S.empty() ? 0 : S.top()), S.push(i);
    }
    for (int i = 1; i <= q; i++) {
        int l = read<int>(), r = read<int>();
        get<0>(ques[i]) = l - 1, get<1>(ques[i]) = r, get<2>(ques[i]) = i;
        get<0>(ques[i + q]) = l - 1, get<1>(ques[i + q]) = l - 1, get<2>(ques[i + q]) = -i;
    }
    sort(ques + 1, ques + 2 * q + 1, [](tiii a, tiii b) { return get<1>(a) < get<1>(b); });
    for (int i = 1, j = 1; i <= 2 * q; i++) {
        while (j <= get<1>(ques[i])) FT.add(p[j++], +1);
        ans[abs(get<2>(ques[i]))] += abs(get<2>(ques[i])) / get<2>(ques[i]) * FT.sum(get<0>(ques[i]));
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
