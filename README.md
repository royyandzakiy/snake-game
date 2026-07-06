# Snake Game

A modern C++ implementation of the classic Snake game using raylib. This project follows C++ Core Guidelines, implements modern C++23 practices, and is built with a professional CMake configuration supporting multiple compilers and platforms.

## Features

- Classic snake gameplay with smooth controls
- Food collection with score tracking
- Wall collision and self-collision detection
- Responsive movement with frame-rate independent timing
- Audio feedback for eating and game over events
- Clean, modern C++23 implementation following best practices

## Requirements

- C++23 compatible compiler (Clang, GCC, MSVC, or AppleClang)
- CMake 3.28 or higher
- Conan 2.0 package manager
- Raylib and fmt libraries (automatically handled by Conan)

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/yourusername/snake-game.git
cd snake-game
```

### Build with CMake Presets

The project uses CMake presets for easy configuration. Available presets:

**Windows**
- `clang-cl-debug` / `clang-cl-release` (recommended)
- `msvc-debug` / `msvc-release`
- `mingw-debug` / `mingw-release`

**Linux**
- `clang-linux-debug` / `clang-linux-release` (recommended)
- `gcc-linux-debug` / `gcc-linux-release`

**macOS**
- `appleclang-debug` / `appleclang-release`

#### Example Build (Clang on Linux)

```bash
cmake --preset clang-linux-debug
cmake --build --preset clang-linux-debug
```

#### Example Build (Clang-CL on Windows)

```bash
cmake --preset clang-cl-debug
cmake --build --preset clang-cl-debug
```

### Run the Game

After building, run the executable from the build output directory:

```bash
./build/clang-linux-debug/snake_game    # Linux
./bin/clang-cl/snake_game.exe           # Windows
```

## Project Structure

```
snake-game/
├── assets/                 # Game assets (textures, audio)
├── cmake/                  # CMake modules and configurations
├── src/                    # Source code
│   └── hello/              # Main game implementation
│       ├── CMakeLists.txt
│       └── main.cpp
├── test/                   # Unit tests
├── CMakeLists.txt
├── CMakePresets.json       # CMake presets configuration
├── conanfile.txt           # Conan dependencies
└── README.md
```

## Implementation Details

### Modern C++ Practices

- **C++23 Standard**: Utilizes latest language features
- **Core Guidelines**: Follows C++ Core Guidelines for safe, idiomatic C++
- **RAII**: Proper resource management with constructors and destructors
- **Move Semantics**: Efficient ownership transfer where appropriate
- **Type Safety**: Strong type usage and explicit conversions
- **Const Correctness**: Proper const qualification throughout

### Code Quality

- **clang-tidy**: Static analysis integrated into the build
- **clangd**: Language server support for excellent IDE experience
- **Formatting**: Consistent code style with automated formatting
- **Sanitizers**: ASan, TSan, MSan available for debugging

### Architecture

The game follows a clean separation of concerns:

- **Game**: Orchestrates game loop, input handling, and state management
- **Snake**: Manages snake state, movement, and collision detection
- **Food**: Handles food spawning and rendering

## Asset Setup

The project expects assets in the following locations:

- Food texture: `assets/imgs/food.png`
- Eat sound: `assets/audio/eat.mp3`
- Game over sound: `assets/audio/wall.mp3`

Update the asset paths in `main.cpp` to match your project structure if needed.

## Credits

This project follows the tutorial by [Learn C++ Games](https://www.youtube.com/watch?v=LGqsnM_WEK4) but has been completely refactored to use modern C++23, best practices, and a professional project structure.

- My Base project template: [cpp-project-template-min](https://github.com/royyandzakiy/cpp-project-template-min)
- Game assets: Provided by the tutorial
- Raylib: [raysan5/raylib](https://github.com/raysan5/raylib)
- fmt: [fmtlib/fmt](https://github.com/fmtlib/fmt)

## License

This project is open source. See the LICENSE file for details.
