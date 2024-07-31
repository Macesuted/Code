/**
 * @file 81600A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

namespace IO {
const int SIZE = 1 << 24;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache[100];
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 0), void(); }
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
    while (x) cache[top++] = x % 10, x /= 10;
    while (top) putch(cache[--top] ^ 48);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::getch;
using IO::putch;
using IO::read;
using IO::write;

#define maxn 50005
#define maxm 1005
#define maxlgn 20

string a[maxn];
int lga[maxn], cnt[maxn], pre[maxn][maxm], rig1[maxn][maxm], pos[maxn], id[maxm][maxn], rnk[maxm][maxn], pow2[maxlgn],
    lg2[maxn];
vector<int> grp[maxm], ST[maxm][maxlgn], cache[maxm];
int n, m, q;

inline int getMin(int g, int l, int r) {
    int t = lg2[r - l + 1], x = ST[g][t][l], y = ST[g][t][r - pow2[t] + 1];
    return rnk[1][x] < rnk[1][y] ? x : y;
}

void solve(void) {
    n = read(), m = read(), q = read();
    for (int i = 1; i <= n; i++) {
        a[i].reserve(m + 1), a[i].push_back(' ');
        char c;
        for (int j = 1; j <= m; j++) {
            c = getch();
            while (c != '0' && c != '1') c = getch();
            a[i].push_back(c);
        }
        rig1[i][m + 1] = -1;
        for (int j = m; j; j--) rig1[i][j] = (a[i][j] == '1' ? j : rig1[i][j + 1]), cnt[i] += (a[i][j] == '1');
        lga[i] = (cnt[i] == 0 ? -1 : m - rig1[i][1] + (cnt[i] > 1));
        if (lga[i] != -1) grp[lga[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) pre[i][j] = pre[i - 1][j];
        if (lga[i] != -1) pre[i][lga[i]]++;
    }

    for (int i = 1; i <= n; i++) rnk[m + 1][i] = id[m + 1][i] = i;
    for (int i = m; i; i--) {
        int cnt[2] = {0, 0};
        for (int j = 1; j <= n; j++) cnt[a[j][i] - '0']++;
        cnt[1] += cnt[0];
        for (int j = n; j; j--) id[i][cnt[a[id[i + 1][j]][i] - '0']--] = id[i + 1][j];
        for (int j = 1; j <= n; j++) rnk[i][id[i][j]] = j;
    }

    for (int i = 0; i <= m; i++) {
        int s = grp[i].size();
        if (!s) continue;
        for (int j = 0; j < maxlgn; j++) ST[i][j].resize(s + 1);
        for (int j = 1; j <= s; j++) ST[i][0][j] = grp[i][j - 1];
        for (int j = 1; j < maxlgn; j++)
            for (int k = 1; k + pow2[j] - 1 <= s; k++)
                ST[i][j][k] = (rnk[1][ST[i][j - 1][k]] < rnk[1][ST[i][j - 1][k + pow2[j - 1]]] ? ST[i][j - 1][k]
                                                                                               : ST[i][j - 1][k + pow2[j -
                                                                                               1]]);
    }

    for (int i = 0; i <= m; i++) cache[i].reserve(m);

    while (q--) {
        int l = read(), r = read();

        int ans = 0, cnt = 0, minVal = 0, rest = 0;
        for (int i = 0; i <= m; i++) {
            int ql = pre[l - 1][i] + 1, qr = pre[r][i];
            if (ql > qr) continue;
            minVal = i;
            break;
        }
        for (int i = m; ~i; i--) {
            cache[i].clear();
            int ql = pre[l - 1][i] + 1, qr = pre[r][i];
            if (ql > qr) continue;
            cnt += qr - ql + 1, ans = max(ans, i + cnt - (i == minVal)), rest += qr - ql + 1;
        }

        bool chk = true;
        cnt = 0;
        for (int i = m; ~i; i--) {
            int ql = pre[l - 1][i] + 1, qr = pre[r][i], minp = -1;
            if (ql > qr && cache[i].empty()) continue;
            if (ql <= qr) {
                cnt += qr - ql + 1, rest -= qr - ql + 1;
                int p = getMin(i, ql, qr);
                if (rig1[p][m - i + 1] != -1) minp = p;
            }
            if (!cache[i].empty()) {
                cnt += cache[i].size(), rest -= cache[i].size();
                for (auto p : cache[i])
                    if (rig1[p][m - i + 1] != -1 && (minp == -1 || (rnk[m - i + 1][p] < rnk[m - i + 1][minp]))) minp = p;
            }
            if (i + cnt - (rest == 0) < ans) continue;
            if (i + cnt - (rest == 0) > ans || !rest || minp == -1) {
                chk = false;
                break;
            }
            int b = rig1[minp][m - i + 2];
            rest++, cache[m - b + (rig1[minp][b + 1] != -1)].push_back(minp);
        }

        write(ans - chk), putch('\n');
    }
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    pow2[0] = 1;
    for (int i = 1; i < maxlgn; i++) pow2[i] = pow2[i - 1] << 1;
    for (int i = 2; i < maxn; i++) lg2[i] = lg2[i >> 1] + 1;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}