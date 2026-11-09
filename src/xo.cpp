#include "pz.h"
#include "ui.h"
#include "rn.h"
#include <iostream>
#include <bitset>

static int xoParse(std::string g) {
    if (g.rfind("0X", 0) == 0) g = g.substr(2);
    if (g.empty()) return -1;
    bool bin = g.size() == 8;
    for (char c : g) if (c != '0' && c != '1') bin = false;
    try {
        size_t p = 0;
        int v = std::stoi(g, &p, bin ? 2 : 16);
        if (p != g.size() || v < 0 || v > 255) return -1;
        return v;
    } catch (...) { return -1; }
}

bool pzXo(St& s, int df) {
    int rounds = std::min(4, 2 + df / 2);
    int at = 3;
    uiSay(cD(), "  key mixer :: xor the byte with the key :: " + std::to_string(rounds) + " rounds");
    for (int r = 0; r < rounds; r++) {
        int a = rnI(0, 255), k = rnI(1, 255);
        std::cout << "\n";
        std::cout << "  " << cD() << "byte " << cL() << "0x" << uiHex(a, 2) << cN() << "  " << std::bitset<8>(a) << rs() << "\n";
        std::cout << "  " << cD() << "key  " << cL() << "0x" << uiHex(k, 2) << cN() << "  " << std::bitset<8>(k) << rs() << "\n";
        while (true) {
            std::string g = gmAsk(s, "answer in hex (3F) or 8-bit binary (00111111). xor: bits that differ become 1.");
            if (s.qt || g == ABORT) return false;
            int v = xoParse(uiUp(g));
            if (v < 0) { uiSay(cR(), "  unreadable value"); continue; }
            if (v == (a ^ k)) { uiSay(cG(), "  round " + std::to_string(r + 1) + " :: mixed"); break; }
            at--;
            s.er++;
            gmTrace(s, 5);
            uiSay(cR(), "  wrong mix :: " + std::to_string(at) + " errors left");
            if (gmDead(s)) return false;
            if (at == 0) { uiSay(cR(), "  mixer jammed :: it was 0x" + uiHex(a ^ k, 2)); return false; }
        }
    }
    return true;
}
