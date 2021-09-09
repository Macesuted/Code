#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        if ((a & 1) + (b & 1) + (c & 1) + (d & 1) <= 1)
            puts("Yes");
        else if (a && b && c) {
            a--, b--, c--, d += 3;
            if ((a & 1) + (b & 1) + (c & 1) + (d & 1) <= 1)
                puts("Yes");
            else
                puts("No");
        } else
            puts("No");
    }
    return 0;
}