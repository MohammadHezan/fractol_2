*This project has been created as part of the 42 curriculum by mhaizan.*

# Fract'ol

A graphical fractal exploration program built with the MiniLibX library.

## Description

Fract'ol is a 42 school project that introduces the concept of fractals and computer graphics programming. The program renders beautiful mathematical fractals in real-time, allowing users to explore their infinite complexity through zooming and navigation.

### Supported Fractals

| Fractal | Description |
|---------|-------------|
| **Mandelbrot** | The classic Mandelbrot set, defined by the iterative formula z = z² + c |
| **Julia** | A family of fractals that use a fixed complex constant, creating diverse patterns |
| **Burning Ship** | A variant of the Mandelbrot set using absolute values, creating a ship-like shape |

### Features

- Real-time fractal rendering at 800x800 resolution
- Smooth mouse-centered zooming for infinite exploration
- Arrow key navigation to pan across the fractal plane
- Adjustable iteration depth for detail control
- 5 color schemes (Rainbow, Fire, Ice, Purple, Green)
- Dynamic Julia set parameter modification

## Instructions

### Prerequisites

- Linux operating system
- GCC compiler
- X11 development libraries (`libxext-dev`, `libx11-dev`)
- Make

### Installation

```bash
# Clone the repository
git clone <repository-url>
cd eval_fractol

# Compile the project (MiniLibX will be cloned automatically)
make
```

### Usage

```bash
# Mandelbrot set
./fractol mandelbrot

# Julia set (requires real and imaginary parts of the constant)
./fractol julia <real> <imaginary>
# Example: ./fractol julia -0.7 0.27015

# Burning Ship fractal
./fractol burning_ship
```

### Controls

| Key/Action | Function |
|------------|----------|
| `Arrow Keys` | Pan/Navigate the fractal |
| `Mouse Scroll Up` | Zoom in (centered on cursor) |
| `Mouse Scroll Down` | Zoom out (centered on cursor) |
| `+` / `=` | Increase iteration count |
| `-` / `_` | Decrease iteration count |
| `C` | Cycle through color schemes |
| `J` / `L` | Adjust Julia real parameter (Julia set only) |
| `I` / `M` | Adjust Julia imaginary parameter (Julia set only) |
| `ESC` | Close window and exit cleanly |
| `Window X button` | Close window and exit cleanly |

### Makefile Rules

| Rule | Description |
|------|-------------|
| `make` | Compile the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and executable |
| `make re` | Recompile the project from scratch |

## Resources

### Documentation & References

- [Mandelbrot Set - Wikipedia](https://en.wikipedia.org/wiki/Mandelbrot_set) - Mathematical background and history
- [Julia Set - Wikipedia](https://en.wikipedia.org/wiki/Julia_set) - Understanding Julia set fractals
- [Burning Ship Fractal - Wikipedia](https://en.wikipedia.org/wiki/Burning_Ship_fractal) - The Burning Ship variant
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Graphics library reference
- [Complex Number Tutorial](https://mathworld.wolfram.com/ComplexNumber.html) - Understanding complex arithmetic

### AI Usage Disclosure

AI tools were **not** used in the development of this project. All code, including fractal algorithms, color schemes, event handling, and rendering logic, was written manually based on mathematical concepts and the MiniLibX documentation.

## Technical Details

- **Graphics Library**: MiniLibX (42 Paris) with image rendering
- **Language**: C (compliant with 42 Norm)
- **No Global Variables**: All state is managed through structs passed by reference
- **Makefile**: Does not relink (recompiles only modified files)
- **Rendering**: Pixel-by-pixel iteration with escape-time algorithm
- **Color Mapping**: Smooth gradient color schemes based on iteration count
- **Window Management**: Smooth handling of focus changes, minimizing, and clean exit via ESC or window close button

## Bonus Features

All bonus features have been implemented:

| Bonus | Implementation |
|-------|----------------|
| ✅ Additional fractal | **Burning Ship** fractal added alongside Mandelbrot and Julia |
| ✅ Mouse-centered zoom | Zoom follows the actual mouse cursor position |
| ✅ Arrow key navigation | Arrow keys move/pan the view across the fractal plane |
| ✅ Color shifting | Press `C` to cycle through 5 color schemes (Rainbow, Fire, Ice, Purple, Green) |
