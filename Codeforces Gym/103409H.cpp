/**
 * @file 103409H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 22;
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

#define maxn 100005
#define maxm 500005
#define maxlgn 30

typedef pair<int, int> pii;

class ACAutomaton {
   private:
    int son[maxm][2], fail[maxm], to[maxlgn][maxm][2], indeg[maxm], tail;
    long long f[maxlgn][maxm][2], cnt[maxm];

   public:
    ACAutomaton(void) { tail = 1; }
    int insert(const string& s) {
        int p = 0;
        for (auto& i : s) {
            int t = i - '0';
            if (!son[p][t]) son[p][t] = tail++;
            p = son[p][t];
        }
        return p;
    }
    void build(void) {
        static queue<int> que;
        while (!que.empty()) que.pop();
        for (int i = 0; i < 2; i++)
            if (son[0][i]) que.push(son[0][i]);
        to[0][0][0] = son[0][0], to[0][0][1] = son[0][1];
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (int i = 0; i < 2; i++)
                if (son[p][i])
                    fail[son[p][i]] = son[fail[p]][i], que.push(son[p][i]);
                else
                    son[p][i] = son[fail[p]][i];
            to[0][p][0] = son[p][0], to[0][p][1] = son[p][1];
        }
        for (int j = 1; j < maxlgn; j++)
            for (int i = 0; i < tail; i++)
                to[j][i][0] = to[j - 1][to[j - 1][i][0]][1], to[j][i][1] = to[j - 1][to[j - 1][i][1]][0];
        return;
    }
    void calc(vector<pii>& s) {
        int p = 0;
        for (auto& i : s) f[i.first][p][i.second]++, p = to[i.first][p][i.second];
        for (int i = maxlgn - 1; i; --i)
            for (int j = 0; j < tail; ++j)
                f[i - 1][j][0] += f[i][j][0], f[i - 1][j][1] += f[i][j][1], f[i - 1][to[i - 1][j][0]][1] += f[i][j][0],
                    f[i - 1][to[i - 1][j][1]][0] += f[i][j][1];
        for (int i = 0; i < tail; i++) cnt[son[i][0]] += f[0][i][0], cnt[son[i][1]] += f[0][i][1], indeg[fail[i]]++;
        static queue<int> que;
        while (!que.empty()) que.pop();
        for (int i = 0; i < tail; i++)
            if (!indeg[i]) que.push(i);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            cnt[fail[p]] += cnt[p];
            if (!--indeg[fail[p]]) que.push(fail[p]);
        }
        return;
    }
    long long query(int p) { return cnt[p]; }
} ACAM;

vector<pii> S;
int p[maxn];

void split(int l, int r, int lg, int rev, int ql, int qr) {
    if (ql <= l && r <= qr) return S.emplace_back(lg, rev), void();
    int mid = (l + r) >> 1;
    if (ql <= mid) split(l, mid, lg - 1, rev, ql, qr);
    if (qr > mid) split(mid + 1, r, lg - 1, !rev, ql, qr);
    return;
}

void solve(void) {
    int n = read<int>(), q = read<int>();
    for (int i = 1; i <= n; i++) {
        int l = read<int>(), r = read<int>(), p = 1, lgp = 0;
        while (p <= r) p <<= 1, lgp++;
        split(0, p - 1, lgp, 0, l, r);
    }
    for (int i = 1; i <= q; i++) p[i] = ACAM.insert(getstr());
    ACAM.build(), ACAM.calc(S);
    for (int i = 1; i <= q; i++) write(ACAM.query(p[i])), putch('\n');
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
