*This project has been created as part of the 42 curriculum by mnajem and haabu-sa.*

## Description

cub3D is a first-person maze renderer built with the MiniLibX graphics library.
It parses a `.cub` scene file, validates the map and configuration, then renders
a textured 3D view using ray-casting.

The mandatory program supports:

- North, South, East, and West wall textures.
- Floor and ceiling colors from the scene file.
- Movement with `W`, `A`, `S`, and `D`.
- Camera rotation with the left and right arrow keys.
- Clean shutdown with `ESC` or the window close button.

The bonus build adds:

- Mouse rotation.
- A minimap.
- Doors.
- Sprites.

## Instructions

Compile the mandatory version:

```sh
make
```

Run it with a mandatory map:

```sh
./cub3D maps/mandatory/map.cub
```

Compile the bonus version:

```sh
make bonus
```

Run it with a bonus map:

```sh
./cub3D maps/bonus/bonus.cub
```

Clean build files:

```sh
make clean
```

Remove build files and the executable:

```sh
make fclean
```

Rebuild from scratch:

```sh
make re
```

## Scene Format

A valid mandatory `.cub` file contains four texture paths, two colors, and a
closed map:

```txt
NO ./assets/textures/greystone.xpm
SO ./assets/textures/redbrick.xpm
WE ./assets/textures/bluestone.xpm
EA ./assets/textures/purplestone.xpm
F 40,40,40
C 80,100,120

111111
100001
1000N1
111111
```

Mandatory map characters are `0`, `1`, `N`, `S`, `E`, `W`, and spaces. The map
must be the last section and must be surrounded by walls.

## Resources

- 42 cub3D subject.
- MiniLibX manual pages included in `minilibx-linux/man`.
- Lode Vandevenne's ray-casting tutorial.
- Permadi ray-casting tutorial.
- Linux manual pages for `open`, `close`, `read`, `write`, `malloc`, `free`,
  `printf`, `exit`, and math functions.

AI assistance was used during the learning and research phase of this project.

Specifically, it was used to better understand the core concepts behind **raycasting** and the **DDA (Digital Differential Analyzer) algorithm**, including how rays are cast from the player's position, how grid intersections are calculated, and how wall collisions are detected.

The AI was not used to generate the final project code directly, but rather as a support tool to explain difficult concepts, clarify formulas, and help build a better understanding of the theory needed to implement the project.
