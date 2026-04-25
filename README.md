# Unreal Engine 5.2 - 2D Arcade Collection

This repository contains my **first semester exam project** for college, developed in **Unreal Engine 5.2** using **C++**.

The project is a collection of **five different 2D arcade-style games** built inside the same Unreal project as a way to practice gameplay programming, game logic, collision systems, score systems, and actor behaviour in C++.

## Included Games

- **Pong**
- **Breakout**
- **Mario**
- **Peggle**
- **Invasion**

---

## Overview

This project was created as part of my **first semester exam** and focuses on implementing multiple classic-inspired 2D games in Unreal Engine.

The main goal of the project was to help me practice:

- Unreal Engine C++ gameplay classes
- 2D gameplay systems using Paper2D-style components
- collision and overlap handling
- player input and movement
- enemy behaviour
- score and game mode logic
- spawning and projectile systems
- simple level-based arcade gameplay

Rather than building one large game, I used this project to explore different game mechanics across multiple genres and gameplay styles.

---

## Games Included

### 1. Pong
A classic Pong-style game with:

- player-controlled paddle
- AI-controlled paddle
- moving ball with collision logic
- player and AI scoring
- win condition and game over transition

Key classes include:
- `APlayerPongBat`
- `AAIPongBat`
- `APongBall`
- `APongGameModeBase`

---

### 2. Breakout
A brick-breaking arcade game with:

- player-controlled bat
- bouncing ball
- destructible bricks
- collision-driven gameplay loop

Key classes include:
- `ABreakOutBat`
- `ABreakOutBalll`
- `ABreakBrick`

---

### 3. Mario
A side-scrolling platform-style prototype inspired by Mario, including:

- player character
- collectible coins
- spike hazards
- enemy character logic
- score tracking through a dedicated game mode

Key classes include:
- `AMario`
- `ACoin`
- `ASpike`
- `ADumbGoombah`
- `AMarioGameMode`

---

### 4. Peggle
A Peggle-inspired prototype with:

- rotatable launcher
- spawned ball projectile
- physics-based movement
- destructible target blocks

Key classes include:
- `APeggleBallLauncher`
- `APeggleBall`
- `APeggleBlock`

---

### 5. Invasion
A 2D space shooter prototype featuring:

- player spaceship
- enemy spaceship
- projectile firing
- meteorites / hazards
- score tracking through a separate game mode

Key classes include:
- `APlayerShip`
- `AEnemyShip`
- `AFireAmmo`
- `AEnemyFireAmmo`
- `AMeteorite`
- `AInvasionGameMode`

---

## Technical Focus

This project helped me practice the following Unreal Engine systems:

- **C++ gameplay programming**
- **custom actors and pawns**
- **collision and overlap events**
- **PaperSprite / Flipbook components**
- **physics-based interactions**
- **game mode and score management**
- **basic AI behaviour**
- **timers and delayed destruction**
- **spawning gameplay actors**
- **level-specific gameplay rules**

---

## Tech Stack

- **Engine:** Unreal Engine 5.2
- **Language:** C++
- **Framework:** Unreal Engine Gameplay Framework
- **Style:** 2D arcade / prototype collection

---

## My Role

I developed this project as part of my **first semester exam**.

My work included:

- designing and implementing the gameplay logic
- creating multiple game systems in C++
- setting up actor classes, movement, collisions, and score systems
- building several classic-inspired 2D gameplay prototypes inside one project

---

## What I Learned

This project was an important early step in my Unreal Engine journey because it gave me practical experience with several different gameplay styles in one codebase.

It helped me understand how to:

- structure Unreal gameplay classes
- build reusable gameplay logic
- handle player and enemy interactions
- create different rules for different game modes
- prototype multiple mechanics quickly inside the same project

---

## Project Status

**Completed**  
Created as a **first semester college exam project** and used as an early learning milestone in Unreal Engine 5.2.

---

## Repository Structure

The project contains source files for multiple mini-games, including systems such as:

- player-controlled pawns
- enemy actors
- projectiles
- score/game mode systems
- hazards and collectibles
- physics-based gameplay objects

---

## Future Improvements

Possible future improvements for this project could include:

- separate polished menus for each mini-game
- UI improvements for score and feedback
- better game over / restart flows
- improved visuals and audio polish
- stronger code organization per game module
- packaging each mini-game as a standalone prototype

---

## Author

**George Bolias**  
Game Programmer / Unreal Engine Developer

- Portfolio: [https://www.georgebolias.com/](https://www.georgebolias.com/)
- LinkedIn: [https://www.linkedin.com/in/georgebolias/](https://www.linkedin.com/in/georgebolias/)
- GitHub: [https://github.com/GamingMystae](https://github.com/GamingMystae)
