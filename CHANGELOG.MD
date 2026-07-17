# Changelog

All notable changes to this project will be documented in this file.

The format is inspired by Keep a Changelog and the project follows Semantic Versioning.

---

## [v1.0.1] - 2026-07-17

### Added

- Functional blocking mechanic.
- Temporary combat state (`isblocking`) for both player and enemy.
- Ability to exit combat by running away.
- Arena loop allowing the player to fight multiple enemies after winning.

### Changed

- Refactored game initialization into dedicated functions:
  - `initialize_game()`
  - `player_class()`
  - `enemy_select()`
- Replaced runtime class initialization with global constant class templates (`PLAYERCLASSES` and `ENEMYCLASSES`).
- Simplified combat loop by introducing a local combat state (`isfighting`).
- Updated damage system to account for blocking.
- Improved overall project organization and code readability.

### Fixed

- Blocking now correctly prevents the next incoming attack.
- Running away now exits combat immediately instead of allowing the enemy to take another turn.
- Character combat state is now initialized correctly when selecting a class.

---

## [v1.0.0] - 2026-07-16

### Added

- Initial playable prototype.
- Three playable classes:
  - Warrior
  - Archer
  - Mage
- Three enemy classes:
  - Goblin
  - Orc
  - Troll
- Turn-based combat system.
- Basic enemy AI.
- Attack action.
- Heal action.
- Character selection.
- Enemy selection.
- Health management system.
- Death detection.
- Class stat system using structs.

### Prototype Notes

- Block action was a placeholder and had no gameplay effect.
- Combat ended after a single battle.
- Running away was not fully implemented.
