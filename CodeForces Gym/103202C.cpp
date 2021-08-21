/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1000005

bool a[maxn], vis[maxn];
vector<int> limit[maxn], belong[maxn];
int to[maxn], ready[maxn];

inline int getNum(stringstream& in) {
    register char c;
    register int x = 0, f = 1;
    for (c = in.get(); c < '0' || c > '9'; c = in.get())
        if (c == '!')
            f = -1;
        else if (c == '>')
            return 0;
    for (; c <= '9' && c >= '0'; c = in.get()) x = x * 10 + (c & 15);
    return x * f;
}

inline void wrong(void) { cout << "conflict" << endl, exit(0); }

queue<int> que;

void let(int p) {
    bool v = true;
    if (p < 0) v = false, p = -p;
    if (vis[p] && a[p] != v) wrong();
    if (!vis[p]) que.push(p);
    vis[p] = true, a[p] = v;
    return;
}

string str;

int main() {
    ios::sync_with_stdio(false);
    int m, n;
    cin >> m >> n;
    getline(cin, str);
    for (register int i = 1; i <= m; i++) {
        getline(cin, str), str.push_back('#');
        stringstream ssin(str);
        bool cmd1 = true;
        for (string::iterator i = str.begin(); i != str.end(); i++)
            if (*i == '-') cmd1 = false;
        if (cmd1)
            let(getNum(ssin));
        else {
            int t;
            while ((t = getNum(ssin)) != 0) limit[i].push_back(t), belong[t].push_back(i);
            to[i] = getNum(ssin);
        }
    }
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (vector<int>::iterator i = belong[p].begin(); i != belong[p].end(); i++)
            if (++ready[*i] == (int)limit[*i].size()) let(to[*i]);
    }
    for (register int i = 1; i <= n; i++) cout << "FT"[a[i]];
    cout << endl;
    return 0;
}