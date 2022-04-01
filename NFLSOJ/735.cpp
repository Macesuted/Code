/**
 * @file 735.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-01
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

#define maxn 500005

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

int a[maxn], ans[maxn], bel[maxn], pt[maxn], fl[maxn], len[maxn], fr[maxn];
vector<int> S;
map<int, vector<int>> pos;
vector<int> chain[maxn];
vector<pii> ques[maxn];

void solve(int l, int r) {
    if (l == r) {
        while (!ques[l].empty()) ans[ques[l].back().second] = 1, ques[l].pop_back();
        return;
    }
    int mid = (l + r) >> 1;
    fl[mid + 1] = fr[mid] = 0;
    for (int i = mid; i >= l; i--) {
        len[i] = 1;
        if (pt[i] + 1 != (int)chain[bel[i]].size() && chain[bel[i]][pt[i] + 1] <= mid)
            len[i] = len[chain[bel[i]][pt[i] + 1]] + chain[bel[i]][pt[i] + 1] - i;
        fl[i] = max(fl[i + 1], len[i]);
    }
    for (int i = mid + 1; i <= r; i++) {
        len[i] = 1;
        if (pt[i] && chain[bel[i]][pt[i] - 1] > mid) len[i] = len[chain[bel[i]][pt[i] - 1]] + i - chain[bel[i]][pt[i] - 1];
        fr[i] = max(fr[i - 1], len[i]);
    }
    for (int i = mid; i >= l; i--) {
        if (pt[i] + 1 != (int)chain[bel[i]].size() && chain[bel[i]][pt[i] + 1] > mid)
            for (int j = pt[i] + 1; j < (int)chain[bel[i]].size() && chain[bel[i]][j] <= r; j++) S.push_back(chain[bel[i]][j]);
        while (!ques[i].empty() && ques[i].back().first > mid) {
            int qr = ques[i].back().first, id = ques[i].back().second;
            ques[i].pop_back();
            ans[id] = max(fl[i], fr[qr]);
            int p = upper_bound(S.begin(), S.end(), qr) - S.begin();
            if (p) {
                int q = S[p - 1];
                ans[id] = max(ans[id], q - *lower_bound(chain[bel[q]].begin(), chain[bel[q]].end(), i) + 1);
            }
        }
    }
    S.clear();
    return solve(l, mid), solve(mid + 1, r);
}

void solve(void) {
    int n = read(), q = read();
    for (int i = 1; i <= n; i++) pos[a[i] = read()].push_back(i);
    for (int i = 1; i <= q; i++) {
        int l = read(), r = read();
        ques[l].emplace_back(r, i);
    }
    for (int i = 1; i <= n; i++) sort(ques[i].begin(), ques[i].end());
    for (const auto& i : pos) {
        for (auto j : i.second) FT.add(j, 1);
        int last = i.second.front();
        for (auto j : i.second) {
            if (FT.sum(j) - FT.sum(last - 1) != j - last + 1) last = j;
            chain[bel[j] = last].push_back(j), pt[j] = chain[bel[j]].size() - 1;
        }
    }
    solve(1, n);
    for (int i = 1; i <= q; i++) write(ans[i]), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("spiral.in", "r", stdin), freopen("spiral.out", "w", stdout);
#endif
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
