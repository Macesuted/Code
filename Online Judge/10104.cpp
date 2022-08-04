/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) return x = 1, y = 0, a;
    long long g = exgcd(b, a % b, x, y);
    return tie(x, y) = make_tuple(y, x - a / b * y), g;
}
long long getSolution(long long a, long long b, long long &x, long long &y) {
    long long g = exgcd(abs(a), abs(b), x, y);
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return g;
}

struct Ans {
    long long x, y;
    inline bool operator<(const Ans &oth) const {
        return abs(x) + abs(y) < abs(oth.x) + abs(oth.y) || (abs(x) + abs(y) == abs(oth.x) + abs(oth.y) && x <= y);
    }
};

int main() {
    ios::sync_with_stdio(false);
    long long x, y;
    while (cin >> x >> y) {
        long long a, b, g = getSolution(x, y, a, b);
        cout << a << ' ' << b << ' ' << g << endl;
    }
    return 0;
}