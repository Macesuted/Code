/**
 * @file 207.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005
#define _ get

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int> tiiii;

vector<int> graph[maxn];
int dep[maxn], son[maxn];
bool vis[maxn];
tiii pos[maxn], ans[maxn];
vector<tiiii> task[maxn];
vector<tiiii> nodes, ques;
vector<int>* rec[maxn];

void dfs1(int p, int pre = -1) {
    dep[p] = 0;
    vector<int> rec;
    for (auto i : graph[p])
        if (i != pre) {
            dfs1(i, p), dep[p] = max(dep[p], dep[i] + 1), rec.push_back(dep[i] + 1);
            if (!son[p] || dep[i] > dep[son[p]]) son[p] = i;
        }
    return;
}
void dfs2(int p, int pre = -1) {
    vector<int> rec;
    for (auto i : graph[p]) rec.push_back(dep[i] + 1);
    sort(rec.begin(), rec.end(), greater<int>());
    while (rec.size() < 3) rec.push_back(0);
    nodes.emplace_back(rec[0] + 1, rec[1] + 1, rec[2] + 1, p);
    for (auto i : graph[p]) {
        if (i == pre) continue;
        int _depp = dep[p], _depi = dep[i];
        dep[p] = rec[rec[0] == dep[i] + 1], dep[i] = max(dep[i], dep[p] + 1);
        dfs2(i, p);
        dep[p] = _depp, dep[i] = _depi;
    }
    return;
}
void dfs3(int p, int pre = -1) {
    for (auto i : graph[p])
        if (i != pre) dfs3(i, p), rec[i]->push_back(p);
    rec[p] = (son[p] ? rec[son[p]] : new vector<int>{p});
    return;
}
void dfs4(int p, int pre = -1) {
    vector<pair<int, vector<int>*>> vec;
    for (auto i : graph[p]) vec.emplace_back(i, rec[i]);
    sort(vec.begin(), vec.end(), [](auto x, auto y) { return _<1>(x)->size() > _<1>(y)->size(); });
    while (vec.size() < 3) vec.emplace_back(p, new vector<int>{p});
    for (auto i : task[p]) {
        int id = _<3>(i);
        _<0>(ans[id]) = (*_<1>(vec[0]))[_<1>(vec[0])->size() - 1 - _<0>(i)];
        _<1>(ans[id]) = (*_<1>(vec[1]))[_<1>(vec[1])->size() - 1 - _<1>(i)];
        _<2>(ans[id]) = (*_<1>(vec[2]))[_<1>(vec[2])->size() - 1 - _<2>(i)];
    }
    for (auto i : graph[p]) {
        if (i == pre) continue;
        vector<int>* _recp = rec[p];
        rec[p] = _<1>(vec[i == _<0>(vec[0])]), rec[p]->push_back(i), rec[i]->pop_back();
        dfs4(i, p);
        rec[p]->pop_back(), rec[i]->push_back(p), rec[p] = _recp;
    }
    return;
}
void CDQ(int l, int r, int nl, int nr, int ql, int qr) {
    if (ql > qr || nl > nr || l == r) {
        sort(&ques[nl], &ques[nr] + 1, [&](tiiii a, tiiii b) { return _<1>(a) < _<1>(b); });
        sort(&nodes[ql], &nodes[qr] + 1, [&](tiiii a, tiiii b) { return _<1>(a) < _<1>(b); });
        return;
    }
    int mid = (l + r) >> 1, nm = nr, qm = qr;
    while (_<0>(ques[nm]) > mid) nm--;
    while (_<0>(nodes[qm]) > mid) qm--;
    CDQ(l, mid, nl, nm, ql, qm), CDQ(mid + 1, r, nm + 1, nr, qm + 1, qr);
    priority_queue<pii, vector<pii>, greater<pii>> que;
    for (int i = qm + 1, j = nl; i <= qr; i++) {
        while (j <= nm && _<1>(ques[j]) < _<1>(nodes[i])) {
            if (!vis[_<3>(ques[j])]) que.emplace(_<2>(ques[j]), j);
            j++;
        }
        while (!que.empty() && _<0>(que.top()) < _<2>(nodes[i])) {
            int p = _<1>(que.top());
            task[_<3>(nodes[i])].emplace_back(ques[p]), vis[_<3>(ques[p])] = true, que.pop();
        }
    }
    sort(&ques[nl], &ques[nr] + 1, [&](tiiii a, tiiii b) { return _<1>(a) < _<1>(b); });
    sort(&nodes[ql], &nodes[qr] + 1, [&](tiiii a, tiiii b) { return _<1>(a) < _<1>(b); });
    return;
}

void solve(void) {
    int n, q;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    cin >> q;
    for (int i = 1, x, y, z; i <= q; i++) {
        cin >> x >> y >> z;
        int d = (y + z - x) / 2;
        vector<pii> vec = {{y - d, 0}, {z - d, 1}, {d, 2}};
        sort(vec.begin(), vec.end(), greater<pii>());
        ques.emplace_back(_<0>(vec[0]), _<0>(vec[1]), _<0>(vec[2]), i), pos[i] = {_<1>(vec[0]), _<1>(vec[1]), _<1>(vec[2])};
    }
    dfs1(1), dfs2(1);
    sort(nodes.begin(), nodes.end()), sort(ques.begin(), ques.end());
    CDQ(1, n, 0, q - 1, 0, n - 1);
    dfs3(1), dfs4(1);
    for (int i = 1; i <= q; i++) {
        array<int, 3> out;
        out[_<0>(pos[i])] = _<0>(ans[i]), out[_<1>(pos[i])] = _<1>(ans[i]), out[_<2>(pos[i])] = _<2>(ans[i]);
        cout << out[0] << ' ' << out[1] << ' ' << out[2] << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("game.in", "r", stdin), freopen("game.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
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