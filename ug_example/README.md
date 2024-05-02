# Ndigo5G-10 User Guide Example

## About

This directory contains a project to compile the C++ example shown in the user guide of the cronologic Ndigo5G-10 analog-to-digital converter.
The project is a `Console` App.

You can download the user guide from the [product web page](https://www.cronologic.de/products/adcs/cronologic-ndigo5g-10).

## Directory Structure
```
    .
    ├── src/        # source code: .cpp files
    ├── tools/      # files and scripts of the tools, e.g. building tools (CMake, etc...)
    └── build/      # (default) compiled output for any OS, configuration, platform
```

---
---

## Build the Project

The project is build using `CMake`.

If you don't have `CMake` installed, refer to [Installing CMake](https://cmake.org/install/) for instructions. You can check if `CMake` is installed by
running `cmake --version`.

On **Windows**, you can install the project using either `CMake` directly, or using Visual Studio 2019 (or later), see [Build Using `CMake`](#build-using-cmake) or [Build Using Visual Studio](#build-using-visual-studio), respectively.

On **Linux**, you can install the project using `CMake`, see [Build Using `CMake`](#build-using-cmake).

---

### Build Using Visual Studio

**Prerequisites**
- Visual Studio 2019 or later
- [C++ CMake tools for Windows](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio#installation)

  You can install these from the _Visual Studio Installer_ under 
  _Desktop development with C++_.

**Open and configure the project**
1. Open Visual Studio.
2. Select `Open a local folder`.
3. Select the project folder, e.g., `ndigo5g_babel\ug_example`.
4. If a "CMake Integration" message _to enable Visual Studio's CMake support with this workspace_ is displayed
   1. Select `Enable and set source directory` button.
   2. In "Select CMakeLists.txt" Dialog, navigate to `<path\to\project\folder>\tools`, and open `CMakeLists.txt` file, e.g. `ug_example\tools\CMakeLists.txt`

**Compile and Link**

Select `Build -> Build All` from the menu bar (or any standard Visual Studio way to build the project).

**Project Environments and Configurations**

The target executable name is `ndigo_ugex.exe`.

| Configuration     | `CMakeSettings` | `Build root`                     | `CMake generator`     | Output Folder          |
| ----------------- | --------------- | -------------------------------- | --------------------- | ---------------------  |
| **x86_64 Debug**  | x64-Debug       | `${projectDir}\..\build\bfvsD`   | Visual Studio 17 2022 Win64 | `lib\x64\Debug`   |
| **x86_64 Release**| x64-Release     | `${projectDir}\..\build\bfvsR`   | Visual Studio 17 2022 Win64 | `lib\x64\Release`   |


> **Note**
The provided file builds the project using Visual Studio 2022, however, you can change `generator` in [`CMakeSettings.json`](./tools/CMakeSettings.json) to any other Visual Studio generator you have on your machine.


---

### Build using `CMake`

In a terminal, navigate to `tools\` and run the following command

| Platform          | Configuration | Configure CMake command                                                           | Compile & Link Command                            | Output Folder          |
| ----------------- | ------------- | -------------------------------------------------     | ------------------------------------------------- | ---------------------  |
| **Windows x86_64**| Release       | `cmake -B ..\build\bfR -A x64`                                                  | `cmake --build ..\build\bfR --config Release`     | `bin`   |
| **Windows x86_64**| Debug         | `cmake -B ..\build\bfD -A x64`                                                  | `cmake --build ..\build\bfD --config Debug`       | `bin`     |
| **Linux x86_64**  | Release       | `cmake -B ../build/bfR -DCMAKE_BUILD_TYPE=Release`                              | `cmake --build ../build/bfR`                      | `bin`   |
| **Linux x86_64**  | Debug         | `cmake -B ../build/bfD -DCMAKE_BUILD_TYPE=Debug`                                | `cmake --build ../build/bfD`                      | `bin`     |

> **Note**
The default configuration is `Debug` on Windows, and `Release` on Linux.

> **Note**
Linux `x86` is not supported.

---
---

## Run/Debug the Program

### Windows

1. The device driver is necessary to run the executable. You can download the
   driver from cronologic's Ndigo5G [product page](https://www.cronologic.de/product/ndigo5g-10).
2. Copy `ndigo5g_babel\lib\ndigo_driver_64.dll` to the _Output Folder_.
3. In a terminal, navigate to the _Output Folder_ and run the executable

### Linux
1. `Cronologic PCI Linux Kernel Module` needs to be installed on your machine. You can build it from [`cronologic_linux_kernel`](https://github.com/cronologic-de/cronologic_linux_kernel) on GitHub.
2. In a terminal, navigate to the _Output Folder_ and run the executable. `sudo` privileges might be necessary.