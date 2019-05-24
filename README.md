<p align="center"><img src="title.png" alt="title"></p>

Reproduction of Nene Sakura's game "Nene Quest" from "New Game!!" (2nd
season, episode 3) written in C++ with the SFML library.

# Preview

## Original

![](samples/screenshot01.png)

## nene-quest

![](samples/screenshot02.png)

# Compilation & Execution

We currently don't have any release yet so you have to compile the
project by yourself.

* download SFML (2.5+): https://www.sfml-dev.org/download.php
* or install it (on Debian or Ubuntu) with: `apt-get install libsfml-dev`

* CMake:

    ```sh
    cd nenequest/
    cmake -B build . # -DCMAKE_BUILD_TYPE=Debug
    make -C build
    ./build/NeneQuest
    ```

* IDE: https://www.sfml-dev.org/tutorials/2.5/#getting-started

* On Windows, don't forget to put the .dll files in the right
  folder. These files are located in `<SFML path>/bin`.

* In Visual Studio:
  + Make a new project/solution
  + Clone the git repository inside the project with `git clone
    https://github.com/echofee/nene-quest.git`
  + Include the `nenequest/headers` folder in your IDE's "Additional
    Include Directories" (in Visual Studio: `Project > [project name]
    properties... > C/C++ > General`)
  + Left-click on the "Show all files" button on the "Solution
    Explorer" on the right corner
  + Right-click on the `src` and `headers` folders then select
    "Include in the project"
  + You can navigate in the files with the "Solutions and folders"
    button in the right corner
  + Now, you should be able to compile the project

* In Eclipse for C/C++
	+ clone project with `git clone https://github.com/engboris/nene-quest.git` 
	+ In eclipse File -> Import -> C/C++ -> Existing Code as Makefile Project with MinGW GCC toolchain -> select folder nenequest of repo (might need to add MinGW folder to $PATH)
	+ Go in project properties -> C/C++ Build -> Settings
	+ GCC C++ Compiler -> Preprocessor -> Defined symbols,  add the following:  
		+ SFML_STATIC  
		+ \_\_GX_EXPERIMENTAL_CXX_0X\_\_  
		+ _cplusplus=201103L
	+ GCC C++ Compiler -> Miscellaneaous, add flags
		+ -std=c++11 : for c++ 11
		+ -U__STRICT_ANSI__ : if this flag is not here, for whatever reason we can't use the math.h constants
	+ GCC C++ Compiler -> include, add 
		+ (SFML-Location)/include
		+ headers folder
	+ MinGW C++ Linker -> Libraries, add (SFML-Location)/lib to search path
	+ MinGW C++ Linker -> Libraries, add the following libraires (in this order, remove -d from SFML libs for release version):
		+ sfml-graphics-s-d
		+ freetype
		+ sfml-window-s-d
		+ opengl32
		+ gdi32
		+  sfml-audio-s-d
		+ flac
		+ vorbisenc
		+ vorbisfile
		+ vorbis
		+ ogg
		+ openal32
		+ sfml-network-s-d
		+ ws2_32
		+ sfml-system-s-d
		+ winmm

Please format the code before committing, with

``` sh
cd nenequest/
clang-format -i headers/**/*.hpp src/**/*.cpp
```
