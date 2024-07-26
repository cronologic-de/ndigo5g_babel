# Ndigo250M-14 User Guide Example

## About

This directory contains a project to compile the C++ example shows in the user guide of the cronologic Ndigo5G-10 analog-to-digital converter.

You can download the user guide from the [product download page](https://download.cronologic.de/Ndigo250M-14/Ndigo250M-14.pdf).

Output is `ndigo_250M_ugex.exe` for Windows, and `ndigo_250M_ugex` for Ubuntu/Debian, and is found on the root shared folder [`/bin`](./bin).

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
- The project is build using `CMake`.
- If you don't have `CMake` installed, refer to [Installing CMake](https://cmake.org/install/) for instructions. You can check if `CMake` is installed by running `cmake --version`.
- On **Windows**, you can build the project using either `CMake` directly, or using Visual Studio 2019 (or later), see [Build Using `CMake`](#build-using-cmake) or [Build Using Visual Studio](#build-using-visual-studio), respectively.
- On **Linux**, you can build the project using `CMake`, see [Build Using `CMake`](#build-using-cmake).

---

### Build Using Visual Studio

**Prerequisites**
- Visual Studio 2019 or later
- [C++ CMake tools for Windows](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio#installation)

  You can install them from the _Visual Studio Installer_ under 
  _Desktop development with C++_.

**Open and configure the project**
1. Open Visual Studio.
2. Select `Open a local folder`.
3. Select the project folder, e.g. `ndigo5g_babel\ug_example_250M`.
4. If "CMake Integration" message _to enable Visual Studio's CMake support with this workspace_ is displayed
   1. Select `Enable and set source directory` button.
   2. In "Select CMakeLists.txt" Dialog, navigate to the <path\to\project\folder>\tools, and open our project `CMakeLists.txt` file, e.g. `ug_example\tools\CMakeLists.txt`

**Compile and Link**

Select `Build -> Build All` from menu, or any standard Visual Studio way to build the project.

**Project Environments and Configurations**

| Configuration     | `CMakeSettings` | `Build root`                     | `CMake generator`     | 
| ----------------- | --------------- | -------------------------------- | --------------------- | 
| **x86_64 Debug**  | x64-Debug       | `${projectDir}\..\build\bfvsD`   | Visual Studio 17 2022 Win64 | 
| **x86_64 Release**| x64-Release     | `${projectDir}\..\build\bfvsR`   | Visual Studio 17 2022 Win64 | 

> **Notes**
> * The provided file builds the project using Visual Studio 2022, however, you can change `generator` in [`CMakeSettings.json`](./tools/CMakeSettings.json) to any other Visual Studio generator you have on your machine.
> * The output folder is the same for both release and debug builds.

---

### Build using `CMake`

In a terminal, navigate to `tools\` and run the following command:

| Platform          | Configuration | Configure CMake command                           | Compile & Link Command                            | 
| ----------------- | ------------- | ----------------------------------------------    | ------------------------------------------------- | 
| **Windows x86_64**| Release       | `cmake -B ..\build\bfR -A x64`                    | `cmake --build ..\build\bfR --config Release`     | 
| **Windows x86_64**| Debug         | `cmake -B ..\build\bfD -A x64`                    | `cmake --build ..\build\bfD --config Debug`       | 
| **Linux x86_64**  | Release       | `cmake -B ../build/bfR -DCMAKE_BUILD_TYPE=Release`| `cmake --build ../build/bfR`                      | 
| **Linux x86_64**  | Debug         | `cmake -B ../build/bfD -DCMAKE_BUILD_TYPE=Debug`  | `cmake --build ../build/bfD`                      | 

> **Notes**
> * The default configuration is `Debug` on Windows, and `Release` on Linux.
> * The output folder is the same for both release and debug builds.
> * You can change the build/output directory from `CMakeLists.txt` file.
> * Linux `x86` is not supported.

---

## Run/Debug the Sample

### Windows
In a terminal, navigate to `/bin` and run the executable. Alternatively, if you are using Visual Studio, you can run/debug the program from within Visual Studio.

### Linux
1. `Cronologic PCI Linux Kernel Module` needs to be installed on your machine. You can build it from [`cronologic_linux_kernel`](https://github.com/cronologic-de/cronologic_linux_kernel) on GitHub.
2. In a terminal, navigate to the `./bin` and run the executable. `sudo` privileges may be necessary.

---

# Ndigo250M on Linux

Ndigo250M requires cronologic_linux_kernel version of 1.1.0 or newer because of contiguous buffers usage.
A Ndigo250M buffer of 2 MB of requires 512 4K pages that are sequential in the physical memory (and below 4G). This is normally not a problem a short time after booting, but after a while, the memory is fragmented and contiguous blocks are no longer available.
When using lower frequencies you can reduce the buffer size and the allocation should work.
If larger buffers are needed and guarantee that the contiguous memory is available at all times, it is recommended to use CMA (Contiguous Memory Allocator), which reserves memory at boot time. Depending on the distribution it might be already enabled (some newer Red Hat derivatives) or not (most Debian distros). 

You can test it by executing:

```
cat /boot/config-$(uname -r)|grep CONFIG_DMA_CMA
```

If not enabled please recompile the kernel by changing this is option to the enabled, after copying the current .config in the following instructions:
https://davidaugustat.com/linux/how-to-compile-linux-kernel-on-ubuntu
CONFIG_DMA_CMA=y

The other CMA options can be left to default.

The boot option should be changed to include this flag now

```
cma=64M@0-4G
```

This reserves 64MB in the lower 4GB of ram (250M requires 32bit DMA addresses) 

* It can be built on Windows and Linux.
* The provided prebuilt linux libraries are tested on Ubuntu/Debian, and might work for other distributions, if they didn't work with you, please contact cronologic support team.