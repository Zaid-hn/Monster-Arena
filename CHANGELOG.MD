# Changelog

All notable changes to this project will be documented in this file.

The format is inspired by Keep a Changelog and the project follows Semantic Versioning.

---

## [v1.3.0] - 2026-07-21

### Added

- Enemy data system (`EnemyData`).
- Individual XP rewards for each enemy type.
- Enemy type definitions using immutable data tables.

### Changed

- Renamed the Skill system to the Spell system throughout the project.
- Refactored enemy initialization to separate immutable enemy definitions from runtime enemy state.
- Character initialization now returns the selected class index, allowing enemy data and character data to remain synchronized.
- Enemy instances now reference immutable `EnemyData` instead of storing duplicated XP values.
- Improved project architecture by separating:
  - Runtime character state (`Character`)
  - Character templates (`CharacterClass`)
  - Enemy-specific data (`EnemyData`)

### Fixed

- Eliminated duplicated XP values stored directly in enemy instances.
- Improved consistency between enemy class selection and XP reward assignment.

---

## [v1.2.0] - 2026-07-20

### Added

- Skill progression system.
- Three unlockable skills:
  - Fireball
  - Icicle
  - Poison Ivy
- Skill Point (SP) rewards on level up.
- Skill purchasing system.
- Combat skill menu.
- Mana cost system for skills.
- Player skill inventory using `PlayerSkill`.
- Global immutable skill database (`ALL_SKILLS`).

### Changed

- Refactored skill-related logic into dedicated functions:
  - `initialize_skills()`
  - `display_locked_skills()`
  - `display_player_skills()`
  - `choose_skill()`
  - `select_skill()`
  - `buy_skill()`
  - `cast_skill()`
  - `use_skill()`
- Extended the combat menu with a dedicated Skills action.
- Character initialization now includes skill initialization.
- Character model now distinguishes between current mana and maximum mana.
- Improved combat architecture by separating skill selection, purchasing, and casting responsibilities.

### Fixed

- Prevented crashes caused by invalid skill selections.
- Added validation when purchasing and casting skills.
- Prevented invalid pointer dereferences when skill selection fails.
- Improved handling of insufficient mana during skill usage.

---

## [v1.1.0] - 2026-07-20

### Added

- Experience (XP) reward system after defeating enemies.
- Player leveling system.
- Stat point rewards on level up.
- Character stat progression.
- Stat allocation system allowing players to upgrade:
  - Health
  - Mana
  - Attack Power

### Changed

- Refactored combat flow into smaller dedicated functions:
  - `player_action()`
  - `enemy_action()`
  - `player_attack()`
  - `enemy_attack()`
  - `character_attack()`
- Moved experience rewards outside of the combat loop to separate combat resolution from game progression.
- Refactored stat upgrade logic into dedicated helper functions:
  - `select_stat()`
  - `spend_stat_points()`
- Improved separation of responsibilities throughout the combat and progression systems.
- Improved overall project organization and readability.

### Fixed

- Prevented crashes caused by invalid stat selections during stat allocation.
- Improved combat flow after victories and progression handling.

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
