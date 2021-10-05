/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) { return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++); }
inline void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
}
string getstr(void) {
    string s = "";
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) s.push_back(c), c = getch();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (register int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
inline T read() {
    register T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
inline void write(const T& t) {
    register T x = t;
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putch(qu[qr--]);
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

#define maxn 300005

int a[maxn], maxx[maxn], minn[maxn];

long long work(int l, int r) {
    if (l == r) return 1;
    int mid = (l + r) >> 1;
    long long answer = work(l, mid) + work(mid + 1, r);
    maxx[mid] = minn[mid] = a[mid], maxx[mid + 1] = minn[mid + 1] = a[mid + 1];
    for (register int i = mid - 1; i >= l; i--) maxx[i] = max(maxx[i + 1], a[i]), minn[i] = min(minn[i + 1], a[i]);
    for (register int i = mid + 2; i <= r; i++) maxx[i] = max(maxx[i - 1], a[i]), minn[i] = min(minn[i - 1], a[i]);
    for (register int i = l; i <= mid; i++) {
        register int j = i + maxx[i] - minn[i];
        if (mid < j && j <= r && maxx[i] > maxx[j] && minn[i] < minn[j]) answer++;
    }
    for (register int i = mid + 1; i <= r; i++) {
        register int j = i - maxx[i] + minn[i];
        if (l <= j && j <= mid && maxx[j] < maxx[i] && minn[j] > minn[i]) answer++;
    }
    static map<int, int> record;
    record.clear();
    for (register int i = mid + 1, p1 = mid, p2 = mid; i <= r; i++) {
        while (p1 >= l && minn[p1] > minn[i]) record[p1 + maxx[p1]]++, p1--;
        while (p2 > p1 && maxx[p2] < maxx[i]) record[p2 + maxx[p2]]--, p2--;
        answer += record[i + minn[i]];
    }
    record.clear();
    for (register int i = mid, p1 = mid + 1, p2 = mid + 1; i >= l; i--) {
        while (p2 <= r && minn[p2] > minn[i]) record[p2 - maxx[p2]]++, p2++;
        while (p1 < p2 && maxx[p1] < maxx[i]) record[p1 - maxx[p1]]--, p1++;
        answer += record[i - minn[i]];
    }
    record.clear();
    return answer;
}

int main() {
    int n = read<int>();
    for (register int i = 1, x; i <= n; i++) x = read<int>(), a[x] = read<int>();
    write(work(1, n)), putch('\n');
    return 0;
}  // awawa