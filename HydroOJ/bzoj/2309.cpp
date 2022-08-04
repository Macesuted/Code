/**
 * @file 2309.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-08
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

#define maxn 40005
#define maxq 100005

typedef pair<int, int> pii;

class Trie {
   private:
    struct Node {
        int cnt, id, lef[27], rig[27], fLef, fRig;
        Node *fa, *child[27];
        string childstr[27];
        Node(void) {
            fa = NULL, cnt = id = 0, fLef = fRig = -1;
            for (int i = 0; i < 27; i++) child[i] = NULL, lef[i] = rig[i] = -1;
        }
    };

    Node* root;

    Node* find(const string& s) {
        Node* p = root;
        for (int i = 0; i < (int)s.size();)
            tie(i, p) = make_pair(i + p->childstr[s[i] - 'a'].size(), p->child[s[i] - 'a']);
        return p;
    }
    int64_t query(Node* p, int len = 0) {
        int64_t ans = 0;
        for (int i = 0; i < 27; i++)
            if (p->child[i] != NULL) ans += query(p->child[i], len + p->childstr[i].size());
        ans += max(0LL, p->cnt - 1LL) * len * len;
        return ans;
    }
    void print(Node* p) {
        if (p->id) return write(p->id), putch(' ');
        bool vis[27];
        memset(vis, 0, sizeof(vis));
        if (~p->fLef) {
            int x = p->fLef;
            while (~x) print(p->child[x]), vis[x] = true, x = p->rig[x];
        }
        stack<int> cache;
        if (~p->fRig && !vis[p->fRig]) {
            int x = p->fRig;
            while (~x) cache.push(x), vis[x] = true, x = p->lef[x];
        }
        for (int i = 0; i < 27; i++) {
            if (p->child[i] == NULL || ~p->lef[i] || vis[i]) continue;
            int x = i;
            while (~x) print(p->child[x]), vis[x] = true, x = p->rig[x];
        }
        while (!cache.empty()) print(p->child[cache.top()]), cache.pop();
        return;
    }

   public:
    Trie(void) { root = new Node(); }
    void insert(const string& s, int id) {
        Node* p = root;
        for (auto i : s) {
            if (p->child[i - 'a'] == NULL)
                p->cnt++, p->child[i - 'a'] = new Node(), p->childstr[i - 'a'] = string(1, i);
            p = p->child[i - 'a'];
        }
        return p->id = id, void();
    }
    void compress(void) {
        static queue<Node*> que;
        while (!que.empty()) que.pop();
        que.push(root);
        while (!que.empty()) {
            Node* p = que.front();
            que.pop();
            for (int i = 0; i < 27; i++) {
                if (p->child[i] == NULL) continue;
                Node *x = p->child[i], *c;
                string cache = string(1, 'a' + i);
                while (x->cnt == 1 && !x->id)
                    for (int i = 0; i < 27; i++)
                        if (x->child[i] != NULL) {
                            cache.push_back('a' + i), c = x->child[i], delete x, x = c;
                            break;
                        }
                p->child[i] = x, p->childstr[i] = cache, x->fa = p;
                if (x->cnt) que.push(x);
            }
        }
        return;
    }
    int64_t query(void) { return query(root); }
    bool link(const string& L, const string& R) {
        vector<Node*> ql, qr;
        Node *tl = find(L), *tr = find(R), *lca = root;
        while (tl != root) ql.push_back(tl), tl = tl->fa;
        while (tr != root) qr.push_back(tr), tr = tr->fa;
        while (!ql.empty() && !qr.empty() && ql.back() == qr.back()) lca = ql.back(), ql.pop_back(), qr.pop_back();
        auto getSon = [&](Node* p, Node* s) {
            for (int i = 0; i < 27; i++)
                if (p->child[i] == s) return i;
            return -1;
        };
        auto toRight = [](Node* p, int x) {
            if (x == -1) return -1;
            while (~p->rig[x]) x = p->rig[x];
            return x;
        };
        auto len = [](Node* p, int x) {
            int cnt = 0;
            while (~x) cnt++, x = p->rig[x];
            return cnt;
        };
        int lw = getSon(lca, ql.back()), rw = getSon(lca, qr.back());
        if ((~lca->rig[lw] && lca->rig[lw] != rw) || (~lca->lef[rw] && lca->lef[rw] != lw) || lca->fLef == rw ||
            lca->fRig == lw)
            return false;
        if (toRight(lca, rw) == lw) return false;
        if (~lca->fLef && ~lca->fRig && toRight(lca, lca->fLef) == lw && toRight(lca, rw) == lca->fRig &&
            len(lca, lca->fLef) + len(lca, rw) != lca->cnt)
            return false;
        for (auto i = ql.rbegin(); i + 1 != ql.rend(); i++) {
            int x = getSon(*i, *(i + 1));
            if ((~(*i)->fRig && (*i)->fRig != x) || ~(*i)->rig[x] ||
                (toRight(*i, (*i)->fLef) == x && len(*i, (*i)->fLef) != (*i)->cnt))
                return false;
        }
        for (auto i = qr.rbegin(); i + 1 != qr.rend(); i++) {
            int x = getSon(*i, *(i + 1));
            if ((~(*i)->fLef && (*i)->fLef != x) || ~(*i)->lef[x] ||
                (toRight(*i, x) == (*i)->fRig && len(*i, x) != (*i)->cnt))
                return false;
        }
        lca->rig[lw] = rw, lca->lef[rw] = lw;
        for (auto i = ql.rbegin(); i + 1 < ql.rend(); i++) (*i)->fRig = getSon(*i, *(i + 1));
        for (auto i = qr.rbegin(); i + 1 < qr.rend(); i++) (*i)->fLef = getSon(*i, *(i + 1));
        return true;
    }
    void print(void) { return print(root); }
} trie;

string s[maxn];
pii ques[maxq];

void solve(void) {
    int n = read(), q = read();
    for (int i = 1; i <= n; i++) trie.insert(s[i] = getstr() + "{", i);
    trie.compress(), write(trie.query()), putch('\n');
    for (int i = 1; i <= q; i++) ques[i].first = read(), ques[i].second = read();
    stack<int> answer;
    for (int i = q; i; i--)
        if (trie.link(s[ques[i].first], s[ques[i].second])) answer.push(i);
    write(answer.size()), putch(' ');
    while (!answer.empty()) write(answer.top()), putch(' '), answer.pop();
    putch('\n'), trie.print(), putch('\n');
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
