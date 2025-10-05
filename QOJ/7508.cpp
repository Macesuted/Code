/**
 * @file 7508.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 12005
#define maxq 10005

const int klim = 1e9;

struct Block {
    int64_t cnt, scnt;

    array<int, 16> vals, svals;

    vector<Block*> childs;
    vector<array<int, 16>> preVal;
    vector<int64_t> preCnt;
};

string code[maxn];
int k[maxq], v[maxq][4], ans[maxq][4], rig[maxn];

int trans(string s) { return s[0] - 'a'; }
int calc(string op, int u, int v) { return op.substr(0, 2) == "or" ? (u | v) : op.substr(0, 3) == "and" ? (u & v) : (u ^ v); }

array<int, 16> add(array<int, 16> a, array<int, 16> b) {
    array<int, 16> ans;
    for (int i = 0; i < 16; i++) ans[i] = b[a[i]];
    return ans;
}
array<int, 16> pow(array<int, 16> a, int m) {
    array<int, 16> ans;
    for (int i = 0; i < 16; i++) ans[i] = i;
    while (m) {
        if (m & 1) ans = add(ans, a);
        a = add(a, a);
        m >>= 1;
    }
    return ans;
}

Block* build(int d, int l, int r) {
    Block* ans = new Block();

    if (l == r) {
        ans->scnt = ans->cnt = 1;

        stringstream ssin = stringstream(code[l]);
        string op;
        ssin >> op;
        if (op.back() != 'i') {
            string sr1, sr2;
            ssin >> sr1 >> sr2;
            int r1 = trans(sr1), r2 = trans(sr2);
            for (int S = 0; S < 16; S++) ans->svals[S] = S ^ (((S >> r1 & 1) ^ calc(op, S >> r1 & 1, S >> r2 & 1)) << r1);
        } else {
            string sr;
            int val;
            ssin >> sr >> val;
            int r = trans(sr);
            for (int S = 0; S < 16; S++) ans->svals[S] = S ^ (((S >> r & 1) ^ calc(op, S >> r & 1, val >> d & 1)) << r);
        }
        ans->vals = ans->svals;

        return ans;
    }

    int m = stoi(code[l].substr(7));

    ans->scnt = 0;
    for (int S = 0; S < 16; S++) ans->svals[S] = S;

    for (int i = l + 1, j; i < r; i = j + 1) {
        j = i;
        Block* ch;
        if (code[i].substr(0, 6) == "repeat") j = rig[i];
        ch = build(d, i, j);

        ans->scnt += ch->cnt;
        ans->svals = add(ans->svals, ch->vals);
        ans->childs.push_back(ch);
        ans->preVal.push_back(ans->svals);
        ans->preCnt.push_back(ans->scnt);

        if (ans->scnt >= klim) return ans->cnt = ans->scnt, ans;
    }

    ans->cnt = ans->scnt * m;
    ans->vals = pow(ans->svals, m);

    return ans;
}

void print(Block* p) {
    cerr << "cnt: " << p->cnt << endl;
    for (int S = 0; S < 16; S++) cerr << p->vals[S] << ' ';
    cerr << endl;
    cerr << "BEGIN" << endl;
    for (auto x : p->childs) print(x);
    cerr << "END" << endl;
    return;
}

vector<Block*> path;
vector<int64_t> cnt;
vector<array<int, 16>> preS;

void slim(Block* p, int& k) {
    if (p->cnt <= k) return path.push_back(p), cnt.push_back(p->cnt), preS.push_back(p->vals), k -= p->cnt, void();

    int t = k / p->scnt;

    if (t) path.push_back(p), cnt.push_back(t * p->scnt), preS.push_back(pow(p->svals, t)), k -= t * p->scnt;

    for (auto q : p->childs) {
        slim(q, k);
        if (!k) return;
    }

    return;
}

void solve(void) {
    int n, q;
    cin >> n >> q;

    string s;
    getline(cin, s);
    code[0] = "repeat 1";
    for (int i = 1; i <= n; i++) getline(cin, s), code[i] = s;
    code[n + 1] = "end";

    stack<int> S;
    for (int i = 0; i <= n + 1; i++) {
        if (code[i].substr(0, 6) == "repeat") S.push(i);
        if (code[i].substr(0, 3) == "end") rig[S.top()] = i, S.pop();
    }

    for (int i = 1; i <= q; i++) cin >> k[i] >> v[i][0] >> v[i][1] >> v[i][2] >> v[i][3];

    for (int d = 0; d < 8; d++) {
        Block* root = build(d, 0, n + 1);

        path.clear(), cnt.clear(), preS.clear();

        path.push_back(new Block());
        cnt.push_back(0);
        array<int, 16> alli;
        for (int i = 0; i < 16; i++) alli[i] = i;
        preS.push_back(alli);

        slim(root, *(new int(klim)));

        for (size_t i = 1; i < cnt.size(); i++) cnt[i] += cnt[i - 1], preS[i] = add(preS[i - 1], preS[i]);

        for (int i = 1; i <= q; i++) {
            int S = 0;
            for (int t = 0; t < 4; t++) S |= (v[i][t] >> d & 1) << t;

            int px = upper_bound(cnt.begin(), cnt.end(), k[i]) - cnt.begin() - 1, rest = k[i];
            S = preS[px][S], rest -= cnt[px];

            if (rest) {
                Block* blk = path[px + 1];
                while (rest) {
                    int t = rest / blk->scnt;
                    if (t) S = pow(blk->svals, t)[S], rest -= t * blk->scnt;

                    int p = upper_bound(blk->preCnt.begin(), blk->preCnt.end(), rest) - blk->preCnt.begin();
                    if (p) S = blk->preVal[p - 1][S], rest -= blk->preCnt[p - 1];
                    blk = blk->childs[p];
                }
            }

            for (int t = 0; t < 4; t++) ans[i][t] |= (S >> t & 1) << d;
        }
    }

    for (int i = 1; i <= q; i++) cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << ' ' << ans[i][3] << endl;

    return;
}

bool mem2;

int main() {
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