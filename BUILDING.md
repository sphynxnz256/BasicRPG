# Building ClickerGame

The game uses SFML 2.6.2. CMake downloads and builds it automatically the first time you configure the project (this needs an internet connection and takes a few minutes). After that it's cached in the `build/` folder.

## Requirements

- [Build Tools for Visual Studio 2022](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022) with the **Desktop development with C++** workload
- [CMake](https://cmake.org/download/) 3.20 or newer
- [Git](https://git-scm.com/) (CMake uses it to download SFML)
- [VS Code](https://code.visualstudio.com/) with the **C/C++** and **CMake Tools** extensions (VS Code will offer to install these when you open the folder)

## In VS Code

1. Open this folder in VS Code.
2. When CMake Tools asks for a kit, pick **Visual Studio Build Tools 2022 Release - amd64**.
3. Press **F5** to build and run the game under the debugger.

## From the command line

```
cmake -S . -B build
cmake --build build --config Debug
build\Debug\ClickerGame.exe
```

SFML is linked statically, so there are no SFML DLLs. The build copies the contents of `assets/` and `openal32.dll` (used by SFML's audio) next to the executable, so it can be run directly.
