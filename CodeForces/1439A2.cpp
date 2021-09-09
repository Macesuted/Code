/**
 * @author Macesuted (macesuted@outlook.com)
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
    queue<char> que;
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) que.push(c), c = getch();
    string s;
    s.resize(que.size());
    for (register int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
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

#define maxn 105

typedef pair<int, int> pii;

bool a[maxn][maxn];
int n, m;

struct Option {
    int a1, b1, a2, b2, a3, b3;
};

vector<Option> answer;

inline void sign(int a1, int b1, int a2, int b2, int a3, int b3) {
    a[a1][b1] ^= true, a[a2][b2] ^= true, a[a3][b3] ^= true;
    answer.push_back((Option){a1, b1, a2, b2, a3, b3});
    return;
}
void solveblock(int i, int j) {
    string str;
    str.push_back('0' + a[i][j]);
    str.push_back('0' + a[i][j + 1]);
    str.push_back('0' + a[i + 1][j]);
    str.push_back('0' + a[i + 1][j + 1]);
    if (str == "0000") return;
    if (str == "1000") return sign(i, j, i, j + 1, i + 1, j), solveblock(i, j);
    if (str == "0100") return sign(i, j, i, j + 1, i + 1, j), solveblock(i, j);
    if (str == "0010") return sign(i, j, i, j + 1, i + 1, j), solveblock(i, j);
    if (str == "0001") return sign(i, j + 1, i + 1, j, i + 1, j + 1), solveblock(i, j);
    if (str == "1100") return sign(i, j, i + 1, j, i + 1, j + 1), solveblock(i, j);
    if (str == "1010") return sign(i, j, i, j + 1, i + 1, j + 1), solveblock(i, j);
    if (str == "1001") return sign(i, j, i, j + 1, i + 1, j), solveblock(i, j);
    if (str == "0110") return sign(i, j, i, j + 1, i + 1, j + 1), solveblock(i, j);
    if (str == "0101") return sign(i, j, i, j + 1, i + 1, j), solveblock(i, j);
    if (str == "0011") return sign(i, j, i, j + 1, i + 1, j), solveblock(i, j);
    if (str == "1110") return sign(i, j, i, j + 1, i + 1, j);
    if (str == "1101") return sign(i, j, i, j + 1, i + 1, j + 1);
    if (str == "1011") return sign(i, j, i + 1, j, i + 1, j + 1);
    if (str == "0111") return sign(i, j + 1, i + 1, j, i + 1, j + 1);
    if (str == "1111") return sign(i, j, i, j + 1, i + 1, j), solveblock(i, j);
    return;
}
void solve(void) {
    answer.clear();
    n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= m; j++) {
            char c = getch();
            while (c != '0' && c != '1') c = getch();
            a[i][j] = (c == '1');
        }
    for (register int i = 1; i <= n; i++)
        if (i + 1 == n) {
            for (register int j = 1; j < m; j++)
                if (j + 1 == m)
                    solveblock(i, j);
                else {
                    if (!a[i][j] && !a[i + 1][j]) continue;
                    vector<pii> li;
                    if (a[i][j]) li.push_back((pii){i, j});
                    if (a[i + 1][j]) li.push_back((pii){i + 1, j});
                    if (li.size() < 3) li.push_back((pii){i, j + 1});
                    if (li.size() < 3) li.push_back((pii){i + 1, j + 1});
                    sign(li[0].first, li[0].second, li[1].first, li[1].second, li[2].first, li[2].second);
                }
        } else {
            for (register int j = 1; j <= m; j += 2) {
                if (j == m) j--;
                if (!a[i][j] && !a[i][j + 1]) continue;
                vector<pii> li;
                if (a[i][j]) li.push_back((pii){i, j});
                if (a[i][j + 1]) li.push_back((pii){i, j + 1});
                if (li.size() < 3) li.push_back((pii){i + 1, j});
                if (li.size() < 3) li.push_back((pii){i + 1, j + 1});
                sign(li[0].first, li[0].second, li[1].first, li[1].second, li[2].first, li[2].second);
            }
        }
    write((int)answer.size()),
        putch('\n');
    for (vector<Option>::iterator i = answer.begin(); i != answer.end(); i++)
        write(i->a1), putch(' '), write(i->b1), putch(' '),
            write(i->a2), putch(' '), write(i->b2), putch(' '),
            write(i->a3), putch(' '), write(i->b3), putch('\n');
    return;
}

int main() {
    int _ = read<int>();
    while (_--) solve();
    return 0;
}