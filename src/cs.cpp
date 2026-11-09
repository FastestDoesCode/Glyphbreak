#include "pz.h"
#include "ui.h"
#include "rn.h"
#include "wd.h"
#include <iostream>
#include <sstream>

static std::string csShift(const std::string& t, int k) {
    k = ((k % 26) + 26) % 26;
    std::string r = t;
    for (char& c : r) if (c >= 'A' && c <= 'Z') c = static_cast<char>('A' + (c - 'A' + k) % 26);
    return r;
}

static std::string csNorm(const std::string& t) {
    std::istringstream in(t);
    std::string w, r;
    while (in >> w) { if (!r.empty()) r += " "; r += w; }
    return r;
}

bool pzCs(St& s, int df) {
    auto ph = wdPhrases();
    std::string p = rnPick(ph);
    int k = rnI(1, 25);
    std::string e = csShift(p, k);
    uiSay(cD(), "  intercepted transmission :: rotational cipher :: depth " + std::to_string(df + 1));
    std::cout << "\n";
    uiSay(cL(), "    " + e);
    std::cout << "\n";
    uiSay(cD(), "  tools :: shift N  (rotate the signal back N, +2 trace)");
    int at = 3;
    while (true) {
        std::string g = gmAsk(s, "use 'shift N' to test a rotation, then type the decoded message.");
        if (s.qt || g == ABORT) return false;
        g = uiUp(g);
        if (g.rfind("SHIFT", 0) == 0) {
            int n = 0;
            try { n = std::stoi(g.substr(5)); } catch (...) { uiSay(cR(), "  bad shift value"); continue; }
            gmTrace(s, 2);
            uiSay(cM(), "  rot-" + std::to_string(n) + " :: " + csShift(e, -n));
            if (gmDead(s)) return false;
            continue;
        }
        if (csNorm(g) == p) { uiSay(cG(), "  transmission decoded"); return true; }
        at--;
        s.er++;
        gmTrace(s, 5);
        uiSay(cR(), "  mismatch :: " + std::to_string(at) + " attempts left");
        if (gmDead(s)) return false;
        if (at == 0) { uiSay(cR(), "  signal lost :: it read " + p); return false; }
    }
}
