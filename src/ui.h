#pragma once
#include <string>
#include "tm.h"
std::string cA();
std::string cL();
std::string cN();
std::string cM();
std::string cR();
std::string cG();
std::string cD();
std::string uiHex(int v, int w);
std::string uiUp(std::string s);
std::string uiTrim(const std::string& s);
void uiRule();
void uiHead(const std::string& t, const std::string& s);
void uiBar(int tr);
void uiSay(const std::string& c, const std::string& t);
void uiBanner(const std::string& w);
void uiBoot();
