<p align="center"><img src="title.png" alt="title"></p>

Reproduction of Nene Sakura's game "Nene Quest" from "New Game!!" (2nd
season, episode 3) written in C++ with the SFML library.

# Preview

## Original

![screenshot](samples/screenshot01.png)

## nene-quest

![screenshot](samples/screenshot02.png)

# Compilation & Execution

We currently don't have any release yet so you have to compile the
project by yourself.

Follow the [SFML tutorial][sfml-tutorial]; or our instructions.

[sfml-tutorial]: https://www.sfml-dev.org/tutorials/2.5/#getting-started

## Windows

### CMake Instructions

1. Download a C++ compiler, either [MinGW-w64][mingw-w64] (preferred),
   [Clang][clang], or Visual C++, and add the compiler path to the
   `PATH` environment variable
   (e.g. `C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin`).
2. Download [CMake][cmake]. During the installation, set the "set
   `PATH` variable" checkbox.
3. Download a [SFML (2.5+)][sfml-dl] build that matches your compiler,
   and extract it. We'll call that path `<SFML path>`
   (e.g. `C:\Users\User\Downloads\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1`).
4. Clone or download NeneQuest, open Windows Powershell, and go to
   NeneQuest's directory. Chose the CMake Generator for your build
   system or favorite IDE (e.g. `MinGW Makefiles`,
   `Eclipse CDT4 - MinGW Makefiles`, `Visual Studio 16 2019`).
   Supported generators can be listed with `cmake -G`.
   ```powershell
   cd nenequest
   cmake -B build -DCMAKE_PREFIX_PATH="<SFML path>" -G "<Generator>" .

   # If "MinGW Makefiles" was the generator
   mingw32-make.exe -C build
   ```
5. Copy the files from `<SFML path>\bin` to `build`.
6. Execute `.\build\NeneQuest.exe`.

[mingw-w64]: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download
[clang]: http://releases.llvm.org/download.html
[cmake]: https://cmake.org/download/
[sfml-dl]: https://www.sfml-dev.org/download.php

### Visual Studio

Follow the [SFML tutorial][sfml-tutorial-vc]; or

1. Make a new project/solution
2. Clone the git repository inside the project with
   `git clone https://github.com/echoffee/nene-quest.git`
3. Include the `nenequest/headers` folder in your IDE's "Additional
   Include Directories" (in Visual Studio: `Project > [project name]
   properties... > C/C++ > General`)
4. Left-click on the "Show all files" button on the "Solution
   Explorer" on the right corner
5. Right-click on the `src` and `headers` folders then select "Include
   in the project"
6. You can navigate in the files with the "Solutions and folders"
   button in the right corner
7. Now, you should be able to compile the project

[sfml-tutorial-vc]: https://www.sfml-dev.org/tutorials/2.5/start-vc.php

### Eclipse C/C++

1. Clone project with `git clone https://github.com/echoffee/nene-quest.git`
2. In eclipse File -> Import -> C/C++ -> Existing Code as Makefile
   Project with MinGW GCC toolchain -> select folder nenequest of repo
   (might need to add MinGW folder to $PATH)
3. Go in project properties -> C/C++ Build -> Settings
4. GCC C++ Compiler -> Preprocessor -> Defined symbols, add the following:
   + `SFML_STATIC`
   + `__GX_EXPERIMENTAL_CXX_0X__`
   + `_cplusplus=201103L`
5. GCC C++ Compiler -> Miscellaneaous, add flags
   + `-std=c++11` : for C++11
   + `-U__STRICT_ANSI__` : if this flag is not here, for whatever reason
     we can't use the `math.h` constants
6. GCC C++ Compiler -> include, add
   + `<SFML path>/include`
   + headers folder
7. MinGW C++ Linker -> Libraries, add `<SFML path>/lib` to search path
8. MinGW C++ Linker -> Libraries, add the following libraires (in this
   order, remove `-d` from SFML libs for release version):
   ```
   sfml-graphics-s-d freetype sfml-window-s-d opengl32 gdi32
   sfml-audio-s-d flac vorbisenc vorbisfile vorbis ogg openal32
   sfml-network-s-d ws2_32 sfml-system-s-d winmm
   ```

## Linux

1. Install CMake and SFML development files
   ```sh
   apt-get install cmake libsfml-dev # Ubuntu, Debian
   pacman -S cmake sfml # Arch Linux
   ```
2. Compile and execute:
   ```sh
   cd nenequest/
   cmake -B build . # -DCMAKE_BUILD_TYPE=Debug
   make -C build
   ./build/NeneQuest
   ```

# Contributing

Please format the code before committing, with

``` sh
cd nenequest/
clang-format -i headers/**/*.hpp src/**/*.cpp
```
