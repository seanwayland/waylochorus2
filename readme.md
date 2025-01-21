# Waylo Project

This repository demonstrates how to set up and build the Waylo project using CMake. Follow the steps below to configure and build the project.

## Prerequisites

Ensure you have the following installed on your system:

- [CMake](https://cmake.org/download/) version cmake version 3.24.2 required 
- [Git](https://git-scm.com/)
- A C++ compiler (e.g., GCC, Clang, or MSVC) version 11 of gcc required 

## Instructions

1. Create a new directory for the project and navigate into it:

   ```bash
   mkdir waylo && cd waylo
   ```

2. Copy the `CMakeLists.txt` file into the `waylo` directory.

3. Clone the Waylo Chorus 2 repository:

   ```bash
   git clone --depth=1 git@github.com:seanwayland/waylochorus2.git
   ```

4. Generate build files using CMake:

   ```bash
   cmake -B build -DWAYLO2_SOURCE_DIR=waylochorus2/waylochorus2/waylochorus2
   ```

5. Build the project:

   ```bash
   cmake --build build --config Debug
   ```

## Notes

- The `WAYLO2_SOURCE_DIR` variable specifies the path to the Waylo Chorus 2 source directory. Adjust the path if necessary.
- Use the `--config Release` flag in the build step to build in Release mode instead of Debug mode.

## Troubleshooting

If you encounter issues, ensure that:

- All prerequisites are installed and available in your system's PATH.
- The `WAYLO2_SOURCE_DIR` path is correctly set to the `waylochorus2` source directory.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Happy coding!

