/**
 * @file 12805.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

#ifdef MACESUTED

bool mem1;

#endif

class Constellation {
   private:
    struct Node {
        int x, y;
        double p;
        inline bool operator!=(const Node& oth) const { return this->x != oth.x || this->y != oth.y; }
    };

    vector<Node> P;
    deque<Node> Q;

   public:
    double expectation(vector<int> x, vector<int> y, vector<int> prob) {
        int n = x.size();
        P.resize(n + 1);
        for (int i = 0; i < n; i++) P[i + 1] = {x[i], y[i], prob[i] / 1000.};
        double ans = 0;
        auto cro = [](Node a, Node b) { return a.x * b.y - a.y * b.x; };
        auto cmp = [cro](Node a, Node b, Node p) {
            a.x -= p.x, a.y -= p.y, b.x -= p.x, b.y -= p.y;
            return cro(a, b);
        };
        auto in = [cmp](Node a, Node b, Node p) {
            auto cp = cmp(a, b, p);
            if (cp != 0) return cp > 0;
            if ((a.x > p.x) == (b.x > p.x) && (a.y > p.y) == (b.y > p.y)) return false;
            return true;
        };
        auto dist = [](Node a, Node b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); };
        for (int i = 1; i <= n; i++) {
            Q.clear();
            for (int j = 0; j <= n; j++)
                if (i != j) Q.push_back(P[j]);
            sort(Q.begin() + 1, Q.begin() + n, [=](Node a, Node b) {
                bool bela = a.y > P[i].y, belb = b.y > P[i].y;
                if (a.y == P[i].y) bela = a.x > P[i].x;
                if (b.y == P[i].y) belb = b.x > P[i].x;
                if (bela != belb) return bela < belb;
                auto cp = cmp(a, b, P[i]);
                if (cp != 0) return cp > 0;
                return dist(a, P[i]) < dist(b, P[i]);
            });
            double p = 0;
            for (int l = 1, r = 1; l < n; l++) {
                p /= 1 - Q[l].p;
                r = l;
                if (l == r) {
                    r = l % (n - 1) + 1, p = 1;
                    while (r != l && Q[r].p != 1 && cmp(Q[l], Q[r], P[i]) == 0) p *= 1 - Q[r].p, r = r % (n - 1) + 1;
                }
                while (r != l && Q[r].p != 1 && in(Q[l], Q[r], P[i])) p *= 1 - Q[r].p, r = r % (n - 1) + 1;
                if (r != l && Q[r].p == 1 && in(Q[l], Q[r], P[i])) continue;
                ans += cro(Q[l], P[i]) / 2. * p * Q[l].p * P[i].p;
            }
        }
        return ans;
    }
};

#ifdef MACESUTED

Constellation _;

bool mem2;

int main() {
    ios::sync_with_stdio(false);
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    vector<int> x, y, prob;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        x.push_back(t);
    }
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        y.push_back(t);
    }
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        prob.push_back(t);
    }
    cout << setprecision(16) << _.expectation(x, y, prob) << endl;

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}

#endif