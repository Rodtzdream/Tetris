# Tetris

This project is a puzzle game that combines elements of a puzzle and strategy game. It is based on the classic version of Tetris.

## Description

Tetris is a 2D puzzle video game that combines elements of puzzle and strategy. The player's task is to arrange falling pieces in such a way as to fill rows across the entire width of the playing field, causing them to disappear and make room for new pieces.

The game features a graphical interface and sound effects created using the SFML library. Additionally, a user record-keeping system has been implemented, allowing players to compete with friends for the best score.

## Tools and Technologies

- **C++**: The programming language used to implement the game's code.
- **SFML (Simple and Fast Multimedia Library)**: The library used for creating graphics and sound effects.
- **CMake**: The tool used to automate the project's build process.

## Installation and Running

### Installation via .exe

To install and run the game, download the appropriate installer from the following path:

- [Tetris_x86.exe](https://github.com/Rodtzdream/Tetris/tree/main/bin)

After completing the installation, you can start the game from the shortcut created on the desktop or from the "Start" menu.

### Building with CMake

To build the project's source code using CMake, follow these steps:

1. **Install dependencies:**

Before starting the build process, ensure that all necessary dependencies are installed on your system. Use the following commands to install the SFML dependencies on Linux:

#### Ubuntu / Debian

```bash
sudo apt-get install libfreetype6-dev libx11-dev libxrandr-dev libudev-dev libgl1-mesa-dev libflac-dev libogg-dev libvorbis-dev libvorbisenc2 libvorbisfile3 libopenal-dev libpthread-stubs0-dev xorg-dev
```

#### Fedora

```bash
sudo dnf install freetype-devel libX11-devel libXrandr-devel libudev-devel mesa-libGL-devel flac-devel libogg-devel libvorbis-devel openal-soft-devel xorg-x11-proto-devel
```

#### Arch Linux

```bash
sudo pacman -S freetype2 libx11 libxrandr libudev mesa flac libogg libvorbis openal xorg-server-devel
```

#### openSUSE

```bash
sudo zypper install freetype-devel libX11-devel libXrandr-devel libudev-devel Mesa-libGL-devel flac-devel libogg-devel libvorbis-devel openal-soft-devel xorg-x11-devel
```

2. **Open a terminal and navigate to the root directory of the project.1**

3. **Create a build directory:**

```bash
mkdir build && cd build
```

4. **Configure the build with CMake:**

```bash
cmake ..
```

> Note: To build the project correctly, you need CMake version 3.27 or higher.

5. **Execute the build:**

```bash
cmake --build .
```

6. **After a successful build, you can run the game from the created output directory:** `build/bin`

## Game screenshots

### Main menu

![Головне меню гри](https://imgur.com/wMNzctY.png)

### Gameplay

![Процес гри](https://imgur.com/qBzcNyd.png)

## Author

**Yurii Oliinyk**

- Email: <olijnikura@gmail.com>
- Telegram: [@rodtzdream](https://t.me/rodtzdream)

## Support

If you have any questions or suggestions regarding this project, please feel free to contact me.
