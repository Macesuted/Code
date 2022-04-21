#include <bits/stdc++.h>
using namespace std;

#ifdef MACESUTED

bool mem1;

#endif

#define Class ClassName
#define Method MethodName

class Class {
   private:
   public:
    void Method(void) {}
};

#ifdef MACESUTED

Class _;

bool mem2;

int main() {
    ios::sync_with_stdio(false);
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    _.Method();

    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
    return 0;
}

#endif