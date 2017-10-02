![title](title.png)

Reproduction of Nene Sakura's game "Nene Quest" from "New Game!!" (2nd
season, episode 3) written in C++ with the SFML library.

# Preview

## Original

![screenshot01](samples/screenshot01.png)

## Our project

![screenshot02](samples/screenshot02.png)

Still in developement as you can see.

# Compilation & Execution

We don't have any release yet so you can only compile the project by
yourself for the moment.

* Install [SFML 2.4.2](https://www.sfml-dev.org/download/sfml/2.4.2/)

## [Meson](http://mesonbuild.com/)

```sh

    # configuring the source
    mkdir build && cd build
    meson .. # --backend=vs2010
             # --prefix /path-to-install-dir

    # building (without an IDE)
    ninja
    ninja install
```

See [Getting Meson](http://mesonbuild.com/Getting-meson.html) and
[Running Meson](http://mesonbuild.com/Running-Meson.html) for more
information.

## Manually

* Link SFML to your IDE :
  + Windows
    - [Visual
      Studio](https://www.sfml-dev.org/tutorials/2.4/start-vc.php)
    - [Code Blocks](https://www.sfml-dev.org/tutorials/2.4/start-cb.php)
  + [Linux](https://www.sfml-dev.org/tutorials/2.4/start-linux.php)
  + [Mac OS
    (Xcode)](https://www.sfml-dev.org/tutorials/2.4/start-osx.php)
  + [Compilation with
    CMake](https://www.sfml-dev.org/tutorials/2.4/compile-with-cmake.php)

* Don't forget to put the `.dll` files in the right folder. These files
  are located in `$(your SFML directory)/bin`.

* Make a new project and add our source/header files (located in
  `nenequest/src` and `nenequest/headers`) manually.

You can ask for help in issues if you're having some troubles.

# Collaborations

You can also contribute in :
- C++ programming (you don't necessarily have to be experimented but
  you should be used to programming with at least one imperative
  language)
- 2D Graphics reproduction
- Maybe more if you have any ideas...
