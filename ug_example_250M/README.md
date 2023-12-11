# Ndigo250M-14 User Guide Example

## About

This directory contains a project to compile the C++ example shows in the user guide of the cronologic Ndigo5G-10 analog-to-digital converter.

You can download the user guide from the [product download page](https://download.cronologic.de/Ndigo250M-14/Ndigo250M-14.pdf).

## Directory Structure
```
    .
    ├── src/        # source code: .cpp files
    ├── tools/      # files and scripts of the tools, e.g. building tools (CMake, etc...)
    └── build/      # (default) compiled outbput for any OS, configuration, platform
```

---

## Build the Project

### Overview
- The project is a `Console` App.
- The Project can be mainly built using `CMake`, on both Windows and Linux. 
- `CMake` also can be used on Windows by Microsoft Visual Studio 2019 or later for build and debug, [`CMakeSettings.json`](/tools/CMakeSetting.json) is provided to build the project using Visual Studio CMake Tools.

### Prerequisites

##### Install `CMake`
To check if `CMake` is installed, run `cmake --version`; if not installed, please refer to [Installing CMake](https://cmake.org/install/).

### Build Using Visual Studio for Windows
It is mainly done using `CMakeSettings.json` file provided in [`tools` folder](/tools/CMakeSettings.json) package, that uses the projects [`CMakeLists.txt`](/tools/CMakeLists.tx).

#### Prerequisites
##### 1. Install Development Tools
1. `Visual Studio 2019` or later is installed.
2. In "Visual Studio Installer", under "Desktop development with C++", the option [`C++ CMake tools for Windows`](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio#installation) is installed.

##### Open the Project 
1. Open Visual Studio.
2. Select `Open a local folder`.
3. Select the project folder, e.g. `ndigo5g_babel\ug_example_250M`.
4. If "CMake Integration" message _to enable Visual Studio's CMake support with this workspace_ is displayed
   1. Select `Enable and set source directory` button.
   2. In "Select CMakeLists.txt" Dialog, navigate to the <path\to\project\folder>\tools, and open our project `CMakeLists.txt` file, e.g. `ug_example\tools\CMakeLists.txt`

##### Compile and Link
Select `Build -> Build All` from menu, or any standard Visual Studio way to build the project.

#### Project Environments and Configurations
The Target Exectuable name is `ndigo_250M_ugex.exe`.
| Configuration     | `CMakeSettings` | `Build root`                     | `CMake generator`     | Output Folder          |
| ----------------- | --------------- | -------------------------------- | --------------------- | ---------------------  |
| **x86_64 Debug**  | x64-Debug       | `${projectDir}\..\build\bfvsD`   | Visual Studio 17 2022 Win64 | `driver\x64\Release`   |
| **x86_64 Release**| x64-Release     | `${projectDir}\..\build\bfvsR`   | Visual Studio 17 2022 Win64 | `driver\x64\Release`   |
* The provided file builds the project using `Visual Studio 2022`, however, you can change `generator` in  `CMakeSettings.json` to any other Visual Studio generator you have on your machine.

### Build Using `CMake`, for Windows and Linux

Go to tools: `cd tools`, then run the following command:
| Platform          | Configuration | Configur CMake ommand                                                           | Compile & Link Command                            | Output Folder          |
| ----------------- | ------------- | -------------------------------------------------     | ------------------------------------------------- | ---------------------  |
| **Windows x86_64**| Release       | `cmake -B ..\build\bfR -A x64`                                                  | `cmake --build ..\build\bfR --config Release`     | `driver\x64\Release`   |
| **Windows x86_64**| Debug         | `cmake -B ..\build\bfD -A x64`                                                  | `cmake --build ..\build\bfD --config Debug`       | `driver\x64\Debug`     |
| **Linux x86_64**  | Release       | `cmake -B ../build/bfR -DCMAKE_BUILD_TYPE=Release`                              | `cmake --build ../build/bfR`                      | `bin`   |
| **Linux x86_64**  | Debug         | `cmake -B ../build/bfD -DCMAKE_BUILD_TYPE=Debug`                                | `cmake --build ../build/bfD`                      | `bin`     |

* The default configuration is `Debug` on Windows, and `Release` on Linux.
* Linux x86 is not supported.

---

## Run/Debug the Sample

**Prerequisites**
- Cronologic Kernel Module is installed.

**Steps**
- Run the executable found in the _Output Folder_ from system command, you might need to use `sudo` in Linux.
- For Windows, there is nothing special about using MS Visual Studio in debugging the project, just go ahead using MS Visual Studio debugger.
