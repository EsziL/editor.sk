
# editor.sk

A code editor for [SkriptLang](github.com/skriptlang/skript) made in C++ with [GTK4](https://www.gtk.org/).

This is a project I am developing to have some fun learning C++, and to maybe even help in developing in another, more obscure programming language I enjoy.

## Run Locally (for contributors)

Releases that are ready will be found in the `releases` tab, but if you would like to contribute, feel free to follow this guide to build the project yourself:

The following steps are for VSCode, but there are tutorials online for Visual Studio as well.

Navigate to a directory you want the project to be (preferably an empty one) using `cd` in the Terminal, then do:
```bash
git clone https://github.com/EsziL/editor.sk.git
```

I will assume you have at least a C/C++ compiler installed, but if you do not, you can follow [this guide](https://www.freecodecamp.org/news/how-to-install-c-and-cpp-compiler-on-windows/). (If you have a recent version of Linux or MacOS, you should have one already)

Check if both of these are recognised as commands, if so, you now have a compiler installed:
```bash
gcc --version
g++ --version
```

### Windows

Open the MSYS2 MSYS app, then type:
```bash
pacman -Syu
```
After that, close the terminal, then open it again. Type:
```bash
pacman -Su
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-gtk4
pacman -S mingw-w64-x86_64-toolchain base-devel
```

Open the command prompt, then type:
```bash
mingw32-make --version
```
If it doesn't throw an unknown command error, then it should be good. (If not, feel free to open an issue)

**After the Linux part, there are a few steps all users are required to do, skip there.**

### MacOS

Install Homebrew if not already installed:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
Install CMake and GTK4:
```bash
brew install cmake
brew install gtk4
```

That should be it, but if not, feel free to create an issue or pull request. (I don't have a Mac to test it on.)

**After the Linux part, there are a few steps all users are required to do, skip there.**

### Linux (Ubuntu)

Execute these commands:
```bash
sudo apt update
sudo apt install cmake
sudo apt install libgtk-4-dev
```

### All Systems (after the former steps)

In VSCode, click the cog icon, then go to settings.

Install the CMake Tools extension if you haven't already.

Search `Cmake: Generator`, and paste in `MinGW Makefiles` in the input box below.

Search `Cmake: Cmake Path` and paste in the CMake executable's file path:
- On Windows, the default location is `C:\msys64\mingw64\bin\cmake.exe`
- On Linux and MacOS, you can find it with `which cmake` in the terminal.

**And that should be it! Go to the `CMakeLists.txt` file, press F1, and type `Cmake: Configure`, then hit enter. From then it should be straightfoward and should configure normally.**

To actually compile and run it, open the Terminal, navigate to the `build` directory using `cd`, then type:

- On Windows:
```bash
mingw32-make
.\editor.sk.exe
```
- On MacOS/Linux:
```bash
make
./editor.sk
```

And that should run it.

**If I missed something, please make an Issue or Pull Request.**

## Authors

- [@EsziL](https://www.github.com/EsziL) - Everything (so far)

