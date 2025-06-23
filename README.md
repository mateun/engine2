# Engine-CRS

A modern C++ game engine built on Vulkan, featuring a scene graph, GLTF mesh loading, Win32 windowing, and efficient GPU resource management.

## Features
- Vulkan 1.3 renderer with validation and debug support
- Scene graph with hierarchical transforms
- GLTF mesh loading (via tinygltf)
- Per-mesh GPU buffer management
- Win32 windowing
- Camera system with perspective and view controls
- Texture loading and sampling
- Efficient command buffer usage
- RenderDoc integration for debugging

## Getting Started

### Prerequisites
- Windows 10 or later
- [Visual Studio 2022](https://visualstudio.microsoft.com/)
- [Vulkan SDK 1.3+](https://vulkan.lunarg.com/)
- [CMake 3.20+](https://cmake.org/)

### Building
1. **Clone the repository:**
   ```sh
   git clone <your-repo-url>
   cd engine-crs
   ```
2. **Configure with CMake:**
   ```sh
   cmake -S . -B build
   ```
3. **Build the project:**
   ```sh
   cmake --build build --config Debug
   ```
4. **Run the engine:**
   - The executable will be in `build/` or your chosen output directory.

### Visual Studio
- Open the generated `.sln` file in Visual Studio for IDE-based development and debugging.

## Assets
- Place your GLTF models and textures in the `assets/` directory.
- Example assets:
  - `assets/test.glb` (GLTF mesh)
  - `assets/debug_texture.png` (texture)

## Usage
- The engine loads and displays a GLTF mesh with a camera and basic controls.
- Modify `main.cpp` to load different assets or extend the scene graph.

## Dependencies
- [Vulkan SDK](https://vulkan.lunarg.com/)
- [GLM](https://github.com/g-truc/glm) (included in `external/`)
- [tinygltf](https://github.com/syoyo/tinygltf) (included in `external/`)
- [stb_image](https://github.com/nothings/stb) (included in `external/`)

## Contributing
Pull requests and issues are welcome! Please:
- Follow the code style (snake_case for methods, etc.)
- Write clear commit messages
- Test your changes before submitting

## License
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details. 