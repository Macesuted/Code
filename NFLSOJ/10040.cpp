/**
 * @file 10040.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-29
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

#define maxn 20
#define mod 998244353

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

class Matrix {
   private:
    vector<vector<int>> M;
    int n, m;

   public:
    void resize(int _n, int _m) { return M.resize(n = _n, vector<int>(m = _m, 0)); }
    vector<int>& operator[](size_t x) { return M[x]; }
    int get(int x, int y) const { return M[x][y]; }
    Matrix operator*(const Matrix& o) const {
        Matrix ans;
        assert(m == o.n), ans.resize(n, o.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < o.m; k++) ans[i][k] = (ans[i][k] + 1LL * get(i, j) * o.get(j, k)) % mod;
        return ans;
    }
    Matrix operator^(int x) const {
        Matrix ans, a = *this;
        assert(n == m), ans.resize(n, n);
        for (int i = 0; i < n; i++) ans[i][i] = 1;
        while (x) {
            if (x & 1) ans = ans * a;
            a = a * a, x >>= 1;
        }
        return ans;
    }
};

map<vector<int>, int> arrs;
int n;

bool vis[maxn];

vector<int> arr;
int cnt = 0;
void dfs(int p) {
    if (p == n) return arrs[arr] = cnt++, void();
    int last = (arr.empty() ? 1 : arr.back());
    for (int i = last; p + i <= n; i++) arr.push_back(i), dfs(p + i), arr.pop_back();
    return;
}
int calc(vector<int> p) {
    vector<int> vec;
    for (int i = 0; i < n; i++)
        if (!vis[i]) {
            vis[i] = true;
            int x = i, cnt = 1;
            while (!vis[p[x]]) vis[x = p[x]] = true, cnt++;
            vec.push_back(cnt);
        }
    for (int i = 0; i < n; i++) vis[i] = false;
    sort(vec.begin(), vec.end());
    return arrs[vec];
}

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }

void solve(void) {
    n = read<int>();
    dfs(0);
    int m = arrs.size(), T = read<int>();
    int64_t invCn3 = Pow(n * (n - 1) * (n - 2), mod - 2);
    vector<int> A, B, C;
    A.resize(n), B.resize(n), C.resize(n);
    for (int i = 0; i < n; i++) A[i] = read<int>() - 1;
    for (int i = 0; i < n; i++) B[i] = read<int>() - 1;
    for (int i = 0; i < n; i++) C[B[i]] = A[i];
    int S = calc(C);
    Matrix X, base;
    X.resize(1, m), base.resize(m, m);
    X[0][S] = 1;
    for (auto i : arrs) {
        if (i.second == 0) {
            base[0][0] = 1;
            continue;
        }
        int x = i.second;
        vector<int> vec;
        vec.reserve(n);
        int cnt = 0;
        for (auto j : i.first) {
            for (int i = 1; i < j; i++) vec.push_back(cnt + i);
            vec.push_back(cnt), cnt += j;
        }
        for (int a = 0; a < n; a++)
            for (int b = 0; b < n; b++)
                for (int c = 0; c < n; c++) {
                    if (a == b || a == c || b == c) continue;
                    tie(vec[a], vec[b], vec[c]) = make_tuple(vec[c], vec[a], vec[b]);
                    base[x][calc(vec)] = Mod(base[x][calc(vec)] + invCn3);
                    tie(vec[a], vec[b], vec[c]) = make_tuple(vec[b], vec[c], vec[a]);
                }
    }
    write((X * (base ^ T))[0][0]), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("goodbye.in", "r", stdin), freopen("goodbye.out", "w", stdout);
#endif
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
