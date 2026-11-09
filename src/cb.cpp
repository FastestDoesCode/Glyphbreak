#include "pz.h"
#include "ui.h"
#include "rn.h"
#include <iostream>
#include <algorithm>
#include <cctype>

bool pzCb(St& s, int df) {
    int n = df >= 3 ? 5 : 4;
    std::string d = "0123456789";
    std::shuffle(d.begin(), d.end(), rnG());
    std::string code = d.substr(0, n);
    int tries = n == 5 ? 10 : 8;
    uiSay(cD(), "  vault lock :: " + std::to_string(n) + " unique digits :: " + std::to_string(tries) + " probes");
    uiSay(cD(), "  locked = right digit, right slot :: drifting = right digit, wrong slot");
    std::cout << "\n";
    while (tries > 0) {
        std::string g = gmAsk(s, "enter " + std::to_string(n) + " different digits, e.g. 0123.");
        if (s.qt || g == ABORT) return false;
        bool ok = static_cast<int>(g.size()) == n;
        for (char c : g) if (!std::isdigit(static_cast<unsigned char>(c))) ok = false;
        std::string u = g;
        std::sort(u.begin(), u.end());
        if (ok && std::adjacent_find(u.begin(), u.end()) != u.end()) ok = false;
        if (!ok) { uiSay(cR(), "  invalid probe"); continue; }
        int lk = 0, dr = 0;
        for (int i = 0; i < n; i++) {
            if (g[i] == code[i]) lk++;
            else if (code.find(g[i]) != std::string::npos) dr++;
        }
        if (lk == n) { uiSay(cG(), "  > " + g + " :: vault open"); return true; }
        tries--;
        s.er++;
        gmTrace(s, 2);
        uiSay(cM(), "  > " + g + " :: locked " + std::to_string(lk) + " :: drifting " + std::to_string(dr) +
                    cD() + "   [" + std::to_string(tries) + " left]");
        if (gmDead(s)) return false;
    }
    uiSay(cR(), "  vault sealed :: code was " + code);
    return false;
}
