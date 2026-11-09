#include "pz.h"
#include "ui.h"
#include "rn.h"
#include "wd.h"
#include <iostream>
#include <algorithm>

static int pwLike(const std::string& a, const std::string& b) {
    int n = 0;
    for (size_t i = 0; i < a.size() && i < b.size(); i++) if (a[i] == b[i]) n++;
    return n;
}

static std::string pwJunk(int n) {
    std::string j = "!@#$%^&*()[]{}<>?/|;:+=-_~";
    std::string r;
    for (int i = 0; i < n; i++) r += j[rnI(0, static_cast<int>(j.size()) - 1)];
    return r;
}

bool pzPw(St& s, int df) {
    int ln = std::min(8, 5 + df / 2 + (df >= 4 ? 1 : 0));
    auto ws = wdLen(ln);
    std::shuffle(ws.begin(), ws.end(), rnG());
    int nw = std::min(static_cast<int>(ws.size()), 8 + df);
    std::vector<std::string> pk(ws.begin(), ws.begin() + nw);
    std::string tg = pk[rnI(0, nw - 1)];
    uiSay(cD(), "  memory dump :: " + std::to_string(nw) + " candidate keys :: length " + std::to_string(ln));
    std::cout << "\n";
    int ad = 0x1A30 + rnI(0, 0x300);
    for (int i = 0; i < nw; i++) {
        int a = rnI(0, 6);
        std::cout << "  " << cN() << "0x" << uiHex(ad + i * 16, 4) << "  " << cD() << pwJunk(a) << cL() << pk[i]
                  << cD() << pwJunk(16 - a) << rs() << "\n";
    }
    std::cout << "\n";
    int at = 4;
    while (true) {
        std::cout << cD() << "  attempts " << cA();
        for (int i = 0; i < at; i++) std::cout << "■ ";
        std::cout << rs() << "\n";
        std::string g = gmAsk(s, "type one of the keys from the dump. likeness = letters in the right position.");
        if (s.qt || g == ABORT) return false;
        g = uiUp(g);
        if (std::find(pk.begin(), pk.end(), g) == pk.end()) { uiSay(cR(), "  entry not found in dump"); continue; }
        if (g == tg) { uiSay(cG(), "  > " + g + " :: key accepted"); return true; }
        at--;
        s.er++;
        gmTrace(s, 4);
        uiSay(cM(), "  > " + g + " :: likeness " + std::to_string(pwLike(g, tg)) + "/" + std::to_string(ln));
        if (gmDead(s)) return false;
        if (at == 0) { uiSay(cR(), "  terminal lockout :: key was " + tg); return false; }
    }
}
