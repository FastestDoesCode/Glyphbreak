#pragma once
#include <string>
void tmInit();
void tmSleep(int ms);
void tmClear();
void tmType(const std::string& s, int ms);
std::string tmLine(bool& eof);
std::string fg(int r, int g, int b);
std::string rs();
std::string bd();
