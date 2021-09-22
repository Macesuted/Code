#include "testlib.h"

void eraseSpace(std::string& str) {
    while (!str.empty() && isspace(str.back())) str.pop_back();
    return;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int line = 0;
    while (!ans.seekEof() && !ouf.seekEof()) {
        line++;
        std::string a, o;
        a = ans.readLine(), o = ouf.readLine();
        eraseSpace(a), eraseSpace(o);
        int len = std::min(a.size(), o.size());
        for (int column = 0; column < len; column++)
            if (a[column] != o[column])
                quitf(_wa, "On line %d column %d, read %c, expected %c.", line, column + 1, o[column], a[column]);
        if (a.size() < o.size()) quitf(_wa, "Too long on line %d.", line);
        if (a.size() > o.size()) quitf(_wa, "Too short on line %d.", line);
    }
    if (ans.seekEof())
        while (!ouf.seekEof()) {
            std::string str;
            str = ouf.readLine();
            eraseSpace(str);
            if (!str.empty()) quit(_wa, "User output longer than standard answer.");
        }
    if (ouf.seekEof())
        while (!ans.seekEof()) {
            std::string str;
            str = ans.readLine();
            eraseSpace(str);
            if (!str.empty()) quit(_wa, "Standard answer longer than user output.");
        }
    quit(_ok, "Accepted!");
}