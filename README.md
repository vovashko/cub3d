# Cub3D

## Overview

Cub3D is a 3D graphical project inspired by *Wolfenstein 3D*, developed as part of the 42 curriculum. It features a custom raycasting engine, allowing for real-time rendering of a simple 3D world based on a 2D map.

![Gameplay Preview](./simplescreenrecorder-2025-02-14_09.49.53-ezgif.com-video-to-gif-converter.gif)

## Features

- Raycasting-based 3D rendering
- Custom parser for map validation
- Player movement and rotation
- Wall textures and basic shading
- MLX42 for graphical rendering

## Collaborators

- [**Vova Shkonda**](https://github.com/vovashko) - Worked on the raycaster, graphical rendering, and controls
- [**Paulius Minialga**](https://github.com/PauliusMinialga) - Responsible for parsing and validation

## Installation

Clone the repository and initialize submodules:
```bash
git clone <repo-url>
cd cub3D
git submodule init
git submodule update
```

If you haven't used MLX42 library before please refer to its installment process [here](https://github.com/codam-coding-college/MLX42/tree/7f95e70415705dcc723f94a2696aba84ed3756ad) first. 
Run:
```bash
make
```
to compile the project.

This will generate the `cub3D` executable.

## Usage

Run the program with a valid map file:
```bash
./cub3D maps/good/*.cub
```

In case you want to see the magic of error handling in this project, feel free to execute:
```bash
./map_tester.sh
```


## Map Format

The map should be a `.cub` file with the following format:

- First lines define textures and colors.
- Last section contains the map layout using **1** for walls, **0** for empty space, and **NESW** for player placement.

Example:
```txt
NO ./textures/north.jpg
SO ./textures/south.jpg
WE ./textures/west.jpg
EA ./textures/east.jpg

F 220,100,50
C 255,255,255

111111
1S0001
101001
100001
111111
```

## Controls

- **W / S** - Move forward / backward
- **A / D** - Strafe left / right
- **← / →** - Rotate view left / right
- **ESC** - Quit the game

## Project Details

### File Validation

- Ensures all texture files are present or defaults to RGB colors if missing.
- Requires all necessary configuration parameters, including floor (`F`) and ceiling (`C`) colors in the RGB range [0, 255].
- Validates the presence of a complete and properly formatted map.

### Map Handling

- The map is parsed and stored in a structured format.
- Validation ensures the map is fully enclosed by walls with no invalid characters.
- Handles player starting position based on direction (N, S, W, E).
- Normalizes the map to handle edge cases, preventing players from spawning inside walls.

### Raycasting Engine

- Functional raycasting that renders the map using textures from MLX42.
- Basic wall collision implemented to prevent the player from moving out of bounds.

### Testing

- Integrated a tester as a Git submodule for consistent testing and validation.

## **cub3D**  
*You got cubed.*
