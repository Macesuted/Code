/**
 * @file 6702.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
using namespace std;

void solve(void) {
    long long A, B, C = 0;
    cin >> A >> B;
    if (!(A & B)) return cout << 1 << endl, void();
    for (int i = 0; i < 32; i++)
        if ((A >> i & 1) && (B >> i & 1)) C |= (long long)1 << i;
    cout << C << endl;
    return;
}

int main() {
    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}