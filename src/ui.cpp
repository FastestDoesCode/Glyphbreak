#include "ui.h"
#include "tm.h"
#include "bn.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <vector>
#include <utility>

std::string cA() { return fg(127, 162, 240); }
std::string cL() { return fg(201, 214, 255); }
std::string cN() { return fg(26, 48, 99); }
std::string cM() { return fg(232, 196, 106); }
std::string cR() { return fg(224, 90, 138); }
std::string cG() { return fg(91, 227, 154); }
std::string cD() { return fg(84, 112, 180); }

std::string uiHex(int v, int w) {
    std::ostringstream o;
    o << std::uppercase << std::hex << std::setw(w) << std::setfill('0') << v;
    return o.str();
}

std::string uiUp(std::string s) {
    for (char& c : s) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return s;
}

std::string uiTrim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}

void uiRule() {
    std::cout << cN();
    for (int i = 0; i < 64; i++) std::cout << "━";
    std::cout << rs() << "\n";
}

void uiHead(const std::string& t, const std::string& s) {
    uiRule();
    std::cout << cA() << "  ▌ " << bd() << cL() << t << rs() << cD() << "  ::  " << s << rs() << "\n";
    uiRule();
}

void uiBar(int tr) {
    int n = tr * 30 / 100;
    std::string c = tr < 40 ? cG() : (tr < 70 ? cM() : cR());
    std::cout << cD() << "  TRACE " << cN() << "[" << c;
    for (int i = 0; i < 30; i++) std::cout << (i < n ? "█" : "░");
    std::cout << cN() << "] " << c << tr << "%" << rs() << "\n";
}

void uiSay(const std::string& c, const std::string& t) {
    std::cout << c << t << rs() << "\n";
}

void uiBanner(const std::string& w) {
    auto ln = bnRender(w);
    int sh[5][3] = {{201, 214, 255}, {170, 190, 250}, {127, 162, 240}, {95, 128, 210}, {60, 92, 170}};
    std::cout << "\n";
    for (int i = 0; i < 5; i++) std::cout << "  " << fg(sh[i][0], sh[i][1], sh[i][2]) << ln[i] << rs() << "\n";
    std::cout << "\n";
}

void uiBoot() {
    std::vector<std::pair<std::string, std::string>> L = {
        {"FASTEST-CORE BIOS v5.0  ::  0x1A3063", ""},
        {"> mnt /sys/gb ...................", "OK"},
        {"> ld  glyph.tbl .................", "OK"},
        {"> ld  cipher.kit ................", "OK"},
        {"> lnk uplink.vs .................", "OK"},
        {"> spoof trace.id ................", "RUN"}
    };
    std::cout << "\n";
    for (auto& p : L) {
        tmType("  " + cA() + p.first, 8);
        if (!p.second.empty()) {
            tmSleep(120);
            std::cout << " " << (p.second == "OK" ? cL() : cM()) << "[ " << p.second << " ]";
        }
        std::cout << rs() << "\n";
        tmSleep(90);
    }
    tmSleep(500);
}
