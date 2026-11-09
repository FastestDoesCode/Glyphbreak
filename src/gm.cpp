#include "gm.h"
#include "pz.h"
#include "ui.h"
#include "tm.h"
#include "rn.h"
#include "wd.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

static const std::string SAVE = "gb.sav";

std::string gmAsk(St& s, const std::string& hint) {
    while (true) {
        std::cout << "\n" << cA() << "  fs@gb" << cD() << ":~$ " << rs();
        bool eof = false;
        std::string l = uiTrim(tmLine(eof));
        if (eof) { s.qt = true; return ""; }
        std::string u = uiUp(l);
        if (u == "QUIT" || u == "EXIT") { s.qt = true; return ""; }
        if (u == "ABORT") return ABORT;
        if (u == "HELP") {
            uiSay(cD(), "  " + hint);
            uiSay(cD(), "  commands :: help  trace  abort  quit");
            continue;
        }
        if (u == "TRACE") { uiBar(s.tr); continue; }
        return l;
    }
}

void gmTrace(St& s, int a) {
    s.tr = std::max(0, std::min(100, s.tr + a));
}

bool gmDead(const St& s) { return s.tr >= 100; }

static int gmBest() {
    std::ifstream f(SAVE);
    int b = 0;
    if (f >> b) return b;
    return 0;
}

static void gmSaveBest(int v) {
    std::ofstream f(SAVE);
    f << v;
}

static bool gmWait(St& s) {
    std::cout << "\n" << cD() << "  [ enter ]" << rs();
    bool eof = false;
    tmLine(eof);
    if (eof) s.qt = true;
    return !s.qt;
}

static bool gmPuzzle(int t, St& s, int df) {
    switch (t) {
        case 0: return pzPw(s, df);
        case 1: return pzCs(s, df);
        case 2: return pzHx(s, df);
        case 3: return pzCb(s, df);
        case 4: return pzXo(s, df);
        default: return pzSq(s, df);
    }
}

static void gmEnd(St& s, bool won) {
    tmClear();
    int fin = std::max(0, s.sc + (won ? (100 - s.tr) * 5 : 0) - s.er * 10);
    int best = gmBest();
    if (won) {
        uiBanner("GLYPHBREAK");
        tmType("  " + cG() + "ROOT ACCESS GRANTED :: THE CORE IS YOURS" + rs() + "\n", 25);
    } else {
        std::cout << "\n";
        tmType("  " + cR() + "TRACE COMPLETE :: CONNECTION SEVERED" + rs() + "\n", 25);
    }
    std::cout << "\n";
    uiSay(cD(), "  score   " + cL() + std::to_string(fin));
    uiSay(cD(), "  errors  " + cL() + std::to_string(s.er));
    uiSay(cD(), "  trace   " + cL() + std::to_string(s.tr) + "%");
    if (fin > best) { gmSaveBest(fin); uiSay(cM(), "  new record"); }
    else uiSay(cD(), "  record  " + cL() + std::to_string(best));
    gmWait(s);
}

static void gmPlay() {
    St s;
    std::vector<int> ty = {0, 1, 2, 3, 4, 5};
    std::shuffle(ty.begin(), ty.end(), rnG());
    ty.resize(5);
    ty.push_back(0);
    auto nm = wdNodes();
    for (int i = 0; i < 6; i++) {
        while (true) {
            tmClear();
            uiHead("NODE 0x" + uiHex(0x1A30 + i * 0x10, 4), nm[i] + "  [" + std::to_string(i + 1) + "/6]");
            uiBar(s.tr);
            uiSay(cD(), "  score " + cL() + std::to_string(s.sc));
            std::cout << "\n";
            bool ok = gmPuzzle(ty[i], s, i);
            if (s.qt) return;
            if (ok) {
                s.sc += 100 * (i + 1);
                gmTrace(s, -6);
                uiSay(cG(), "\n  node breached :: trace cooling");
                if (!gmWait(s)) return;
                break;
            }
            gmTrace(s, 12);
            if (gmDead(s)) { gmEnd(s, false); return; }
            uiSay(cR(), "\n  intrusion detected :: rerouting through a new gate");
            if (!gmWait(s)) return;
        }
    }
    gmEnd(s, true);
}

static void gmHow(St& s) {
    tmClear();
    uiHead("MANUAL", "how to break the core");
    std::vector<std::string> L = {
        "  six nodes stand between you and the core. each one is locked by a puzzle.",
        "  every mistake raises your TRACE. at 100% you are caught and the run ends.",
        "  breaching a node cools the trace a little. failing one reroutes you to a new lock.",
        "",
        "  locks you will meet:",
        "    memory dump   pick the key, use likeness to narrow it down",
        "    rot cipher    rotate the letters until the message reads",
        "    hex sector    turn hex bytes back into letters",
        "    vault         find the digit code from locked and drifting hints",
        "    key mixer     xor two bytes",
        "    port knock    remember a sequence before it vanishes",
        "",
        "  type help at any prompt for a hint. abort gives up the current lock."
    };
    for (auto& l : L) uiSay(cL(), l);
    gmWait(s);
}

void gmRun() {
    tmInit();
    rnSeed();
    tmClear();
    uiBoot();
    while (true) {
        tmClear();
        uiBanner("GLYPHBREAK");
        uiSay(cD(), "  a terminal intrusion game  ::  (c) 2026 Fastest");
        uiSay(cD(), "  record " + cL() + std::to_string(gmBest()));
        std::cout << "\n";
        uiSay(cA(), "  [1] " + cL() + "jack in");
        uiSay(cA(), "  [2] " + cL() + "manual");
        uiSay(cA(), "  [3] " + cL() + "disconnect");
        St m;
        std::string c = gmAsk(m, "pick 1, 2 or 3.");
        if (m.qt || c == "3") break;
        if (c == "1") gmPlay();
        else if (c == "2") gmHow(m);
        if (m.qt) break;
    }
    std::cout << rs() << "\n";
}
