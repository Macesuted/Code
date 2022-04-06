/**
 * @file 12985.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-06
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

#define maxm 15

const int INF = numeric_limits<int>::max();

int f[14][4782969];
char a[205][205], b[205][205];
int pow3[15];

int Min(int& x, int y) { return x = (x < y ? x : y); }

void solve(void) {
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            a[i][j] = ' ';
            while (a[i][j] < '0' || a[i][j] > '2') a[i][j] = getch();
        }
    if (n < m) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) b[i][j] = a[i][j];
        swap(n, m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) a[i][j] = b[j][i];
    }
    pow3[0] = 1;
    for (int i = 1; i <= m + 1; i++) pow3[i] = pow3[i - 1] * 3;
    bool t = false;
    for (int S = 1; S < pow3[m + 1]; S++) f[t][S] = INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            t = !t;
            for (int S = 0; S < pow3[m + 1]; S++) f[t][S] = INF;
            for (int S = 0; S < pow3[m + 1]; S++) {
                if (f[!t][S] == INF) continue;
                int lef = S / pow3[j - 1] % 3, up = S / pow3[j] % 3, T = S - lef * pow3[j - 1] - up * pow3[j];
                if (a[i][j] != '0' && lef != 1 && up != 1) Min(f[t][T], f[!t][S]);
                if (a[i][j] != '1') {
                    Min(f[t][T + 2 * pow3[j - 1] + 2 * pow3[j]], f[!t][S] + 1);
                    if (lef == 2 || up == 2)
                        Min(f[t][T + up * pow3[j - 1] + lef * pow3[j]], f[!t][S]);
                    else
                        Min(f[t][T + pow3[j - 1] + lef * pow3[j]], f[!t][S]),
                            Min(f[t][T + up * pow3[j - 1] + pow3[j]], f[!t][S]);
                }
            }
        }
        t = !t;
        for (int S = 0; S < pow3[m + 1]; S++) f[t][S] = INF;
        for (int S = 0; S < pow3[m + 1]; S++)
            if (S / pow3[m] % 3 != 1) Min(f[t][S * 3 % pow3[m + 1]], f[!t][S]);
    }
    int ans = INF;
    for (int S = 0; S < pow3[m + 1]; S++) {
        bool check = true;
        for (int i = 1; i <= m && check; i++)
            if (S / pow3[i] % 3 == 1) check = false;
        if (check) Min(ans, f[t][S]);
    }
    return write(ans), putch('\n');
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("daredevil.in", "r", stdin), freopen("daredevil.out", "w", stdout);
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