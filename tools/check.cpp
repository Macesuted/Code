/**
 * @file check.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-11
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      An efficient testlib checker that ignores end-of-line blank characters and end-of-text blank lines.
 *
 */

#include "testlib.h"

bool checkLine(InStream& in) {
    while (!in.eoln())
        if (!isBlanks(in.readChar())) return false;
    return in.readChar(), true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int line = 0;
    while (!ans.eof() && !ouf.eof()) {
        line++;
        int column = 0;
        while (!ans.eof() && !ouf.eof() && !isEoln(ans.curChar()) && !isEoln(ouf.curChar())) {
            column++;
            if (ans.curChar() != ouf.curChar()) break;
            ans.readChar(), ouf.readChar();
        }
        char charAns = ans.curChar(), charOuf = ouf.curChar();
        bool eolnAns = checkLine(ans), eolnOuf = checkLine(ouf);
        if (!eolnAns && !eolnOuf) quitf(_wa, "On line %d column %d, read '%c', expected '%c'.", line, column, charOuf, charAns);
        if (!eolnAns && eolnOuf) quitf(_wa, "Too short on line %d.", line);
        if (eolnAns && !eolnOuf) quitf(_wa, "Too long on line %d.", line);
    }
    if (ans.eof() && !ouf.seekEof()) quit(_wa, "User output longer than standard answer.");
    if (ouf.eof() && !ans.seekEof()) quit(_wa, "Standard answer longer than user output.");
    quit(_ok, "Accepted!");
}