/**
 * @file 3350.cpp
 * @author Macesuted Moe (i@macesuted.moe)
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 512MB
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

#define maxn 100005
#define mod 1000000007

class Matrix {
   private:
    vector<vector<long long>> a;
    int n, m;

   public:
    void resize(int _n, int _m) {
        n = _n, m = _m;
        a.resize(n, vector<long long>(m, 0));
        return;
    }
    long long get(int n, int m) const { return a[n][m]; }
    vector<long long>& operator[](int n) { return a[n]; }
    Matrix operator*(const Matrix& oth) const {
        Matrix ans;
        ans.resize(this->n, oth.m);
        assert(this->m == oth.n);
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->m; j++)
                for (int k = 0; k < oth.m; k++) ans[i][k] = (ans[i][k] + this->get(i, j) * oth.get(j, k)) % mod;
        return ans;
    }
    Matrix operator^(long long x) const {
        Matrix ans, a = *this;
        assert(a.n == a.m);
        ans.resize(n, n);
        for (int i = 0; i < n; i++) ans[i][i] = 1;
        while (x) {
            if (x & 1) ans = ans * a;
            a = a * a, x >>= 1;
        }
        return ans;
    }
};

bool sg[maxn];
long long sum[maxn][2], cnt[maxn], tot[maxn], p1 = 0, p2 = 0;

vector<vector<int>> graph;

void calc(int p) {
    return sg[p] = (tot[p] > 0), cnt[p] = (sg[p] ? (tot[p] == 1 ? sum[p][0] : 0) : 1 + sum[p][1]) % mod, void();
}
void dfs1(int p, int pre = -1) {
    sum[p][0] = sum[p][1] = tot[p] = 0;
    for (auto i : graph[p])
        if (i != pre) dfs1(i, p), tot[p] += !sg[i], sum[p][sg[i]] = (sum[p][sg[i]] + cnt[i]) % mod;
    return calc(p);
}
void dfs2(int p, int pre = -1) {
    sg[p] ? p1 = (p1 + cnt[p]) % mod : (p1 = (p1 + mod - cnt[p]) % mod, p2++);
    for (auto i : graph[p])
        if (i != pre) {
            tot[p] -= !sg[i], sum[p][sg[i]] = (sum[p][sg[i]] + mod - cnt[i]) % mod, calc(p);
            tot[i] += !sg[p], sum[i][sg[p]] = (sum[i][sg[p]] + cnt[p]) % mod, calc(i);
            dfs2(i, p);
            tot[i] -= !sg[p], sum[i][sg[p]] = (sum[i][sg[p]] + mod - cnt[p]) % mod, calc(i);
            tot[p] += !sg[i], sum[p][sg[i]] = (sum[p][sg[i]] + cnt[i]) % mod, calc(p);
        }
    return;
}

void solve(void) {
    long long n = read<int>(), D = read<long long>();
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    dfs1(1);
    bool SG = sg[1];
    long long CNT = cnt[1];
    dfs2(1);
    Matrix a, base;
    a.resize(1, 2), a[0][0] = p2, a[0][1] = n * n % mod;
    base.resize(2, 2), base[0][0] = p1, base[1][0] = p2, base[0][1] = 0, base[1][1] = n * n % mod;
    Matrix ret = a * (base ^ (D - 1));
    write((SG ? (ret[0][1] + mod - CNT * ret[0][0] % mod) : CNT * ret[0][0]) % mod), putch('\n');
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
