/**
 * @file 8253.cpp
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

#define maxm 5
#define maxn 200005

typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int> tiiii;

class FenwickTree {
   private:
    int tree[maxn * 2];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn * 2; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

int a[maxm][maxn];
long long ans[maxn];
tiii nodes[maxn];
tiiii ques[maxn];

void CDQ(int tl, int tr, int nl, int nr, int ql, int qr) {
    if (tl == tr || nl > nr || ql > qr) return;
    int tmid = (tl + tr) >> 1, nmid = nl - 1, qmid = ql - 1;
    while (nmid < nr && get<0>(nodes[nmid + 1]) <= tmid) nmid++;
    while (qmid < qr && get<0>(ques[qmid + 1]) <= tmid) qmid++;
    CDQ(tl, tmid, nl, nmid, ql, qmid), CDQ(tmid + 1, tr, nmid + 1, nr, qmid + 1, qr);
    if (nl > nmid || qmid + 1 > qr) return;
    sort(nodes + nl, nodes + nmid + 1, [](tiii a, tiii b) { return get<1>(a) < get<1>(b); });
    sort(ques + qmid + 1, ques + qr + 1, [](tiiii a, tiiii b) { return get<1>(a) < get<1>(b); });
    int j = nl;
    for (int i = qmid + 1; i <= qr; i++) {
        while (j <= nmid && get<1>(nodes[j]) < get<1>(ques[i])) FT.add(get<2>(nodes[j++]), +1);
        ans[get<3>(ques[i])] += FT.sum(get<2>(ques[i]) - 1);
    }
    for (int i = nl; i < j; i++) FT.add(get<2>(nodes[i]), -1);
    return;
}

void solve(void) {
    int m = read<int>(), n = read<int>();
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) a[i][j] = read<int>();
    for (int i = m + 1; i <= 4; i++)
        for (int j = 1; j <= n; j++) a[i][j] = a[i - 1][j];
    long long answer = 0;
    for (int t = 1; t <= 4; t++) {
        for (int i = 1; i <= n; i++) {
            vector<int> cache;
            for (int j = 1; j <= 4; j++)
                if (j != t) cache.push_back(a[j][i] - a[t][i]);
            nodes[i] = {cache[0] + maxn, cache[1] + maxn, cache[2] + maxn};
            cache.clear();
            for (int j = 1; j <= 4; j++)
                if (j != t) cache.push_back(a[t][i] - a[j][i] + (j > t));
            ques[i] = {cache[0] + maxn, cache[1] + maxn, cache[2] + maxn, i};
        }
        for (int i = 1; i <= n; i++) ans[i] = 0;
        sort(nodes + 1, nodes + n + 1, [](tiii a, tiii b) { return get<0>(a) < get<0>(b); });
        sort(ques + 1, ques + n + 1, [](tiiii a, tiiii b) { return get<0>(a) < get<0>(b); });
        CDQ(1, maxn * 2, 1, n, 1, n);
        for (int i = 1; i <= n; i++) answer += ans[i] * a[t][i];

        for (int i = 1; i <= n; i++) {
            vector<int> cache;
            for (int j = 1; j <= 4; j++)
                if (j != t) cache.push_back(a[t][i] - a[j][i]);
            nodes[i] = {cache[0] + maxn, cache[1] + maxn, cache[2] + maxn};
            cache.clear();
            for (int j = 1; j <= 4; j++)
                if (j != t) cache.push_back(a[j][i] - a[t][i] + (j > t));
            ques[i] = {cache[0] + maxn, cache[1] + maxn, cache[2] + maxn, i};
        }
        for (int i = 1; i <= n; i++) ans[i] = 0;
        sort(nodes + 1, nodes + n + 1, [](tiii a, tiii b) { return get<0>(a) < get<0>(b); });
        sort(ques + 1, ques + n + 1, [](tiiii a, tiiii b) { return get<0>(a) < get<0>(b); });
        CDQ(1, maxn * 2, 1, n, 1, n);
        for (int i = 1; i <= n; i++) answer += ans[i] * a[t][i];
    }
    return write(answer * 2), putch('\n');
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
