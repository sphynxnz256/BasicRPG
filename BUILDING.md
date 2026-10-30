# Building BasicRPG

The game uses SFML 2.6.0 (bundled in `external/SFML/`), which is built for the MSVC compiler on 64-bit Windows.

## Requirements

- [Build Tools for Visual Studio 2022](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022) with the **Desktop development with C++** workload
- [CMake](https://cmake.org/download/) 3.20 or newer
- [VS Code](https://code.visualstudio.com/) with the **C/C++** and **CMake Tools** extensions (VS Code will offer to install these when you open the folder)

## In VS Code

1. Open this folder in VS Code.
2. When CMake Tools asks for a kit, pick **Visual Studio Build Tools 2022 Release - amd64**.
3. Press **F5** to build and run the game under the debugger.

## From the command line

```
cmake -S . -B build
cmake --build build --config Debug
build\Debug\BasicRPG.exe
```

The build copies the SFML DLLs and the contents of `assets/` next to the executable, so it can be run directly.
