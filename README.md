# GLYPHBREAK

A terminal intrusion game. Six nodes stand between you and the core, and every one is locked by a different puzzle. Each mistake raises your trace; hit 100% and the connection is severed.

```
 ████ █     █   █ ████  █   █ ████  ████  █████  ███  █   █
█     █      █ █  █   █ █   █ █   █ █   █ █     █   █ █  █
█  ██ █       █   ████  █████ ████  ████  ████  █████ ███
█   █ █       █   █     █   █ █   █ █  █  █     █   █ █  █
 ████ █████   █   █     █   █ ████  █   █ █████ █   █ █   █
```

## Locks

| Code | Lock | How to break it |
|------|------|-----------------|
| pw | memory dump | Pick the key from the dump. Each wrong guess tells you how many letters sit in the right position. |
| cs | rot cipher | The message is rotated through the alphabet. Use `shift N` to test rotations, then type the plain text. |
| hx | hex sector | Turn the hex bytes back into letters. `ref` shows an ASCII table at a cost. |
| cb | vault | Find the digit code. Locked means right digit, right slot; drifting means right digit, wrong slot. |
| xo | key mixer | XOR the byte with the key. Answer in hex or 8-bit binary. |
| sq | port knock | Memorise the port sequence before it vanishes, then replay it. |

Breaching a node cools the trace a little. Failing one adds trace and reroutes you to a fresh lock on the same node.

## Commands

`help` shows a hint for the current lock, `trace` shows the trace bar, `abort` gives up the current lock, and `quit` returns to the menu.

## Build

**Windows**

1. Install a C++ compiler. Open PowerShell and run:

   ```
   winget install -e --id BrechtSanders.WinLibs.POSIX.UCRT
   ```

2. Close and reopen PowerShell so it finds the new compiler.
3. Download this repo (green **Code** button, then **Download ZIP**) and unzip it.
4. Double-click `build.bat`. It ends with `Built glyphbreak.exe`.
5. Double-click `glyphbreak.exe` to play. It looks best in Windows Terminal.

If `build.bat` says no compiler was found, reopen PowerShell or restart your PC and try again. It also works with Visual Studio's compiler when run from a Developer Command Prompt.

**Linux and macOS**

```
make
./glyphbreak
```

**CMake (any platform)**

```
cmake -B build
cmake --build build
```

Needs a C++17 compiler and a terminal with colour support. Windows Terminal works best.

## License

MIT, copyright (c) 2026 Fastest. See [LICENSE](LICENSE).
