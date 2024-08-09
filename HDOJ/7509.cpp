/**
 * @file 7509.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int sti(string s) {
    int v;
    if ('2' <= s[0] && s[0] <= '9')
        v = s[0] - '0';
    else if (s[0] == 'T')
        v = 10;
    else if (s[0] == 'J')
        v = 11;
    else if (s[0] == 'Q')
        v = 12;
    else if (s[0] == 'K')
        v = 13;
    else if (s[0] == 'A')
        v = 14;
    else
        assert(false);
    v *= 10;
    if (s[1] == 'H')
        v += 1;
    else if (s[1] == 'D')
        v += 2;
    else if (s[1] == 'C')
        v += 3;
    else if (s[1] == 'S')
        v += 4;
    else
        assert(false);
    return v;
}

int kindS[20];
class Cards {
   private:
    array<int, 5> a;
    int model, cnt;

    void calc(void) {
        for (int i = 2; i <= 14; i++) kindS[i] = 0;
        for (int i = 0; i < 5; i++) kindS[a[i] / 10]++;
        sort(a.begin(), a.end(), [&](int x, int y) {
            if (kindS[x / 10] != kindS[y / 10]) return kindS[x / 10] > kindS[y / 10];
            return x / 10 > y / 10;
        });

        bool tong = true;
        for (int i = 1; i < 5; i++) tong &= (a[i - 1] % 10 == a[i] % 10);

        bool shun = true, shunSpe = (a[0] / 10 == 14);
        for (int i = 1; i < 5; i++) shun &= (a[i - 1] / 10 - a[i] / 10 == 1);
        for (int i = 1; i < 5; i++) shunSpe &= (a[i] / 10 == 6 - i);
        if (shunSpe) {
            int v = a[0];
            for (int i = 0; i < 4; i++) a[i] = a[i + 1];
            a[4] = v - 130;
        }

        if (tong && shun && a[4] / 10 == 10) return model = 0, void();
        if (tong && (shun || shunSpe)) return model = 1, void();
        if (a[0] / 10 == a[1] / 10 && a[1] / 10 == a[2] / 10 && a[2] / 10 == a[3] / 10) return model = 2, void();
        if (a[0] / 10 == a[1] / 10 && a[1] / 10 == a[2] / 10 && a[3] / 10 == a[4] / 10) return model = 3, void();
        if (tong) return model = 4, void();
        if (shun || shunSpe) return model = 5, void();
        if (a[0] / 10 == a[1] / 10 && a[1] / 10 == a[2] / 10) return model = 6, void();
        if (a[0] / 10 == a[1] / 10 && a[2] / 10 == a[3] / 10) return model = 7, void();
        if (a[0] / 10 == a[1] / 10) return model = 8, void();
        return model = 9, void();
    }

   public:
    Cards(void) { model = -1, cnt = 0; }

    bool operator<(const Cards& o) const {
        if (this->model != o.model) return this->model > o.model;
        for (int i = 0; i < 5; i++)
            if (this->a[i] / 10 != o.a[i] / 10) return this->a[i] / 10 < o.a[i] / 10;
        return false;
    }

    void pushBack(string s) {
        a[cnt++] = sti(s);
        if (cnt == 5) calc();
        return;
    }
    void pushBack(int s) {
        a[cnt++] = s;
        if (cnt == 5) calc();
        return;
    }
    void popBack(void) { return cnt--, model = -1, void(); }

    void print(void) {
        cerr << "! " << model << endl;
        for (int i = 0; i < 5; i++) cerr << a[i] << ' ';
        cerr << endl;
        return;
    }
};

set<int> rest;
int a[13];

Cards query(vector<int> a) {
    assert(a.size() == 7);
    Cards ans;
    bool vis = false;
    for (int v1 = 0; v1 < 7; v1++) {
        for (int v2 = v1 + 1; v2 < 7; v2++) {
            for (int v3 = v2 + 1; v3 < 7; v3++) {
                for (int v4 = v3 + 1; v4 < 7; v4++) {
                    for (int v5 = v4 + 1; v5 < 7; v5++) {
                        Cards cur;
                        cur.pushBack(a[v1]);
                        cur.pushBack(a[v2]);
                        cur.pushBack(a[v3]);
                        cur.pushBack(a[v4]);
                        cur.pushBack(a[v5]);
                        if (!vis) ans = cur, vis = true;
                        if (ans < cur) ans = cur;
                    }
                }
            }
        }
    }
    return ans;
}
int root;
int query(void) {
    int ans = 0;
    for (auto i = rest.begin(); i != rest.end(); i++)
        for (auto j = i; j != rest.end(); j++) {
            if (i == j) continue;
            a[11] = *i, a[12] = *j;
            vector<int> vec;
            for (int i = 8; i < 13; i++) vec.push_back(a[i]);
            vec.push_back(a[root * 2]), vec.push_back(a[root * 2 + 1]);
            Cards own = query(vec);
            vec.pop_back(), vec.pop_back();
            int cnt = 3;
            for (int x = 0; x < 4; x++)
                if (x != root) {
                    vec.push_back(a[x * 2]), vec.push_back(a[x * 2 + 1]);
                    if (own < query(vec)) cnt--;
                    vec.pop_back(), vec.pop_back();
                }
            ans += (cnt == 3);
        }
    return ans;
}

string s[13];
void solve(void) {
    for (int i = 8; i < 11; i++) cin >> s[i], a[i] = sti(s[i]);
    for (int i = 0; i < 8; i++) cin >> s[i], a[i] = sti(s[i]);
    cin >> root;
    for (int i = 2; i <= 14; i++)
        for (int j = 1; j <= 4; j++) rest.insert(i * 10 + j);
    for (int i = 0; i < 11; i++) rest.erase(a[i]);
    pair<int, string> ans = {query(), ""};
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++) {
            if (s[i] >= s[j]) continue;
            swap(a[i], a[j]);
            pair<int, string> ret = {query(), s[i] + " " + s[j]};
            if (ans.first < ret.first || (ans.first == ret.first && ans.second > ret.second)) ans = ret;
            swap(a[i], a[j]);
        }
    if (ans.second.empty()) return cout << "None" << endl, void();
    cout << ans.second << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
