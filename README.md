# Chip8 Emulator
This repository contains an implementation of a Chip-8 interpreter written in C. It supports the complete set of the standard Chip-8 instructions however doesn't include support for Super Chip-48.

CHIP-8 is an interpreter programming language developed by Joseph Weisbecker in the mid-70s and was initially used on the COSMAC VIP and 
Telmac 1800 8-bit microcomputers to make game programming easier. CHIP-8 programs are run using a CHIP-8 virtual machine.

<div align="center">
    <img src="https://github.com/CheesyFrappe/chip8-emulator/assets/80858788/b919f501-2962-4f3f-b511-07cd64235c0b"/>
    <img src="https://github.com/CheesyFrappe/chip8-emulator/assets/80858788/8c2bdc8a-d998-44d8-9d37-cca0ebcf7790">
</div><br>

[This reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) explains the virtual machine (instruction, registers, stack, memory, display, and keypad) and the opcodes supported.

## Dependencies
 - [Mingw-64 compiler](https://gcc.gnu.org/)
 - [SDL2 library (64-bit)](https://www.libsdl.org/)
 - [A copy of a Chip-8 ROM](https://www.zophar.net/pdroms/chip8/chip-8-games-pack.html)

## Compatibility
Verified compatible with Windows (64-bit).

## Building and Running
To build the project run:
```shell
  git clone https://github.com/CheesyFrappe/chip8-emulator.git
  cd chip8-emulator
  mingw32-make
```
Running from the command line:
 - You need to provide the path to a ROM file as an argument. Check [dependencies](https://github.com/CheesyFrappe/chip8-emulator/new/master?readme=1#dependencies) for the ROM file.
 - So you can start the INVADERS game available in the `bin` directory by:
```shell
  cd bin
  .\main.exe ./INVADERS
```

## Registers

## Keyboard Layout




