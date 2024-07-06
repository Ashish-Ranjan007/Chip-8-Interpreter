# Chip-8 Interpreter

Welcome to the Chip8 Emulator project! This project emulates the Chip8 system, a simple, interpreted programming language used on some old computers and gaming consoles. The emulator is built using C++ and SDL2.

## Project Overview

This Chip8 emulator project aims to accurately emulate the Chip8 system, allowing you to play classic Chip8 games. It handles the Chip8 instruction set, graphics, sound, and input handling.

## Features

-   Emulates the Chip8 CPU and instruction set
-   Renders graphics using SDL2
-   Handles input using SDL2
-   Plays sound effects using SDL2_mixer

## Demos

### Breakout

![Breakout example GIF](/demos/breakout.gif)

### Space Invaders

![Space Invaders example GIF](/demos/space-invaders.gif)

## Requirements

-   Visual Studio (2019 or later recommended)
-   SDL2 and SDL2_mixer libraries (included in the lib directory)

## Installation

### Building from source with Visual Studio

#### Step 1: Clone the repository to your local machine

```bash
git clone https://github.com/Ashish-Ranjan007/Chip-8-Interpreter.git
cd chip8-emulator
```

#### Step 2: Set Up SDL2 and SDL2_mixer

The `/lib` directory in the root folder contains the necessary SDL2 and SDL2_mixer files. Ensure these are properly configured in your Visual Studio project.

#### Step 3. Open the project in Visual Studio

Click on the `Chip-8 Interpreter.sln` file to open it in Visual Studio.

#### Step 4: Configure include and library directories

1. Include Directories
    - Go to `Project -> Properties -> VC++ Directories -> Include Directories`.
    - Add the path to the lib/SDL2/include and lib/SDL2_mixer/include directories.
2. Library Directories
    - Go to `Project -> Properties -> VC++ Directories -> Library Directories`
    - Add the path to the lib/SDL2/lib and lib/SDL2_mixer/lib directories.
3. Additional Directories
    - Go to Project -> Properties -> Linker -> Input -> Additional Dependencies
    - Add `SDL2.lib;`, `SDL2main.lib;`, and `SDL2_mixer.lib;`.
4. Setup Command Line Arguments
    - Go to `Project -> Properties -> Debugging -> Command Arguments`.
    - Provide `<path_to_rom> <display_scale_factor> <clock_speed>`

#### Step 5: Build and Run

-   Build the project by clicking on Build -> Build Solution.
-   Run the emulator by clicking on Debug -> Start Debugging.

## Usage

To start the emulator, you need to provide a Chip8 ROM file, a scale factor, and a clock speed as command-line arguments. Here is the usage syntax:

```bash
Usage: <path_to_rom> <display_scale_factor> <clock_speed>
ROM: Path to a Chip8 ROM file.
Scale: Scale the size of the screen to fit your needs.
Clock Speed: Clock speed of CPU in Hz (usually 500Hz).
```

Example

```bash
"C:\User\MyName\Documents\chip8-roms\space-invaders.ch8" 10 500
```

## Controls

The Chip8 keypad is mapped to your keyboard as follows:

```mathematics
1 2 3 4        1 2 3 4
Q W E R   =>   Q W E R
A S D F        A S D F
Z X C V        Z X C V
```

## ROMs

Chip8 ROM files are not included in this repository. You can find Chip8 ROMs online.

## Acknowledgements

-   http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
-   https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
-   https://austinmorlan.com/posts/chip8_emulator/
