/**
 * @file J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-12
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Statement: https://1drv.ms/b/s!ApjY84dJhOY-gZ4qAwAmknmaJ99wJw?e=aEKzEQ
 *      Link: https://thupc2022.thusaac.com/#!/contest/2/problem/9
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

typedef pair<int, int> pii;

map<int, vector<pii>> p1, p2;

bool check(map<int, vector<pii>>& p, int x, pii a, int cnt) {
    for (auto& i : p)
        for (auto& j : i.second) {
            if (j == pii{-1, -1}) continue;
            if (j.first <= x && x <= j.second && a.first <= i.first && i.first <= a.second && !cnt--) return false;
        }
    return true;
}
bool checkT(void) {
    for (auto& i1 : p1)
        for (auto& j1 : i1.second) {
            int y1 = i1.first, l1 = j1.first, r1 = j1.second;
            if (j1 == pii{-1, -1} || !check(p2, y1, j1, 1)) continue;
            for (auto& i2 : p2)
                for (auto& j2 : i2.second) {
                    int x2 = i2.first, d2 = j2.first, u2 = j2.second;
                    if (j2 == pii{-1, -1} || !check(p1, x2, j2, 1)) continue;
                    if (d2 < y1 && y1 == u2 && l1 < x2 && x2 < r1) return j1 = j2 = {-1, -1}, true;
                }
        }
    return false;
}
bool checkH(void) {
    for (auto& i3 : p2)
        for (auto& j3 : i3.second) {
            int x3 = i3.first, d3 = j3.first, u3 = j3.second;
            if (j3 == pii{-1, -1} || !check(p1, x3, j3, 1)) continue;
            for (auto& i4 : p1)
                for (auto& j4 : i4.second) {
                    int y4 = i4.first, l4 = j4.first, r4 = j4.second;
                    if (j4 == pii{-1, -1} || !check(p2, y4, j4, 2)) continue;
                    for (auto& i5 : p2)
                        for (auto& j5 : i5.second) {
                            int x5 = i5.first, d5 = j5.first, u5 = j5.second;
                            if (j5 == pii{-1, -1} || !check(p1, x5, j5, 1)) continue;
                            if (d3 == d5 && d5 < y4 && y4 < u3 && u3 == u5 && x3 == l4 && l4 < r4 && r4 == x5)
                                return j3 = j4 = j5 = {-1, -1}, true;
                        }
                }
        }
    return false;
}
bool checkU(void) {
    for (auto& i6 : p2)
        for (auto& j6 : i6.second) {
            int x6 = i6.first, d6 = j6.first, u6 = j6.second;
            if (j6 == pii{-1, -1} || !check(p1, x6, j6, 1)) continue;
            for (auto& i7 : p1)
                for (auto& j7 : i7.second) {
                    int y7 = i7.first, l7 = j7.first, r7 = j7.second;
                    if (j7 == pii{-1, -1} || !check(p2, y7, j7, 2)) continue;
                    for (auto& i8 : p2)
                        for (auto& j8 : i8.second) {
                            int x8 = i8.first, d8 = j8.first, u8 = j8.second;
                            if (j8 == pii{-1, -1} || !check(p1, x8, j8, 1)) continue;
                            if (d6 == d8 && d8 == y7 && y7 < u6 && u6 == u8 && x6 == l7 && l7 < r7 && r7 == x8)
                                return j6 = j7 = j8 = {-1, -1}, true;
                        }
                }
        }
    return false;
}
bool checkP(void) {
    for (auto& i9 : p2)
        for (auto& j9 : i9.second) {
            int x9 = i9.first, d9 = j9.first, u9 = j9.second;
            if (j9 == pii{-1, -1} || !check(p1, x9, j9, 2)) continue;
            for (auto& i10 : p1)
                for (auto& j10 : i10.second) {
                    int y10 = i10.first, l10 = j10.first, r10 = j10.second;
                    if (j10 == pii{-1, -1} || !check(p2, y10, j10, 2)) continue;
                    for (auto& i11 : p1)
                        for (auto& j11 : i11.second) {
                            int y11 = i11.first, l11 = j11.first, r11 = j11.second;
                            if (j11 == pii{-1, -1} || !check(p2, y11, j11, 2)) continue;
                            for (auto& i12 : p2)
                                for (auto& j12 : i12.second) {
                                    int x12 = i12.first, d12 = j12.first, u12 = j12.second;
                                    if (j12 == pii{-1, -1} || !check(p1, x12, j12, 2)) continue;
                                    if (d9 < y11 && y11 == d12 && d12 < u9 && u9 == y10 && y10 == u12 && x9 == l10 &&
                                        l10 == l11 && l11 < r10 && r10 == r11 && r11 == x12)
                                        return j9 = j10 = j11 = j12 = {-1, -1}, true;
                                }
                        }
                }
        }
    return false;
}
bool checkC(void) {
    for (auto& i13 : p2)
        for (auto& j13 : i13.second) {
            int x13 = i13.first, d13 = j13.first, u13 = j13.second;
            if (j13 == pii{-1, -1} || !check(p1, x13, j13, 2)) continue;
            for (auto& i14 : p1)
                for (auto& j14 : i14.second) {
                    int y14 = i14.first, l14 = j14.first, r14 = j14.second;
                    if (j14 == pii{-1, -1} || !check(p2, y14, j14, 1)) continue;
                    for (auto& i15 : p1)
                        for (auto& j15 : i15.second) {
                            int y15 = i15.first, l15 = j15.first, r15 = j15.second;
                            if (j15 == pii{-1, -1} || !check(p2, y15, j15, 1)) continue;
                            if (d13 == y15 && y15 < u13 && u13 == y14 && x13 == l14 && l14 == l15 && l15 < r14 && r14 == r15)
                                return j13 = j14 = j15 = {-1, -1}, true;
                        }
                }
        }
    return false;
}

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int op = read<int>(), a = read<int>(), b = read<int>(), c = read<int>();
        if (op == 0)
            p1[c].emplace_back(a, b);
        else
            p2[c].emplace_back(a, b);
    }
    for (auto& i : p1) {
        auto& x = i.second;
        sort(x.begin(), x.end());
        vector<pii> nx;
        nx.push_back(x.front());
        for (auto j = x.begin(); j != x.end(); j++) {
            if (j->first > nx.back().second) nx.push_back(*j);
            nx.back().second = max(nx.back().second, j->second);
        }
        x = nx;
    }
    for (auto& i : p2) {
        auto& x = i.second;
        sort(x.begin(), x.end());
        vector<pii> nx;
        nx.push_back(x.front());
        for (auto j = x.begin(); j != x.end(); j++) {
            if (j->first > nx.back().second) nx.push_back(*j);
            nx.back().second = max(nx.back().second, j->second);
        }
        x = nx;
    }
    int siz = 0;
    for (auto& i : p1) siz += i.second.size();
    for (auto& i : p2) siz += i.second.size();
    if (siz != 15 || !checkT() || !checkH() || !checkU() || !checkP() || !checkC()) return putstr("No\n");
    return putstr("Yes\n");
}

bool mem2;

int main() {
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
