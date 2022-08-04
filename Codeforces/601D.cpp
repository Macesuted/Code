/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = getchar()) x = x * 10 + (c & 15);
    return x * f;
}

#define maxn 300005

class Trie {
   private:
    struct Node {
        Node* son[26];
        Node(void) {
            for (int i = 0; i < 26; i++) son[i] = NULL;
        }
    };

    Node* root;

    void merge(Node*& p, Node* oth) {
        if (p == NULL) return p = oth, void();
        if (oth == NULL) return;
        size--;
        for (int i = 0; i < 26; i++) merge(p->son[i], oth->son[i]);
        return;
    }

   public:
    int size;

    Trie(void) { root = new Node(), size = 0; }
    void pushFront(char c) {
        Node* p = root;
        root = new Node();
        root->son[c - 'a'] = p;
        size++;
        return;
    }
    void merge(Trie* oth) { return size += oth->size + 1, merge(root, oth->root); }
};

char a[maxn];
vector<vector<int>> graph;
Trie* trie[maxn];

int siz[maxn], son[maxn], answer[maxn], c[maxn];

void dfs1(int p, int pre = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != pre) {
            dfs1(i, p);
            siz[p] += siz[i];
            if (!son[p] || siz[i] > siz[son[p]]) son[p] = i;
        }
    return;
}
void dfs2(int p, int pre = -1) {
    if (son[p])
        dfs2(son[p], p), trie[p] = trie[son[p]];
    else
        trie[p] = new Trie();
    for (auto i : graph[p])
        if (i != pre && i != son[p]) dfs2(i, p), trie[p]->merge(trie[i]);
    trie[p]->pushFront(a[p]);
    answer[p] = trie[p]->size + c[p];
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(8);
    int n = read<int>();
    for (int i = 1; i <= n; i++) c[i] = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = getchar();
        while (a[i] < 'a' || a[i] > 'z') a[i] = getchar();
    }
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    dfs1(1), dfs2(1);
    int maxv = 0, maxcnt = 0;
    for (int i = 1; i <= n; i++)
        if (answer[i] > maxv)
            maxv = answer[i], maxcnt = 1;
        else if (answer[i] == maxv)
            maxcnt++;
    cout << maxv << endl << maxcnt << endl;
    return 0;
}