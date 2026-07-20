# Monster Arena (C RPG)

A terminal-based RPG written in C as a learning project focused on pointers, structs, game architecture, and software design.

## Features

- Choose one of three player classes
- Battle one of three enemy types
- Turn-based combat
- Attack
- Heal
- Block
- Unlockable skills
- Skill Point (SP) progression
- Mana-based skill casting
- Basic enemy AI
- Experience system
- Player leveling
- Spend stat points to upgrade character attributes
- Fight multiple enemies in succession
- Restart game after defeat

## Build & Run

Compile:

```bash
gcc main.c -o monster_arena
```

Run:

```bash
./monster_arena
```

Windows:

```bash
monster_arena.exe
```

## Project Goals

This project was created to strengthen understanding of:

- Structs
- Pointers
- Function decomposition
- Program architecture
- State management
- Combat systems
- Memory layout
- Git & GitHub workflow

## Technologies

- Language: C
- Compiler: GCC (or any C99-compatible compiler)

## Roadmap

### v1.0.x

- [x] Character selection
- [x] Enemy selection
- [x] Turn-based combat
- [x] Attack
- [x] Heal
- [x] Block
- [x] Basic enemy AI
- [x] Arena loop

### v1.1.0

- [x] Experience system
- [x] Leveling
- [x] Stat progression

### v1.2.0

- [x] Skills
- [x] Mana costs
- [x] Skill progression
- [x] Skill unlocking

### v1.3.0

- [ ] Additional skill effects
- [ ] Status effects
- [ ] Enemy skills
- [ ] New combat abilities

### Future Ideas

- Inventory
- Equipment
- Status effects
- Critical hits
- Save/Load system
- Boss enemies

## Project Structure

```
main.c
README.md
CHANGELOG.md
```

## Current Architecture

The project is currently organized into several gameplay systems:

- Character system
- Combat system
- Experience and leveling system
- Stat progression system
- Skill progression system

Although the project is written in procedural C, it is organized into modular gameplay systems using structs and function decomposition. The primary goal is to practice software architecture, pointers, and state management while building a larger-scale terminal RPG.

## Current Release

**v1.2.0**
