#include <bits/stdc++.h>
using namespace std;

#define bufferSiz 1 << 16
char B[bufferSiz], *_S = B, *_T = B;
#define getchar() (_S == _T && (_T = (_S = B) + fread(B, 1, bufferSiz, stdin), _S == _T) ? EOF : *_S++)

template <typename T>
T read(void) {
    T f = 1, num = 0;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') f = -f;
        c = getchar();
    }
    while (isdigit(c)) {
        num = (num << 3) + (num << 1) + (c ^ 48);
        c = getchar();
    }
    return f * num;
}

#define maxn 1005

int a[maxn];

int main() {
    int T = read<int>();
    while (T--) {
        int n = read<int>();
        int red = 0, blue = 0;
        for (register int i = 1; i <= n; i++) {
            char c = getchar();
            while (c < '0' || c > '9') c = getchar();
            a[i] = c ^ 48;
        }
        for (register int i = 1; i <= n; i++) {
            char c = getchar();
            while (c < '0' || c > '9') c = getchar();
            if ((c ^ 48) < a[i])
                red++;
            else if ((c ^ 48) > a[i])
                blue++;
        }
        if (red > blue)
            puts("RED");
        else if (red < blue)
            puts("BLUE");
        else
            puts("EQUAL");
    }
    return 0;
}