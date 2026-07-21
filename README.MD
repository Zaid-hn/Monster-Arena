# Monster Arena (C RPG)

A terminal-based RPG written in C as a learning project focused on pointers, structs, game architecture, and software design.

## Features

- Choose one of three player classes
- Battle one of three enemy types
- Turn-based combat
- Attack
- Heal
- Block
- Unlockable spells
- Spell Point (SP) progression
- Mana-based spell casting
- Experience system
- Player leveling
- Stat point allocation
- Individual XP rewards for each enemy
- Fight multiple enemies in succession
- Restart game after defeat
- Basic enemy AI

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

- [x] Spell system
- [x] Mana costs
- [x] Spell progression
- [x] Spell unlocking

### v1.3.0

- [x] Enemy data definitions
- [x] Per-enemy XP rewards
- [x] Refactored enemy architecture

### Planned

- [ ] Status effects
- [ ] Spell effects
- [ ] Enemy spell casting
- [ ] Additional combat abilities

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

The project is organized into several gameplay systems:

- Character system
- Combat system
- Spell system
- Experience and leveling system
- Stat progression system
- Enemy data system

The architecture separates immutable game definitions from mutable runtime state:

- `CharacterClass` — Base class definitions
- `EnemyData` — Enemy-specific immutable data
- `Character` — Runtime combat state
- `Player` / `Enemy` — Gameplay entities
- `Spell` / `PlayerSpell` — Spell definitions and player progression

Although the project is written in procedural C, it is organized into modular gameplay systems using structs and function decomposition. The primary goal is to practice software architecture, pointers, and state management while building a larger-scale terminal RPG.

## Current Release

**v1.3.0**
