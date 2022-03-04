/**
 * @file piece.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-04
 * 
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 512M
 * 
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
    const int SIZE = (1 << 21) + 1;
    char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
    void flush(void) {
        fwrite (obuf, 1, oS - obuf, stdout);
        oS = obuf;
        return;
    }
    char getch(void) {
        return (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++);
    }
    void putch(char x) {
        *oS++ = x;
        if (oS == oT) flush();
        return;
    }
    template <class I>
    I read (void) {
        I x;
        for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
            if (c == '-') f = -1;
        for (x = 0; c <= '9' && c >= '0'; c = getch()) x = (x << 3) + (x << 1) + (c ^ 48);
        return x * f;
    }
    template <class I>
    void write(I x) {
        if (!x) return putch('0');
        if (x < 0) putch('-'), x = -x;
        while (x) qu[++qr] = x % 10 + '0', x /= 10;
        while (qr) putch(qu[qr --]);
        return;
    }
    struct Flusher_ {
        ~Flusher_() { flush(); }
    } io_flusher_;
}
using io::getch;
using io::putch;
using io::read;
using io::write;

bool mem1;

#define maxn 10000005

typedef pair<int, int> pii;

int a[maxn], b[maxn], c[maxn];
list<pii> li;

void solve(void) {
    int n = read<int>(), k = read<int>(), tk = min(n, k);
    long long sum = 0;
    for (int i = 1; i <= n; i++) sum += (a[i] = read<int>());
    if (tk == 0)
        for (int i = 1; i <= n; i++) b[i] = a[i];
    for (int i = n; i > n - tk; i--) {
        if (!a[i]) continue;
        int l = n - i + 1;
        if (!li.empty() && li.back().second >= l - 1)
            li.back().second = min(li.back().second + a[i], tk);
        else
            li.emplace_back(l, min(l + a[i] - 1, tk));
        if (li.back().second == tk) break;
    }
    for (int i = 1; i <= n; i++) {
        if (!li.empty() && li.back().second + i - 1 == tk) b[i]++;
        if (!li.empty() && li.back().second + i > tk) li.back().second = tk - i;
        if (!li.empty() && li.back().first > li.back().second) li.pop_back();
        int t = a[i];
        if (t) {
            if (!li.empty() && li.front().first + i <= t + 1) {
                int c = min(t, li.front().first + i - 1);
                t -= c, li.front().first -= c;
            } else
                li.emplace_front(1 - i, min(t, tk) - i), t -= min(t, tk);
            auto p = li.begin();
            while (t && p->second + i < tk) {
                auto np = p;
                np++;
                int c = min(t, tk - i - p->second);
                if (np != li.end()) c = min(c, np->first - p->second - 1);
                if (c < min(t, tk - i - p->second)) {
                    int r = np->second;
                    li.erase(np), p->second = r, t -= c;
                } else
                    p->second += c, t -= c;
            }
        }
        b[i] += t;
    }
    if (k > n && sum < n) {
        int delt = k % n;
        for (int i = 1; i <= n; i++) c[i] = b[i];
        for (int i = 1; i + delt <= n; i++) b[i + delt] = c[i];
        for (int i = n - delt + 1; i <= n; i++) b[i + delt - n] = c[i];
    }
    unsigned long long ans = 0, M = 12345678901, mul = M;
    for (int i = 1; i <= n; i++) ans += mul * (unsigned long long)(b[i] + 1), mul *= M;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("piece.in", "r", stdin), freopen("piece.out", "w", stdout);
#endif
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
}