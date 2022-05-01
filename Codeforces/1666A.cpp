/**
 * @file 1666A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-13
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

#define maxn 20005
#define sqrtn 150
#define base 31
#define mod 998244353

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

char s[maxn];
int len[maxn], rlPos[maxn], degPos[maxn], UPos[maxn];
int64_t powb[maxn], invpb[maxn], powpre[maxn], sumU[maxn], sumD[maxn], sumL[maxn], sumR[maxn];
bool chkL[sqrtn][maxn];

void solve(void) {
    string s = getstr(" ");
    int n = s.size() - 1, ans = 0;
    for (int i = 1; i <= n; i++) sumU[i] = (sumU[i - 1] + (s[i] == 'U') * powb[i - 1]) % mod;
    for (int i = 1; i <= n; i++) sumD[i] = (sumD[i - 1] + (s[i] == 'D') * powb[i - 1]) % mod;
    for (int i = 1; i <= n; i++) sumL[i] = (sumL[i - 1] + (s[i] == 'L') * powb[i - 1]) % mod;
    for (int i = 1; i <= n; i++) sumR[i] = (sumR[i - 1] + (s[i] == 'R') * powb[i - 1]) % mod;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        bool t = false;
        while (r <= n && s[r] == "RL"[t]) r++, t = !t;
        if (t) r--;
        r = max(r - 1, l);
        int len = (r - l + 1) / 2;
        ans += len * (len + 1) / 2;
        for (int i = l; i + 1 <= r; i += 2) rlPos[i] = r;
    }
    for (int i = n, pos = n + 1; i; i--) {
        if (s[i] == 'U') pos = i;
        int c = (i < n && (s[i + 1] == 'L'));
        degPos[i] = (c ? pos : i);
        c += (i > 1 && s[i - 1] == 'R');
        if (c == 0) pos = i;
        if (c == 2) pos = i - 1;
    }
    for (int i = n, pos = n + 1; i; i--) {
        if (s[i] == 'U') pos = i;
        UPos[i] = pos;
    }
    auto getU = [&](int l, int r) {
        return (l < 1 || r > n || l > r) ? 0 : (sumU[r] + mod - sumU[l - 1]) * invpb[l - 1] % mod;
    };
    auto getD = [&](int l, int r) {
        return (l < 1 || r > n || l > r) ? 0 : (sumD[r] + mod - sumD[l - 1]) * invpb[l - 1] % mod;
    };
    auto getL = [&](int l, int r) {
        return (l < 1 || r > n || l > r) ? 0 : (sumL[r] + mod - sumL[l - 1]) * invpb[l - 1] % mod;
    };
    auto getR = [&](int l, int r) {
        return (l < 1 || r > n || l > r) ? 0 : (sumR[r] + mod - sumR[l - 1]) * invpb[l - 1] % mod;
    };
    auto check = [&](int p, int len, bool U, bool D) {
        int l = p, r = p + len - 1;
        return s[l] != 'L' && s[r] != 'R' && (U || getU(l, r) == 0) && (D || getD(l, r) == 0) &&
               ((U ? getD(l - len, r - len) : 0) + getR(l, r - 1) * base + getL(l + 1, r) + (D ? getU(l + len, r + len) : 0)) %
                       mod ==
                   powpre[len - 1];
    };
    for (int i = 1; i <= n && UPos[i] <= n; i++) {
        int len = UPos[i] - degPos[i];
        if (!len || !check(i, len, false, true)) continue;
        int p = (rlPos[i] - i + 1) / len;
        if (p > 0) ans -= p;
        if (len < sqrtn)
            chkL[len][i] = true;
        else {
            ans += check(i, len, false, false);
            for (int j = i + len; j + len - 1 <= n; j += len) {
                if (check(j, len, true, false)) ans++;
                if (!check(j, len, true, true)) break;
            }
        }
    }
    for (int len = 1; len < sqrtn; len++)
        for (int i = 1; i <= len; i++)
            for (int j = i, cnt = 0; j + len - 1 <= n; j += len) {
                ans += (chkL[len][j] && check(j, len, false, false));
                if (check(j, len, true, false)) ans += cnt;
                if (!check(j, len, true, true)) cnt = 0;
                cnt += (chkL[len][j] && check(j, len, false, true));
            }
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    powb[0] = powpre[0] = invpb[0] = 1, invpb[1] = Inv(powb[1] = base);
    for (int i = 1; i < maxn; i++)
        powpre[i] = (powpre[i - 1] + (powb[i] = powb[i - 1] * powb[1] % mod)) % mod, invpb[i] = invpb[i - 1] * invpb[1] % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}