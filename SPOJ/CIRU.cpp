/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1005
#define eps 1e-8

typedef pair<double, int> pdi;

struct Circle {
    double x, y, r;
    inline bool operator<(const Circle& oth) const { return this->r < oth.r; }
};

Circle a[maxn];
int n;

vector<pdi> S;

double f(double x) {
    S.clear();
    for (register int i = 1; i <= n; i++) {
        double dist = fabs(a[i].x - x);
        if (dist > a[i].r) continue;
        double t = sqrt(a[i].r * a[i].r - dist * dist);
        S.push_back((pdi){a[i].y - t, 1}), S.push_back((pdi){a[i].y + t, -1});
    }
    if (S.empty()) return 0;
    sort(S.begin(), S.end());
    double ans = 0;
    int pre = S[0].second;
    for (register int i = 1; i < S.size(); i++) {
        if (pre > 0) ans += S[i].first - S[i - 1].first;
        pre += S[i].second;
    }
    return ans;
}

inline double e(double l, double r) { return (r - l) * (f(l) + 4 * f((l + r) / 2) + f(r)) / 6; }

double simpson(double l, double r, double elr) {
    double mid = (l + r) / 2;
    double elm = e(l, mid), emr = e(mid, r);
    if (fabs(elm + emr - elr) < eps) return e(l, r);
    return simpson(l, mid, elm) + simpson(mid, r, emr);
}

int main() {
    scanf("%d", &n);
    for (register int i = 1; i <= n; i++) scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].r);
    sort(a + 1, a + n + 1);
    int tn = n;
    n = 0;
    for (register int i = 1; i <= tn; i++) {
        bool check = true;
        for (register int j = i + 1; check && j <= tn; j++)
            if ((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y) <=
                (a[i].r - a[j].r) * (a[i].r - a[j].r))
                check = false;
        if (check) swap(a[i], a[++n]);
    }
    printf("%.3lf\n", simpson(-2e3, 2e3, e(-2e3, 2e3)));
    return 0;
}