/**
 * @file 3804.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
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

class SuffixAutomaton {
   private:
    struct Node {
        int cnt, len, dep;
        int son[26], fa;
        vector<int> graph;
        Node(void) {
            cnt = len = dep = fa = 0;
            for (int i = 0; i < 26; i++) son[i] = 0;
        }
    };

    Node tree[2000000];
    int root, last, tail;

    long long calc(int p) {
        long long ans = 0;
        for (auto i : tree[p].graph) ans = max(ans, calc(i)), tree[p].cnt += tree[i].cnt;
        if (tree[p].cnt != 1) ans = max(ans, 1LL * tree[p].cnt * tree[p].len);
        return ans;
    }

   public:
    SuffixAutomaton(void) { root = last = (tail = 1)++; }
    void insert(char c) {
        int tc = c - 'a';
        int p = last, np = last = tail++;
        tree[np].len = tree[p].len + 1, tree[np].cnt = 1;
        while (p && !tree[p].son[tc]) tree[p].son[tc] = np, p = tree[p].fa;
        if (!p) return tree[np].fa = root, void();
        int q = tree[p].son[tc];
        if (tree[p].len + 1 == tree[q].len) return tree[np].fa = q, void();
        int nq = tail++;
        tree[nq] = tree[q], tree[nq].cnt = 0, tree[nq].len = tree[p].len + 1, tree[q].fa = tree[np].fa = nq;
        while (p && tree[p].son[tc] == q) tree[p].son[tc] = nq, p = tree[p].fa;
        return;
    }
    void build(void) {
        for (int i = 1; i < tail; i++)
            if (tree[i].fa) tree[tree[i].fa].graph.push_back(i);
        return;
    }
    long long calc(void) { return calc(root); }
} SAM;

void solve(void) {
    string s = getstr();
    for (auto i : s) SAM.insert(i);
    SAM.build(), write(SAM.calc()), putch('\n');
    return;
}

bool mem2;

int main() {
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
