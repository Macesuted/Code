/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 * @brief
 *      My tutorial: https://macesuted.cn/article/h1031/
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
    for (register int i = 0; i < s.size(); i++) s[i] = que.front(), que.pop();
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

#define maxn 100005

vector<vector<int> > graph;

int siz[maxn], son[maxn];

void insert(int p) {
    putch('+'), write(p);
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++) insert(*i);
    return;
}
void erase(int p) {
    for (register int i = 1; i <= siz[p]; i++) putch('-');
    return;
}

class HuffmanTree {
   public:
    struct Node {
        int id, siz;
        Node *l, *r;
        Node(int _id = 0) { siz = ::siz[id = _id], l = r = NULL; }
    };

    typedef pair<int, Node*> pin;

    Node* root;

    void destroy(Node* p) {
        if (p == NULL) return;
        if (p->l != NULL) destroy(p->l);
        if (p->r != NULL) destroy(p->r);
        delete p;
    }

    HuffmanTree(void) { root = NULL; }
    ~HuffmanTree(void) { destroy(root); }
    void build(const vector<int>& sons) {
        static priority_queue<pin, vector<pin>, greater<pin> > que;
        while (!que.empty()) que.pop();
        for (vector<int>::const_iterator i = sons.cbegin(); i != sons.cend(); i++) {
            Node* p = new Node(*i);
            que.push((pin){siz[*i], p});
        }
        while (que.size() > 1) {
            Node* l = que.top().second;
            que.pop();
            Node* r = que.top().second;
            que.pop();
            Node* p = new Node();
            p->l = l, p->r = r;
            p->siz = l->siz + r->siz;
            que.push((pin){p->siz, p});
        }
        root = que.top().second, que.pop();
        return;
    }
    void insert(Node* p) {
        if (p == NULL) return;
        if (p->id) return ::insert(p->id);
        if (p->l != NULL) insert(p->l);
        if (p->r != NULL) insert(p->r);
        return;
    }
    void erase(Node* p) {
        if (p == NULL) return;
        if (p->id) return ::erase(p->id);
        if (p->l != NULL) erase(p->l);
        if (p->r != NULL) erase(p->r);
        return;
    }
};

void dfs1(int p) {
    siz[p] = 1, son[p] = 0;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++) {
        dfs1(*i);
        siz[p] += siz[*i];
        if (son[p] == 0 || siz[*i] > siz[son[p]]) son[p] = *i;
    }
    return;
}
void dfs3(HuffmanTree&, HuffmanTree::Node*);
void dfs2(int p) {
    vector<int> chain, sons;
    chain.clear(), sons.clear();
    int x = p;
    while (x) chain.push_back(x), x = son[x];
    for (vector<int>::iterator i = chain.begin(); i != chain.end(); i++) {
        putch('='), write(*i), putch('+'), write(*i);
        for (vector<int>::iterator j = graph[*i].begin(); j != graph[*i].end(); j++)
            if (*j != son[*i]) sons.push_back(*j), insert(*j);
    }
    for (vector<int>::reverse_iterator i = sons.rbegin(); i != sons.rend(); i++) erase(*i);
    for (vector<int>::reverse_iterator i = chain.rbegin(); i != chain.rend(); i++) putch('-');
    for (vector<int>::iterator i = chain.begin(); i != chain.end(); i++) putch('+'), write(*i);
    if (!sons.empty()) {
        HuffmanTree tree;
        tree.build(sons);
        dfs3(tree, tree.root);
    }
    for (vector<int>::reverse_iterator i = chain.rbegin(); i != chain.rend(); i++) putch('-');
    return;
}
void dfs3(HuffmanTree& tree, HuffmanTree::Node* p) {
    if (p == NULL) return;
    if (p->id) return dfs2(p->id);
    tree.insert(p->r);
    if (p->l != NULL) dfs3(tree, p->l);
    tree.erase(p->r);
    tree.insert(p->l);
    if (p->l != NULL) dfs3(tree, p->r);
    tree.erase(p->l);
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n) {
        graph.resize(n + 1);
        for (register int i = 2, fa; i <= n; i++) cin >> fa, graph[fa].push_back(i);
        dfs1(1), dfs2(1);
        putch('!'), putch('\n');
        graph.clear();
    }
    return 0;
}