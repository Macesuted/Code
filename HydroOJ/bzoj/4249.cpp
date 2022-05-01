/**
 * @file 4249.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-25
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      My Tutorial: https://macesuted.moe/article/bzoj4249
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

#define maxn 200005

typedef pair<int, int> pii;

set<pii> S, Sd;
map<int, vector<pii>> ques;
int a[maxn];
long long ans[maxn], answer = 0;

template <typename T>
T dec(T a) {
    return --a;
}
template <typename T>
T inc(T a) {
    return ++a;
}
void insert(set<pii>::iterator p) {
    return answer += abs(p->second - inc(p)->second), Sd.emplace(abs(p->second - inc(p)->second), p->first), void();
}
void erase(set<pii>::iterator p) {
    return answer -= abs(p->second - inc(p)->second), Sd.erase({abs(p->second - inc(p)->second), p->first}), void();
}

void check(pii x, int tim) {
    auto p = S.find(x);
    if (p == S.begin() && p == dec(S.end())) return;
    if (p == S.begin()) {
        if (p->second == inc(p)->second) return S.erase(p), void();
        if (inc(p)->second < p->second) S.erase(p), p = S.emplace(x.first, x.second + tim).first;
        return insert(p);
    }
    if (p == dec(S.end())) {
        if (p->second == dec(p)->second) return S.erase(p), void();
        if (dec(p)->second < p->second) S.erase(p), p = S.emplace(x.first, x.second + tim).first;
        return insert(dec(p));
    }
    return insert(--S.erase(p));
}

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        int l = read<int>(), r = read<int>();
        ques[r - l].emplace_back(l, i);
    }
    for (int i = 1; i <= m; i++) S.emplace(i, a[i] = read<int>());
    for (auto i = ++S.begin(); inc(i) != S.end(); i++)
        if ((dec(i)->second < i->second) == (i->second < inc(i)->second) || dec(i)->second == i->second ||
            i->second == inc(i)->second)
            i = --S.erase(i);
    for (auto i = S.begin(); inc(i) != S.end(); i++)
        Sd.emplace(abs(i->second - inc(i)->second), i->first), answer += abs(i->second - inc(i)->second);
    int last = 0;
    while (!Sd.empty()) {
        int tim = Sd.begin()->first, ip = Sd.begin()->second;
        Sd.erase(Sd.begin());
        if (tim != last)
            for (auto i = ques.begin(); i != ques.end() && i->first < tim; i = ques.erase(i)) {
                int t = S.begin()->second;
                if (S.begin()->second > inc(S.begin())->second) t -= i->first;
                for (auto j : i->second) ans[j.second] = answer + abs(t - j.first) - 1LL * ((int)S.size() - 1) * i->first;
            }
        last = tim;
        auto p = S.lower_bound({ip, 0}), q = inc(p);
        erase(p);
        if (p->second > q->second) {
            if (p != S.begin()) erase(dec(p));
            q = S.erase(p);
            if (q != dec(S.end())) erase(q);
            check(*q, tim);
        } else {
            if (q != dec(S.end())) erase(q);
            p = --S.erase(q);
            if (p != S.begin()) erase(dec(p));
            check(*p, tim);
        }
    }
    for (auto i : ques)
        for (auto j : i.second)
            if (S.begin()->second - (i.first - last) <= j.first && j.first <= S.begin()->second)
                ans[j.second] = 0;
            else
                ans[j.second] = min(abs(S.begin()->second - j.first), abs(S.begin()->second - (i.first - last) - j.first));
    for (int i = 1; i <= n; i++) write(ans[i]), putch('\n');
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