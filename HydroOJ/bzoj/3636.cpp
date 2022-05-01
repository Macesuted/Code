/**
 * @file 3636.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-21
 *
 * @copyright Copyright (c) 2022
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

#define maxn 100005
#define maxl 55

typedef pair<int, int> pii;

int a[maxn], sum[maxn], n, LEN;
long long ans[maxn], lef[maxl][maxn], rig[maxl][maxn];
vector<pii> ques[maxn];

void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    for (int x = mid; x >= max(l, mid - LEN + 1); x--) {
        int i = mid - x;
        for (int j = x + 1; j <= mid + 1; j++) lef[i][j] = 0;
        for (int j = x; j >= l; j--) {
            lef[i][j] = lef[i][j + 1];
            if (j + LEN - 1 <= x) lef[i][j] = max(lef[i][j], sum[j + LEN - 1] - sum[j - 1] + lef[i][j + LEN]);
        }
    }
    for (int x = mid + 1; x <= min(r, mid + LEN); x++) {
        int i = x - mid - 1;
        for (int j = mid; j < x; j++) rig[i][j] = 0;
        for (int j = x; j <= r; j++) {
            rig[i][j] = rig[i][j - 1];
            if (j - LEN + 1 >= x) rig[i][j] = max(rig[i][j], sum[j] - sum[j - LEN] + rig[i][j - LEN]);
        }
    }
    for (int i = l; i <= mid; i++)
        while (!ques[i].empty() && ques[i].back().first > mid) {
            int L = i, R = ques[i].back().first, t = ques[i].back().second;
            ques[i].pop_back();
            ans[t] = max(ans[t], lef[0][L] + rig[0][R]);
            for (int x = mid; x >= max(l, mid - LEN + 2); x--) {
                int y = x + LEN - 1, ix = mid - x + 1, iy = y - mid;
                if (x < L || y > R || y > r) continue;
                ans[t] = max(ans[t], lef[ix][L] + sum[y] - sum[x - 1] + rig[iy][R]);
            }
        }
    return solve(l, mid), solve(mid + 1, r);
}
void solve(void) {
    n = read<int>(), LEN = read<int>();
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (a[i] = read<int>());
    int q = read<int>();
    for (int i = 1; i <= q; i++) {
        int l = read<int>(), r = read<int>();
        if (r - l + 1 < LEN) continue;
        ques[l].emplace_back(r, i);
    }
    for (int i = 1; i <= n; i++) sort(ques[i].begin(), ques[i].end());
    solve(1, n);
    for (int i = 1; i <= q; i++) write(ans[i]), putch('\n');
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
