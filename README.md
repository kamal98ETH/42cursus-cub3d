<div align="center">

# 🎮 cub3D

**A Wolfenstein 3D-inspired raycasting engine built in C**

*42 School — Common Core Project*

[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-orange?style=flat-square)](https://github.com/42Paris/minilibx-linux)
[![Norminette](https://img.shields.io/badge/Norm-OK-brightgreen?style=flat-square)](https://github.com/42School/norminette)
[![License](https://img.shields.io/badge/License-42-lightgrey?style=flat-square)](https://www.42.fr/)

</div>

---

## 📖 About

**cub3D** is a raycasting-based 3D game engine written entirely in C, inspired by the iconic *Wolfenstein 3D* (1992). The project is a deep dive into the mathematics of ray casting, real-time rendering, texture mapping, and game loop architecture — all implemented from scratch without any game engine or rendering library beyond the MiniLibX windowing API.

The goal is to produce a first-person 3D perspective from a 2D map, simulating a 3D environment using angular ray projection — the same technique used in early 3D games before true polygon rendering became standard.

> **This is a collaborative project.** Built in a two-person team as part of the 42 School curriculum. See [contributions](#-contributions) for a detailed breakdown.

---

## ✨ Features

### Mandatory
- **3D Raycasting Engine** — First-person 3D perspective rendered in real time from a 2D grid map
- **Directional Textures** — Distinct wall textures for North, South, East, and West faces
- **Configurable Scene** — Custom `.cub` scene files define textures, floor/ceiling colors, and map layout
- **WASD Movement** — Smooth player movement with wall collision detection
- **Arrow Key Rotation** — Camera rotation with left/right arrow keys
- **Clean Exit** — `ESC` key and window close button both gracefully exit the engine

### Bonus
- **Doors** — Interactive doors (`D` tile) that open/close using the `E` key, with wall-aligned placement validation
- **Minimap** — Real-time overhead minimap rendered in the corner, centered on the player with fade-out ray lines
- **Mouse Look** — Smooth horizontal camera rotation driven by mouse movement
- **Animated Enemy** — A chasing enemy (`X` tile) that tracks the player through the map, rendered as a 2D sprite using billboard projection
- **Death Screen** — Triggered when the enemy reaches the player

---

## 🛠️ Technical Implementation

### Raycasting Algorithm

The engine casts one ray per screen column across a configurable **field of view (60°)**. For each ray, two sub-casts are performed:

- **Vertical cast** — Steps along X-axis grid boundaries to detect east/west wall hits
- **Horizontal cast** — Steps along Y-axis grid boundaries to detect north/south wall hits

The shorter of the two distances wins, and the hit direction determines which texture face to sample. A **fish-eye correction** is applied by multiplying the raw distance by `cos(player_angle - ray_angle)` before computing wall height.

```
wall_height = (TILE * HEIGHT) / (ray.dist * cos(player_dir - ray_angle))
```

### Wall Rendering

Each screen column is filled top-to-bottom:
1. **Ceiling** — flat color sampled from the `.cub` config
2. **Wall slice** — texture column computed from hit offset within the tile
3. **Floor** — flat color sampled from the `.cub` config

### Minimap

The minimap is rendered into a separate MiniLibX image buffer (`200×150 px`) and placed in the bottom-left corner of the window. It is centered on the player position and recalculates every frame. Ray lines drawn on the minimap use a **fade factor** (`0.95` per pixel step) for a visual trail effect. Doors are highlighted in gold (`0xFBC21A`).

### Door System

Doors are stored as a **linked list** of `t_door` nodes, initialized from `D` tiles in the map. Each door tracks its grid position and state (`OPEN` / `CLOSED`). Placement is validated: a door must be flanked by walls on either its horizontal or vertical axis — floating doors are rejected at parse time. When the player presses `E`, the nearest door within range toggles. The player and enemy can only pass through an open door.

### Movement & Collision

Player movement is resolved with trigonometric direction vectors. Collision is handled per-axis: the engine checks the target X and Y positions independently so the player slides along walls rather than stopping dead. The same system applies to enemy pathfinding.

---

## 🗺️ Map Format (`.cub`)

Scene files follow a strict format. Elements must appear before the map grid.

```
NO ./textures/stone/north.xpm   # North wall texture
SO ./textures/stone/south.xpm   # South wall texture
WE ./textures/stone/west.xpm    # West wall texture
EA ./textures/stone/east.xpm    # East wall texture
DR ./textures/doors/door.xpm    # Door (closed) texture  [bonus]
DF ./textures/doors/gate.xpm    # Door (open) texture    [bonus]
X  ./textures/enemy/enemy.xpm   # Enemy sprite           [bonus]

F 207,175,123                   # Floor color (R,G,B)
C 156,184,250                   # Ceiling color (R,G,B)

11111111111
10000000001
1000D000001     # D = door
100000N0001     # N/S/E/W = player spawn + direction
10000000X01     # X = enemy spawn
11111111111
```

| Character | Meaning |
|-----------|---------|
| `1` | Wall |
| `0` | Empty floor |
| `N` `S` `E` `W` | Player start position & facing direction |
| `D` | Interactive door *(bonus)* |
| `X` | Enemy spawn *(bonus)* |
| ` ` (space) | Out-of-bounds (must be surrounded by walls) |

The map must be fully enclosed by walls. Any gap causes a parse error.

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move forward / strafe left / move backward / strafe right |
| `←` `→` | Rotate camera left / right |
| Mouse | Horizontal camera look *(bonus)* |
| `E` | Interact with door *(bonus)* |
| `ESC` | Quit |

---

## 🚀 Getting Started

### Prerequisites

- **Linux** (tested on Ubuntu / 42 machines)
- `cc` (clang or gcc)
- MiniLibX dependencies: `libxext-dev`, `libx11-dev`

```bash
sudo apt-get install libxext-dev libx11-dev
```

### Build

```bash
# Clone the repository
git clone https://github.com/kamal98ETH/42cursus-cub3d.git
cd 42cursus-cub3d

# Build mandatory version
make

# Build bonus version (doors, minimap, mouse look, enemy)
make bonus
```

### Run

```bash
# Mandatory
./cub3D maps/mandatory.cub

# Bonus — try the maze map with doors and an enemy
./cub3D maps/maze_bonus.cub

# Or explore the jungle
./cub3D maps/jungle_bonus.cub
```

> **Note:** The binary name is always `cub3D` regardless of which version was compiled. Running `make` after `make bonus` (or vice versa) will recompile.

### Clean

```bash
make clean    # Remove object files
make fclean   # Remove objects + binary
make re       # Full recompile
```

---

## 📁 Project Structure

```
42cursus-cub3d/
├── mandatory/srcs/         # Mandatory source files
│   ├── main.c              # Entry point & MLX init
│   ├── raycasting.c        # Ray casting core (vertical/horizontal DDA)
│   ├── circle_halves.c     # Ray half-stepping helpers (right/left/upper/lower)
│   ├── rendering.c         # Wall drawing & frame composition
│   ├── movement.c          # Player movement & collision
│   ├── hooks.c             # Keyboard event hooks
│   ├── parser.c            # .cub file parsing
│   ├── fetch.c             # Texture & color fetching
│   ├── map.c               # Map validation & formatting
│   ├── texture.c           # Texture sampling
│   ├── color.c             # Color utilities
│   └── ...
├── bonus/srcs/             # Bonus source files (superset of mandatory)
│   ├── door_bonus.c        # Door linked-list logic & interaction
│   ├── door_utils_bonus.c  # Door helpers (coordinate lookup, list ops)
│   ├── minimap_bonus.c     # Overhead minimap rendering
│   ├── movement_bonus.c    # Movement + mouse look + enemy pathfinding
│   ├── death_bonus.c       # Death screen & enemy sprite
│   └── ...
├── maps/                   # Sample scene files
├── textures/               # XPM texture assets (stone, jungle, doors, enemy...)
├── libft/                  # Custom C standard library (ft_*)
└── Makefile
```

---

## 👥 Contributions

This project was built as a **two-person team**:

### 🙋 My contributions — **[@kez-zoub](https://github.com/kamal98ETH)**
- **Raycasting engine** — Designed and implemented the full DDA-based ray casting algorithm, including vertical/horizontal grid stepping and fish-eye correction
- **Wall rendering** — Column-by-column wall projection, ceiling/floor flat color fill, and the wall height formula
- **Player movement & collision** — WASD controls with per-axis collision sliding
- **Minimap** — Real-time overhead minimap with player-centered viewport and fading ray lines
- **Door system** — Interactive door rendering, linked-list state tracking, open/close interaction (`E` key), collision passthrough logic, and parse-time placement validation
- **Door traversal** — Ensuring both player and enemy correctly interact with open/closed door states during movement

### 🤝 Teammate — **[@laoubaid](https://github.com/laoubaid)**
- Scene file parser (`.cub` format)
- Texture loading and XPM sampling
- Floor/ceiling color parsing and rendering
- Enemy sprite (billboard projection, distance scaling)
- Death screen logic
- General map validation and error handling

---

## 📚 Resources & References

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — Foundational raycasting math
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d) — Historical reference
- [42 MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) — Windowing and image API

---

<div align="center">

*Made with ☕ and trigonometry at [1337 School](https://1337.ma/) (42 Network)*

</div>
