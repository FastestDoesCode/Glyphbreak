#include "tm.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

static int tmSpeed = 1;

void tmInit() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD m = 0;
    if (GetConsoleMode(h, &m)) SetConsoleMode(h, m | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
    if (std::getenv("GB_FAST")) tmSpeed = 0;
}

void tmSleep(int ms) {
    if (tmSpeed && ms > 0) std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void tmClear() {
    std::cout << "\x1b[2J\x1b[H" << std::flush;
}

void tmType(const std::string& s, int ms) {
    bool esc = false;
    for (char c : s) {
        std::cout << c;
        if (c == '\x1b') esc = true;
        else if (esc) { if (c == 'm') esc = false; }
        else if ((static_cast<unsigned char>(c) & 0xC0) != 0x80) { std::cout << std::flush; tmSleep(ms); }
    }
    std::cout << std::flush;
}

std::string tmLine(bool& eof) {
    std::cout << std::flush;
    std::string l;
    if (!std::getline(std::cin, l)) { eof = true; return ""; }
    eof = false;
    if (!l.empty() && l.back() == '\r') l.pop_back();
    return l;
}

std::string fg(int r, int g, int b) {
    return "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::string rs() { return "\x1b[0m"; }
std::string bd() { return "\x1b[1m"; }
