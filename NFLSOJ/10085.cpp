/**
 * @file 10085.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-09
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

#define mod 1000000007

int A[10], B[10], t[10];

class Matrix {
   private:
    vector<vector<int>> a;
    int n, m;

   public:
    vector<int>& operator[](size_t x) { return a[x]; }
    Matrix operator*(const Matrix& o) const {
        assert(m == o.n);
        Matrix ans;
        ans.resize(n, o.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < o.m; k++) ans[i][k] = (ans[i][k] + (int64_t)(*this).get(i, j) * o.get(j, k)) % mod;
        return ans;
    }
    Matrix operator^(int64_t x) const {
        assert(n == m);
        Matrix ans, a = *this;
        ans.resize(n, n);
        for (int i = 0; i < n; i++) ans[i][i] = 1;
        while (x) {
            if (x & 1) ans = ans * a;
            a = a * a, x >>= 1;
        }
        return ans;
    }
    void resize(int _n, int _m) { return a = vector<vector<int>>(n = _n, vector<int>(m = _m, 0)), void(); }
    int get(int x, int y) const { return a[x][y]; }
};

void solve(void) {
    int n = read(), C = read(), K = read();
    for (int i = 1; i <= n; i++) A[i] = t[i] = read(), B[i] = read();
    sort(t + 1, t + n + 1);
    int tn = unique(t + 1, t + n + 1) - t;
    for (int i = 1; i <= n; i++) A[i] = lower_bound(t + 1, t + tn, A[i]) - t;
    C = C - tn + 1;
    auto _ = [&](int x, int y) { return x * (tn + 1) + y; };
    Matrix M;
    M.resize(1, _(K, tn) + 1), M[0][_(0, 0)] = 1;
    for (int i = 1; i <= n; i++) {
        Matrix base;
        base.resize(_(K, tn) + 1, _(K, tn) + 1);
        for (int j = 0; j <= K; j++) {
            base[_(j, 0)][_(j, 0)] = 1;
            if (j == K) continue;
            for (int k = 1; k < tn; k++)
                if (k != A[i]) base[_(j, 0)][_(j + 1, k)] = 1;
            base[_(j, 0)][_(j + 1, tn)] = C;
        }
        for (int j = 0; j <= K; j++)
            for (int k = 1; k < tn; k++) {
                base[_(j, k)][_(j, k)] = 1;
                if (k != A[i]) base[_(j, k)][_(j, 0)] = 1;
                if (j == K) continue;
                for (int k_ = 1; k_ < tn; k_++)
                    if (k_ != k && k_ != A[i]) base[_(j, k)][_(j + 1, k_)] = 1;
                base[_(j, k)][_(j + 1, tn)] = C;
            }
        for (int j = 0; j <= K; j++) {
            base[_(j, tn)][_(j, tn)] = base[_(j, tn)][_(j, 0)] = 1;
            if (j == K) continue;
            for (int k = 1; k < tn; k++)
                if (k != A[i]) base[_(j, tn)][_(j + 1, k)] = 1;
            base[_(j, tn)][_(j + 1, tn)] = C - 1;
        }
        M = M * (base ^ B[i]);
    }
    int64_t ans = 0;
    for (int j = 0; j <= K; j++)
        for (int k = 0; k <= tn; k++) ans = (ans + M[0][_(j, k)]) % mod;
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("count.in", "r", stdin), freopen("count.out", "w", stdout);
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
