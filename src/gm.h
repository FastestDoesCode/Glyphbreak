#pragma once
#include <string>
struct St {
    int tr = 0;
    int sc = 0;
    int er = 0;
    bool qt = false;
};
const std::string ABORT = "\x01";
std::string gmAsk(St& s, const std::string& hint);
void gmTrace(St& s, int a);
bool gmDead(const St& s);
void gmRun();
