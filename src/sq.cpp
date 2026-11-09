#include "pz.h"
#include "ui.h"
#include "rn.h"
#include "tm.h"
#include <iostream>
#include <sstream>
#include <vector>

bool pzSq(St& s, int df) {
    std::vector<int> ports = {21, 22, 23, 25, 53, 80, 110, 143, 443, 1337, 3306, 5432, 6379, 8080, 27017, 31337};
    int n = 4 + df;
    std::vector<int> q;
    for (int i = 0; i < n; i++) q.push_back(rnPick(ports));
    int at = 2;
    while (true) {
        uiSay(cD(), "  port knock :: memorise the sequence :: it will vanish");
        std::cout << "\n    ";
        tmSleep(600);
        for (int p : q) { std::cout << cL() << p << "  " << std::flush; tmSleep(550); }
        std::cout << rs() << "\n";
        tmSleep(1200 + 250 * n);
        tmClear();
        uiSay(cD(), "  sequence purged :: replay the knock");
        std::string g = gmAsk(s, "type the ports in order, separated by spaces.");
        if (s.qt || g == ABORT) return false;
        std::istringstream in(g);
        std::vector<int> r;
        std::string t;
        while (in >> t) { try { r.push_back(std::stoi(t)); } catch (...) { r.push_back(-1); } }
        if (r == q) { uiSay(cG(), "  knock accepted :: port open"); return true; }
        at--;
        s.er++;
        gmTrace(s, 6);
        if (gmDead(s)) return false;
        if (at == 0) {
            std::string sq;
            for (int p : q) sq += std::to_string(p) + " ";
            uiSay(cR(), "  knock rejected :: it was " + sq);
            return false;
        }
        uiSay(cR(), "  knock rejected :: one more replay");
    }
}
