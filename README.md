# VS Code template project for CMake / C++ development

This template uses CMake, doctest, fltk, sfml as a ready-to-use VS Code project.

## System requirements:

Windows:
---

CMake: [Install windows latest release](https://cmake.org/download/)

MinGW __MSVCRT__ Compiler (x86_64 posix seh gcc msvcrt): [Install windows latest release](https://winlibs.com/)

(_SFML is not compatible with the UCRT version of the MinGW compiler!_)

@see https://github.com/SFML/SFML/issues/2289


macOS:
---

Install xcode command line tools via Terminal app:

```
xcode-select --install
``` 

CMake: [Install macOS latest release](https://cmake.org/download/)

Add symlinks to make CMake available in Terminal, VS Code, etc.:

```
sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install
```

Linux (Ubuntu):
---

Install packages via Terminal:

```
$ sudo apt install g++ cmake
```