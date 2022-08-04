/**
 * @file 1060H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
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
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

bool mem1;

int a[12][12], c[12], binom[12][12], d, mod;

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

void opPlus(int x, int y, int to) {
    return putstr("+ "), write(x), putch(' '), write(y), putch(' '), write(to), putch('\n');
}
void opPow(int x, int to) { return putstr("^ "), write(x), putch(' '), write(to), putch('\n'); }

int empt = 50;
int multi(int x, int v) {
    vector<int> cache;
    if (v & 1) cache.push_back(x), v--;
    for (int i = 1, last = x; v; i++) {
        opPlus(last, last, empt);
        if (v >> i & 1) cache.push_back(empt), v -= 1 << i;
        last = empt++;
    }
    if (cache.size() == 1) return cache.front();
    int to = empt++;
    opPlus(cache[0], cache[1], to);
    for (int i = 2; i < (int)cache.size(); i++) opPlus(to, cache[i], to);
    return to;
}
int pow2(int p) {
    vector<int> cache;
    for (int i = 0; i <= d; i++, opPlus(p, 5000, p)) {
        int x = empt++;
        opPow(p, x);
        if (c[i]) cache.push_back(multi(x, c[i]));
    }
    if (cache.size() == 1) return cache.front();
    int to = empt++;
    opPlus(cache[0], cache[1], to);
    for (int i = 2; i < (int)cache.size(); i++) opPlus(to, cache[i], to);
    return to;
}

void solve(void) {
    d = read<int>(), mod = read<int>();
    for (int i = 0; i <= d; i++) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; j++) binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
    }
    for (int i = 0; i <= d; i++) {
        for (int j = 0; j <= d; j++) a[i][j] = Pow(j, d - i) * binom[d][i] % mod;
        a[i][d + 1] = (i == 2);
    }
    for (int i = 0; i <= d; i++) {
        int p = i;
        for (int j = i + 1; j <= d; j++)
            if (a[j][i] > a[p][i]) p = j;
        for (int j = 0; j <= d + 1; j++) swap(a[i][j], a[p][j]);
        long long inv = Pow(a[i][i], mod - 2);
        for (int j = 0; j <= d + 1; j++) a[i][j] = a[i][j] * inv % mod;
        for (int j = 0; j <= d; j++) {
            if (i == j) continue;
            long long x = a[j][i];
            for (int k = 0; k <= d + 1; k++) a[j][k] = (a[j][k] + mod - x * a[i][k] % mod) % mod;
        }
    }
    for (int i = 0; i <= d; i++) c[i] = a[i][d + 1];
    opPlus(1, 2, 3);
    int p1 = multi(pow2(1), mod - 1), p2 = multi(pow2(2), mod - 1), p3 = pow2(3);
    opPlus(p3, p1, p3), opPlus(p3, p2, p3);
    int p = multi(p3, Pow(2, mod - 2));
    putstr("f "), write(p), putch('\n');
    return;
}

bool mem2;

int main() {
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
