#include "wd.h"

std::vector<std::string> wdLen(int n) {
    if (n <= 5) return {"CACHE", "PROXY", "TOKEN", "LOGIC", "SHELL", "CRYPT", "VIRUS", "QUERY", "PATCH", "STACK",
                        "PIXEL", "DEBUG", "MACRO", "BYTES", "FRAME", "GHOST", "ROUTE", "PROBE", "LAYER", "SPOOF"};
    if (n == 6) return {"CIPHER", "KERNEL", "SOCKET", "BINARY", "BUFFER", "CURSOR", "DAEMON", "ROUTER", "SCRIPT", "MATRIX",
                        "VECTOR", "SIGNAL", "PACKET", "SERVER", "ACCESS", "SYSTEM", "BREACH", "GLITCH", "ENCODE", "DECODE",
                        "MEMORY", "THREAD"};
    if (n == 7) return {"NETWORK", "PAYLOAD", "COMPILE", "PROGRAM", "CONSOLE", "DECRYPT", "ENCRYPT", "RUNTIME", "BOOTKEY",
                        "SPOOFED", "KEYLOGS", "BITMASK", "HEXDUMP", "SEGMENT", "PROCESS", "STORAGE", "SANDBOX", "RECURSE",
                        "PHANTOM", "ARCHIVE", "CHANNEL", "CIRCUIT", "QUANTUM"};
    return {"FIREWALL", "TERMINAL", "BACKDOOR", "PASSWORD", "OVERFLOW", "PROTOCOL", "KEYSTONE", "DATABASE", "REGISTRY",
            "BYTECODE", "HARDWARE", "SOFTWARE", "CHECKSUM", "BOOTLOAD", "DEADLOCK", "OBSIDIAN", "RUNECODE", "GLYPHSET",
            "CLUSTERS", "PIPELINE"};
}

std::vector<std::string> wdPhrases() {
    return {"THE ANCIENT CODE NEVER SLEEPS", "ACCESS IS A STATE OF MIND", "EVERY LOCK HAS A WHISPER",
            "THE CORE REMEMBERS ALL", "SPEED IS THE ONLY KEY", "SILENCE THE WATCHERS", "FOLLOW THE BROKEN GLYPHS",
            "NOTHING HERE IS RANDOM", "THE MAINFRAME DREAMS IN HEX", "FAST HANDS LEAVE NO TRACE"};
}

std::vector<std::string> wdNodes() {
    return {"ATLAS-GATE", "VEIL-RELAY", "ORACLE-9", "CRYPT-WARD", "ECHO-SPIRE", "THE CORE"};
}
