*This project has been created as part of the 42 curriculum by mhaizan.*

<!-- Project Banner -->
<div align="center">
  <h1>🌀 Fract'ol</h1>
  <p><em>A graphical exploration of fractals using the escape-time algorithm</em></p>
  
  ![42 Badge](https://img.shields.io/badge/42-Project-blue)
  ![Language](https://img.shields.io/badge/Language-C-green)
  ![Norminette](https://img.shields.io/badge/Norminette-Passing-success)
  ![Score](https://img.shields.io/badge/Score-125%2F100-brightgreen)
  
  <p><strong>A 42 School Graphics Project by mhaizan</strong></p>
  <img width="201" height="170" alt="fractol score" src="https://github.com/user-attachments/assets/2a9c6e0c-a707-4d51-8806-073e49727ae8" />

</div>

---

## 📋 Table of Contents

1. [Description](#-description)
2. [Instructions](#-instructions)
3. [42 School Rules & Requirements](#-42-school-rules--requirements)
4. [Understanding Fractals](#-understanding-fractals)
5. [The Mathematics Behind Fractals](#-the-mathematics-behind-fractals)
6. [Implemented Fractals](#-implemented-fractals)
7. [Color Schemes](#-color-schemes)
8. [Controls](#-controls)
9. [Project Architecture](#-project-architecture)
10. [Technical Implementation](#-technical-implementation)
11. [What I Learned](#-what-i-learned)
12. [Resources](# success
125-resources)

---

## 📝 Description

**Fract'ol** is a graphical project from the 42 School curriculum that introduces students to computer graphics programming using the MiniLibX library. The project involves rendering beautiful mathematical fractals using the escape-time algorithm, with interactive zoom and pan capabilities.

### Project Goal

The primary objective is to create a visually stunning fractal explorer that:
- Renders the **Mandelbrot set**, **Julia sets**, and **Burning Ship** fractal
- Allows **infinite zoom** into the fractal structure
- Provides **smooth navigation** with keyboard and mouse controls
- Offers **multiple color schemes** for visual customization

### Brief Overview

This implementation features:

- **Three fractal types**: Mandelbrot, Julia (with customizable parameters), and Burning Ship
- **Mouse-centered zoom**: Smooth zooming that preserves the point under the cursor
- **Five color palettes**: Rainbow, Fire, Ice, Purple, and Green gradients
- **Real-time parameter adjustment**: Modify Julia constants interactively
- **Iteration control**: Adjust detail level dynamically

### Key Features

- ✅ Renders Mandelbrot, Julia, and Burning Ship fractals
- ✅ Smooth mouse-wheel zoom centered on cursor position
- ✅ Arrow key navigation for panning the viewport
- ✅ Adjustable iteration count for detail control (+/- keys)
- ✅ Five beautiful color schemes (cycle with C key)
- ✅ Interactive Julia parameter modification (J/L/I/M keys)
- ✅ 800x800 pixel render window
- ✅ Fully Norminette compliant
- ✅ No memory leaks

---

## 📖 Instructions

### Prerequisites

Before compiling, ensure you have:
- **GCC** or **Clang** compiler
- **Make** build system
- **X11 development libraries** (for MiniLibX on Linux)
- A Unix-like operating system (Linux recommended)

On Ubuntu/Debian, install required dependencies:
```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

### Compilation

Clone the repository and compile using the Makefile:

```bash
# Clone the repository
git clone https://github.com/yourusername/fractol.git
cd fractol

# Compile the program (MiniLibX will be cloned automatically)
make

# The executable 'fractol' will be created in the root directory
```

#### Makefile Rules

| Command | Description |
|---------|-------------|
| `make` or `make all` | Compile the program (clones MiniLibX if needed) |
| `make clean` | Remove object files (`.o` files) |
| `make fclean` | Remove object files and the executable |
| `make re` | Recompile everything from scratch |

### Installation

No installation is required. After compilation, the `fractol` executable can be run directly from the project directory.

### Execution

The program accepts the fractal type as a command-line argument:

```bash
# Render the Mandelbrot set
./fractol mandelbrot

# Render the Burning Ship fractal
./fractol burning_ship

# Render a Julia set with custom parameters
./fractol julia <real> <imaginary>
```

#### Examples

```bash
# Classic Mandelbrot set
./fractol mandelbrot

# Burning Ship fractal
./fractol burning_ship

# Julia set with common interesting parameters
./fractol julia -0.7 0.27015
./fractol julia 0.355 0.355
./fractol julia -0.4 0.6
./fractol julia -0.8 0.156
```

#### Error Handling

Invalid inputs display a usage message:

```bash
./fractol               # Missing argument
./fractol unknown       # Invalid fractal name
./fractol julia 1       # Missing Julia parameter
./fractol julia a b     # Invalid float format
```

Usage: `./fractol mandelbrot | burning_ship | julia <r> <i>`

---

## 📜 42 School Rules & Requirements

### The Norm (Norminette)

All code must comply with **42's coding standard** called "The Norm":

| Rule | Description |
|------|-------------|
| **Function Length** | Maximum 25 lines per function |
| **Functions per File** | Maximum 5 functions per `.c` file |
| **Line Length** | Maximum 80 characters per line |
| **Variable Declaration** | All variables declared at the start of functions |
| **No `for` loops** | Only `while` loops are allowed |
| **Global Variables** | Forbidden |
| **Allowed Functions** | `open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `exit`, math library, MiniLibX |

### Mandatory Part Requirements

The project **must** implement:

```
Program name    : fractol
Turn in files   : Makefile, *.h, *.c
Makefile rules  : NAME, all, clean, fclean, re
Arguments       : Fractal type (and Julia parameters if applicable)
External functs : MiniLibX library, math library (-lm)
Description     : Create a graphical fractal renderer
```

### Required Features

| Feature | Requirement |
|---------|-------------|
| **Mandelbrot** | Must be implemented |
| **Julia** | Must be implemented with parameter input |
| **Zoom** | Mouse wheel zoom (in/out) |
| **Color** | Must use psychedelic coloring |
| **Window Management** | Clean exit on ESC and window close button |
| **Image Rendering** | Must use MiniLibX images (not put_pixel to window) |

### What Makes a Valid Submission

✅ **Compiles** with `-Wall -Wextra -Werror` flags  
✅ **No memory leaks** (check with `valgrind`)  
✅ **No crashes** (segfault, bus error, etc.)  
✅ **Handles window close** properly (ESC and X button)  
✅ **Follows the Norm** (run `norminette` on all files)  
✅ **Makefile works** correctly with all required rules  
✅ **Smooth user experience** (responsive controls)

---

## 🎨 Understanding Fractals

### What Is a Fractal?

A **fractal** is a mathematical set that exhibits **self-similarity** at different scales. When you zoom into a fractal, you discover similar patterns repeating infinitely. This property makes fractals both mathematically fascinating and visually stunning.

```
Zoom Level 1:            Zoom Level 2:           Zoom Level 3:
    ████████                 ████                    ██
   ██      ██               █    █                  █  █
  ██        ██             █      █                █    █
   ██      ██               █    █                  █  █
    ████████                 ████                    ██

          Same patterns appear at every scale!
```

### The Escape-Time Algorithm

The fractals in this project use the **escape-time algorithm**:

1. For each pixel on screen, map it to a point on the complex plane
2. Apply an iterative formula (like z = z² + c)
3. Count how many iterations before the value "escapes" (exceeds a threshold)
4. Color the pixel based on the iteration count

```
Iteration 0:  z = 0
Iteration 1:  z = z² + c = c
Iteration 2:  z = z² + c = c² + c
Iteration 3:  z = z² + c = (c² + c)² + c
    ...
Until |z| > 2 (escaped) or max_iterations reached
```

Points that **never escape** are part of the fractal set (colored black).
Points that **escape** are colored based on how quickly they escaped.

---

## 🔢 The Mathematics Behind Fractals

### Complex Numbers

Fractals live in the **complex plane**. A complex number has two parts:

```
z = a + bi

Where:
  a = real part (horizontal axis)
  b = imaginary part (vertical axis)
  i = √(-1) (the imaginary unit)
```

### Complex Arithmetic

**Addition**: `(a + bi) + (c + di) = (a+c) + (b+d)i`

**Squaring**: `(a + bi)² = a² - b² + 2abi`

This squaring operation is the heart of fractal iteration!

### The Iteration Formula

For the Mandelbrot and Julia sets:

```
z(n+1) = z(n)² + c

Expanding:
  z_real_new = z_real² - z_imag² + c_real
  z_imag_new = 2 × z_real × z_imag + c_imag
```

### Escape Condition

A point "escapes" when its magnitude exceeds 2:

```
|z| = √(z_real² + z_imag²) > 2

Optimized (avoid sqrt):
  z_real² + z_imag² > 4
```

---

## 🎯 Implemented Fractals

### 1. Mandelbrot Set

The **Mandelbrot set** is the most famous fractal, discovered by Benoit Mandelbrot in 1980.

**Formula**: `z(n+1) = z(n)² + c`

**Starting values**:
- `z(0) = 0` (always starts at origin)
- `c = pixel coordinate` (varies per pixel)

```
For each pixel (x, y):
  c = complex coordinate of pixel
  z = 0
  iterate until escape or max_iter
```

The Mandelbrot set is the collection of all `c` values for which the iteration does **not** escape to infinity.

**Interesting regions to explore**:
- Main cardioid: The large heart-shaped region
- Period-2 bulb: The circular bulb to the left
- Seahorse Valley: Between the cardioid and bulb (`-0.75, 0.1`)
- Elephant Valley: Similar area with different structures

### 2. Julia Sets

**Julia sets** are closely related to the Mandelbrot set. Each point in the Mandelbrot set corresponds to a unique Julia set!

**Formula**: `z(n+1) = z(n)² + c`

**Starting values**:
- `z(0) = pixel coordinate` (varies per pixel)
- `c = fixed constant` (user-defined parameter)

```
For each pixel (x, y):
  z = complex coordinate of pixel
  c = fixed Julia constant (from command line)
  iterate until escape or max_iter
```

**Beautiful Julia parameters to try**:
| Real | Imaginary | Description |
|------|-----------|-------------|
| -0.7 | 0.27015 | Classic Julia "rabbit" |
| 0.355 | 0.355 | Symmetric snowflake |
| -0.4 | 0.6 | Dragon-like pattern |
| -0.8 | 0.156 | Spiral arms |
| -0.7269 | 0.1889 | Dendritic structure |

### 3. Burning Ship

The **Burning Ship** fractal uses absolute values before squaring, creating an asymmetric, flame-like appearance.

**Formula**: `z(n+1) = (|Re(z)| + i|Im(z)|)² + c`

**Implementation**:
```c
abs_zr = |z_real|
abs_zi = |z_imag|
z_real_new = abs_zr² - abs_zi² + c_real
z_imag_new = 2 × abs_zr × abs_zi + c_imag
```

The absolute value operation breaks the symmetry found in Mandelbrot/Julia sets, producing unique structures like the characteristic "ship" shape.

---

## 🌈 Color Schemes

This implementation includes **five color palettes** that map iteration counts to colors:

### 1. Rainbow (Scheme 0)

Uses **sinusoidal functions** with phase shifts to create smooth, cyclic rainbow gradients:

```c
r = sin(0.1 × i + 0) × 127 + 128
g = sin(0.1 × i + 2) × 127 + 128
b = sin(0.1 × i + 4) × 127 + 128
```

### 2. Fire (Scheme 1)

Uses **polynomial interpolation** to create warm red/orange/yellow gradients:

```c
t = i / max_iter  // Normalized [0, 1]
r = 9 × (1-t) × t³ × 255
g = 15 × (1-t)² × t² × 255
b = 8.5 × (1-t)³ × t × 255
```

### 3. Ice (Scheme 2)

Cool cyan/blue palette, essentially the inverse of Fire:

```c
t = i / max_iter
r = 8.5 × (1-t)³ × t × 255
g = 15 × (1-t)² × t² × 255
b = 9 × (1-t) × t³ × 255
```

### 4. Purple (Scheme 3)

Blue/magenta transitions emphasizing purple tones.

### 5. Green (Scheme 4)

Nature-inspired green gradients.

Press **C** to cycle through all color schemes during exploration!

---

## 🎮 Controls

### Keyboard Controls

| Key | Action |
|-----|--------|
| `ESC` | Exit the program |
| `←` `→` | Pan left/right |
| `↑` `↓` | Pan up/down |
| `+` or `=` | Increase iterations (+10) |
| `-` or `_` | Decrease iterations (-10) |
| `C` | Cycle color scheme |

### Julia Mode Controls

| Key | Action |
|-----|--------|
| `J` | Decrease Julia real component |
| `L` | Increase Julia real component |
| `I` | Increase Julia imaginary component |
| `M` | Decrease Julia imaginary component |

### Mouse Controls

| Button | Action |
|--------|--------|
| Scroll Up | Zoom in (centered on cursor) |
| Scroll Down | Zoom out (centered on cursor) |

### Tips for Exploration

1. **Start with low iterations** (default 100) for fast navigation
2. **Increase iterations** when zoomed deep for more detail
3. **Use mouse-centered zoom** to explore specific areas
4. **Try different color schemes** - they reveal different structures
5. **In Julia mode**, use J/L/I/M to morph the fractal in real-time

---

## 🏗️ Project Architecture

### Directory Structure

```
fractol/
├── Makefile              # Build automation
├── README.md             # This documentation
├── srcs/                 # Source files
│   ├── fractol.h         # Header with definitions and prototypes
│   ├── main.c            # Entry point and argument parsing
│   ├── init.c            # MLX initialization and setup
│   ├── event.c           # Keyboard and mouse event handlers
│   ├── rendering.c       # Fractal rendering pipeline
│   ├── maths.c           # Math utilities and string functions
│   └── colors.c          # Color scheme implementations
└── minilibx-linux/       # MiniLibX library (cloned automatically)
```

### Module Responsibilities

| Module | Purpose | Key Functions |
|--------|---------|---------------|
| **main.c** | Entry point, argument validation | `main()`, `is_valid_float()`, `run_fractol()` |
| **init.c** | MLX setup, event registration | `init_fractol()`, `events_init()`, `image_data()` |
| **event.c** | User input handling | `handle_keypress()`, `handle_mouse()`, `close_window()` |
| **rendering.c** | Pixel rendering, iteration | `fractol_render()`, `handle_pixel()`, `iterate()` |
| **maths.c** | Math utilities | `ft_atof()`, `sum_c()`, `square_c()`, `ft_strncmp()` |
| **colors.c** | Color palette functions | `scheme_rainbow()`, `scheme_fire()`, `scheme_ice()`, etc. |

### Data Structures

```c
// Complex number representation
typedef struct s_complex
{
    double real;    // Real part (x-axis)
    double imag;    // Imaginary part (y-axis)
} t_complex;

// Image buffer for MiniLibX
typedef struct s_image
{
    void    *img_ptr;     // MLX image pointer
    char    *pixels_ptr;  // Raw pixel buffer
    int     bpp;          // Bits per pixel
    int     endian;       // Byte order
    int     line_len;     // Bytes per row
} t_image;

// Main fractal state
typedef struct s_fractol
{
    void        *mlx;           // MLX context
    void        *win;           // Window handle
    t_image     img;            // Image buffer
    int         max_iter;       // Iteration limit
    double      zoom;           // Current zoom level
    double      offset_x;       // Pan offset (real axis)
    double      offset_y;       // Pan offset (imaginary axis)
    char        *name;          // Fractal type name
    int         escape;         // Escape threshold (4)
    double      julia_real;     // Julia c.real
    double      julia_imag;     // Julia c.imag
    int         color_scheme;   // Active palette index
} t_fractol;
```

### Rendering Pipeline

```
┌─────────────────┐
│  fractol_render │ Entry point
└────────┬────────┘
         ▼
┌─────────────────┐
│  For each pixel │ Loop through 800×800 pixels
│    handle_pixel │
└────────┬────────┘
         ▼
┌─────────────────┐
│   init_coords   │ Map pixel to complex plane
└────────┬────────┘
         ▼
┌─────────────────┐
│    iterate()    │ Apply z = z² + c until escape
└────────┬────────┘
         ▼
┌─────────────────┐
│   get_color()   │ Map iteration count to color
└────────┬────────┘
         ▼
┌─────────────────┐
│ imag_pixel_put  │ Write color to image buffer
└────────┬────────┘
         ▼
┌─────────────────┐
│ mlx_put_image   │ Display image in window
└─────────────────┘
```

---

## 🔧 Technical Implementation

### Coordinate Mapping

Converting screen pixels to complex coordinates:

```c
// Scale factor for 4.0 unit span across shortest dimension
scale = 4.0 / min(WIDTH, HEIGHT);

// Pixel to complex coordinate
px = (x - WIDTH/2) × scale × zoom + offset_x;
py = (y - HEIGHT/2) × scale × zoom + offset_y;
```

### Mouse-Centered Zoom

The zoom preserves the point under the cursor:

```c
// 1. Get complex coordinate before zoom
cr = (mouse_x - WIDTH/2) × scale × old_zoom + offset_x;
ci = (mouse_y - HEIGHT/2) × scale × old_zoom + offset_y;

// 2. Apply zoom factor
new_zoom = old_zoom × zoom_factor;

// 3. Recalculate offset to keep (cr, ci) under cursor
offset_x = cr - (mouse_x - WIDTH/2) × scale × new_zoom;
offset_y = ci - (mouse_y - HEIGHT/2) × scale × new_zoom;
```

### Iteration Optimization

The escape check avoids expensive square root:

```c
// Instead of: sqrt(z.real² + z.imag²) > 2
// Use:        z.real² + z.imag² > 4
```

### Image Buffer Writing

Direct pixel buffer manipulation for performance:

```c
void imag_pixel_put(int x, int y, t_image *img, int color)
{
    int offset;
    
    // Calculate byte offset: row * line_length + column * bytes_per_pixel
    offset = (y * img->line_len) + (x * (img->bpp / 8));
    
    // Write 4-byte color directly to buffer
    *(unsigned int *)(img->pixels_ptr + offset) = color;
}
```

---

## 📚 What I Learned

### Technical Skills

1. **Computer Graphics**: Understanding how images are rendered pixel by pixel
2. **Complex Number Mathematics**: Working with complex plane transformations
3. **Event-Driven Programming**: Handling keyboard and mouse input in real-time
4. **Memory Management**: Proper allocation and cleanup of graphical resources
5. **Optimization**: Writing efficient rendering code for smooth interaction

### Mathematical Concepts

1. **Iteration and Convergence**: Understanding when sequences escape or stabilize
2. **Coordinate Systems**: Mapping between screen space and complex plane
3. **Self-Similarity**: The fascinating property of fractals at different scales
4. **Color Theory**: Creating visually appealing gradients from mathematical functions

### Problem-Solving Skills

1. **Debugging graphical applications**: Using visual output to trace issues
2. **Performance tuning**: Balancing quality (iterations) vs. speed
3. **User experience**: Making controls intuitive and responsive

---

## 🔗 Resources

### Fractal Mathematics

- [Mandelbrot Set - Wikipedia](https://en.wikipedia.org/wiki/Mandelbrot_set) - Comprehensive mathematical explanation
- [Julia Set - Wikipedia](https://en.wikipedia.org/wiki/Julia_set) - Theory behind Julia sets
- [Burning Ship Fractal](https://en.wikipedia.org/wiki/Burning_Ship_fractal) - The asymmetric variant

### MiniLibX Documentation

- [42 Docs - MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) - Official 42 documentation
- [MiniLibX Linux Repository](https://github.com/42Paris/minilibx-linux) - Source code and examples

### Tutorials and Guides

- [Fract'ol Tutorial](https://reactive.so/post/42-a-comprehensive-guide-to-fractol) - Step-by-step implementation guide
- [Complex Numbers Visualization](https://www.youtube.com/watch?v=5PcpBw5Hbwo) - 3Blue1Brown video on complex numbers
- [The Art of the Mandelbrot Set](https://www.youtube.com/watch?v=NGMRB4O922I) - Beautiful deep zoom video

### Tools for Testing

- [Online Mandelbrot Explorer](https://mandelbrot.ophir.dev/) - Compare your output
- [Julia Set Generator](https://sciencedemos.org.uk/julia_sets.php) - Find interesting Julia parameters

---

## 🤖 AI Usage Disclosure

In accordance with 42's policy on AI transparency:

### AI Tools Used

- **GitHub Copilot / Claude** - AI coding assistant

### Tasks Where AI Was Used

| Task | AI Involvement | Description |
|------|----------------|-------------|
| **Code Documentation** | ✅ Used | AI assisted in writing comprehensive comments explaining function purposes and mathematical concepts |
| **README Writing** | ✅ Used | AI helped structure and write this README file, including explanations and formatting |
| **Code Review** | ✅ Used | AI was used to review code for clarity and potential improvements |

### Tasks Where AI Was NOT Used

| Task | AI Involvement | Description |
|------|----------------|-------------|
| **Algorithm Implementation** | ❌ Not Used | The fractal iteration algorithms were implemented based on mathematical understanding |
| **Core Rendering Logic** | ❌ Not Used | The MiniLibX integration and pixel rendering were coded independently |
| **Debugging** | ❌ Not Used | All bugs were identified and fixed through manual testing |
| **Mathematical Research** | ❌ Not Used | Understanding of complex numbers and fractals came from studying resources |

---

## 🏆 Conclusion

Fract'ol is a beautiful introduction to computer graphics programming. It combines mathematical elegance with visual artistry, teaching fundamental concepts about rendering, coordinate systems, and optimization.

The infinite complexity hidden within simple formulas like `z = z² + c` never ceases to amaze. Each zoom reveals new patterns, and each Julia parameter creates a unique mathematical universe.

Key takeaways from this project:

1. **Mathematics is beautiful**: Fractals demonstrate the visual beauty of mathematical iteration
2. **Optimization matters**: Efficient code enables smooth, interactive exploration
3. **Simple rules, complex results**: The Mandelbrot set emerges from just one equation
4. **User experience is key**: Good controls make exploration enjoyable

I hope this project inspires you to explore the infinite beauty of fractals! 🌀

---

<div align="center">
  <p><strong>Made with ❤️ at 42 Amman</strong></p>
  <p><em>mhaizan - 2026</em></p>
</div>
