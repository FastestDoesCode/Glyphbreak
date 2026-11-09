#include "pz.h"
#include "ui.h"
#include "rn.h"
#include "wd.h"
#include <iostream>
#include <algorithm>

static void hxRef() {
    std::cout << "\n";
    for (int i = 0; i < 26; i++) {
        std::cout << cN() << "  " << uiHex(65 + i, 2) << cD() << "=" << cL() << static_cast<char>(65 + i) << rs();
        if (i % 9 == 8) std::cout << "\n";
    }
    std::cout << "\n\n";
}

bool pzHx(St& s, int df) {
    int ln = std::min(8, 5 + df / 2);
    auto ws = wdLen(ln);
    std::string w = rnPick(ws);
    uiSay(cD(), "  raw sector bytes :: decode to ascii");
    std::cout << "\n    ";
    for (char c : w) std::cout << cN() << "0x" << cL() << uiHex(static_cast<unsigned char>(c), 2) << " ";
    std::cout << rs() << "\n\n";
    uiSay(cD(), "  tools :: ref  (ascii table, +5 trace)");
    int at = 3;
    while (true) {
        std::string g = gmAsk(s, "convert each hex byte to its letter. 0x41 is A, 0x5A is Z.");
        if (s.qt || g == ABORT) return false;
        g = uiUp(g);
        if (g == "REF") { gmTrace(s, 5); hxRef(); if (gmDead(s)) return false; continue; }
        if (g == w) { uiSay(cG(), "  sector decoded :: " + w); return true; }
        at--;
        s.er++;
        gmTrace(s, 5);
        uiSay(cR(), "  corrupt read :: " + std::to_string(at) + " attempts left");
        if (gmDead(s)) return false;
        if (at == 0) { uiSay(cR(), "  sector wiped :: it was " + w); return false; }
    }
}
