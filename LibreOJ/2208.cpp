/**
 * @file 2208.cpp
 * @author Macesuted Moe (i@macesuted.moe)
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 512M
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

#define maxn 100005

string a[maxn];
vector<int> fail;

int cti(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    return c - 'a' + 10;
}

bool solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[i] = getstr();
    int p = 0;
    for (int i = 1; i <= n; i++) {
        bool check = true;
        for (auto j : a[i])
            if (j == '*') check = false;
        if (check) p = i;
    }
    string s = "";
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < (int)a[i].size() && a[i][j] != '*'; j++) {
            if ((int)s.size() <= j) s.push_back(a[i][j]);
            if (s[j] != a[i][j]) return false;
        }
    s = "";
    for (int i = 1; i <= n; i++)
        for (int j = (int)a[i].size() - 1; ~j && a[i][j] != '*'; j--) {
            if ((int)s.size() <= (int)a[i].size() - j - 1) s.push_back(a[i][j]);
            if (s[(int)a[i].size() - j - 1] != a[i][j]) return false;
        }
    if (p == 0) return true;
    for (int t = 1; t <= n; t++) {
        vector<string> sub;
        for (int j = 0, l = 0; j <= (int)a[t].size(); j++)
            if (j == (int)a[t].size() || a[t][j] == '*') {
                if (l < j) sub.push_back(a[t].substr(l, j - l));
                l = j + 1;
            }
        int x = 0;
        for (auto& s : sub) {
            fail.resize(s.size()), fail[0] = -1;
            for (int i = 1; i < (int)s.size(); i++) {
                fail[i] = fail[i - 1] + 1;
                while (fail[i] && s[fail[i]] != s[i]) fail[i] = fail[fail[i] - 1] + 1;
                if (s[fail[i]] != s[i]) fail[i] = -1;
            }
            for (int i = 0; i < (int)s.size(); i++, x++) {
                if (x == (int)a[p].size()) return false;
                while (i && a[p][x] != s[i]) i = fail[i - 1] + 1;
                if (a[p][x] != s[i]) i = -1;
            }
        }
    }
    return true;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) putch("NY"[solve()]), putch('\n');

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
