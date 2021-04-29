# RT

générer des images de synthèse selon la méthode du Ray-Tracing. Ces images de synthèse représentent une scène, vue d’une position et d’un angle spécifiques, définie par des objets géométriques simples, entiers ou partiels, et disposant d’un système d’éclairage.

## Installing
####  install SDL2.<br>
- Linux :
```
$ sudo apt install libsdl2-2.0-0 libsdl2-gfx-1.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-net-2.0-0 libsdl2-ttf-2.0-0
```
- Mac _(takes time)_ :
```
$ brew install sdl2 sdl2_image sdl2_ttf
```
Then run :
```
$ make
```
## Compiling

Use [make](https://en.wikipedia.org/wiki/Makefile) for compiling all files.

When you have already installed SDL2 library you can use this simple rules:
- **make**: Compile all.
- **make clean**: Delete temporary files.
- **make fclean**: Delete executable Rt file & libft.
- **make re**: It's rules - **make fclean** & **make** in one.

## Usage
The programm takes a scene written in yaml as an argument. Multiple **scenes** are directly available in the directory "./correction/" .
```
$ usage: ./rt correction/(chose a file .yaml)

### Basics
- 4 objects : sphere, plane, cylinder, cone
- Multiple light sources
- Phong shading
- Shadows
- Translations & rotations (camera & objects)

# ![multispot](./imgs/multi.bmp)

### Limited objects
- Each object can be cut on 3 different axes
- These 3 axes can be either the world axes or the object axes
- Translations & rotations are still working with cut objects

### Textures
- Each object can have a texture put on it
- Variable scale & position

# ![textures](imgs/room.bmp)

### Refraction / Reflection

- Both have adjustable percentages
- Implementation of Snell-Descartes's indice of refraction
- A semi-transparent object has its colors projected in its shadow
- Checkerboard / rainbow

# ![refraction](imgs/ref.bmp)

### Visual effects
- Sepia
- blur

# ![refraction](imgs/sepia.bmp)

### Lights
- Colored lights
- multi lights
- ambient %

### Optimization
- Multi-threading
