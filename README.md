# Corewar

A fearsome arena where programs compete to be the last one alive, and tries to corrupt its enemies by overwritting them. 
Will yours be the last one standing ?

![corewar preview](/.github/corewar.gif)

Contestant are written in a simplified assembly language, compiled to bytecode and executed by a virtual machine 
(the arena).

##### ASM

The `asm` binary is in charge of parsing your contestant.s, and compiling it to bytecode. 

We provide `wtc.s` as an example for a contestant's source code.

##### VM

The `corewar` binary, the virtual machine, takes a list of 1 to 4 contestants, and make them compete against each other.

The 4 programs are run in parallel, and each instruction takes a variable amount of cycles to complete, so choose your
strategy wisely !

By default the `corewar` binary will simulate the battle internally and only tell you the result. 
Use `-v` to get a nice ncurses display like above. You can then run the battle at the speed you want, pause it, and even
do step-by step.

#### Build

* `make` to build the project. This will compile the `asm` and `corewar` binaries.
* `asm wtc.s` to compile the example contestant to bytecode.
* `corewar -v wtc.cor` to start the battle with only this one contestant.

#### Origin

This project was inspired by the 1984 [core war](https://en.wikipedia.org/wiki/Core_War) game.

#### Final grade

Corewar was originally a school project, and was graded **118/100**.
