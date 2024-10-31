---
type: yml
---
# demoCI.yml

```yaml
# 目录：
# - Linux-gcc-4.8
# - Linux-gcc (5-13)
# - MacOS
# - Win-MSVC
# - Win-MinGW
# - Win-ClangCl
# - Android

name: CI

on:
  push:
    paths-ignore:
      - '**.md'

  pull_request:
    paths-ignore:
      - '**.md'

jobs:
  build-linux-gcc48:
    name: Linux-gcc-4.8
    runs-on: ubuntu-latest
    container: ubuntu:16.04
    steps:
      - name: Checkout
        uses: actions/checkout@v3

      - name: Install dependency
        run: |
          apt update
          apt install -y gcc-4.8 g++-4.8 make

      - name: Get latest CMake and Ninja
        uses: lukka/get-cmake@latest

      - name: CMake
        run: cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc-4.8 -DCMAKE_CXX_COMPILER=g++-4.8

      - name: Build
        run: cmake --build build --target recorder --parallel 10

      - name: Upload
        uses: actions/upload-artifact@v3
        with:
          name: recorder_linux_gcc48
          path: build/recorder

  build-linux:
    name: Linux-gcc
    runs-on: ubuntu-latest
    strategy:
      matrix:
        compiler: [ '5', '6', '7', '8', '9', '10', '11', '12', '13' ]
    container: gcc:${{ matrix.compiler }}
    steps:
      - name: Checkout
        uses: actions/checkout@v3

      - name: Get latest CMake and Ninja
        uses: lukka/get-cmake@latest

      - name: CMake
        run: cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

      - name: Build
        run: cmake --build build --target recorder --parallel 10

      - name: Upload
        uses: actions/upload-artifact@v3
        with:
          name: recorder_linux_gcc${{ matrix.compiler }}
          path: build/recorder

  build-macos:
    name: MacOS
    runs-on: macos-11
    strategy:
      matrix:
        arch: [ 'arm64', 'x86_64' ]
    steps:
      - name: Checkout
        uses: actions/checkout@v3

      - name: Cmake
        run: cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="${{ matrix.arch }}" -DCMAKE_OSX_DEPLOYMENT_TARGET=10.12

      - name: Build
        run: cmake --build build --target recorder --parallel 10

      - name: Upload
        uses: actions/upload-artifact@v3
        with:
          name: recorder_mac_${{ matrix.arch }}
          path: build/recorder

  build-windows-msvc:
    name: Win-MSVC
    runs-on: windows-2022
    steps:
      - name: Checkout
        uses: actions/checkout@v3

      - name: Cmake
        run: cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022" -A x64

      - name: Build
        run: cmake --build build --target recorder --parallel 10

      - name: Upload
        uses: actions/upload-artifact@v3
        with:
          name: recorder_win_msvc
          path: build/Debug/recorder.exe

  build-windows-mingw:
    name: Win-MinGW
    runs-on: windows-2019
    steps:
      - name: Checkout
        uses: actions/checkout@v3

      - name: Set up MinGW
        uses: egor-tensin/setup-mingw@v2
        with:
          platform: x64

      - name: CMake
        run: cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

      - name: Build
        run: cmake --build build --target recorder --parallel 10

      - name: Upload
        uses: actions/upload-artifact@v3
        with:
          name: recorder_win_mingw
          path: build/recorder.exe

  build-windows-clang-cl:
    name: Win-ClangCl
    runs-on: windows-2019
    steps:
      - name: Checkout
        uses: actions/checkout@v3

      - name: Cmake
        run: cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 16 2019" -A x64 -T ClangCL

      - name: Build
        run: cmake --build build --target recorder --parallel 10

      - name: Upload
        uses: actions/upload-artifact@v3
        with:
          name: recorder_win_clang_cl
          path: build/Debug/recorder.exe

  build-android:
    name: Android
    runs-on: ubuntu-latest
    strategy:
      matrix:
        arch: [ 'arm64-v8a', 'x86_64' ]
    steps:
      - name: Checkout
        uses: actions/checkout@v3

      - name: Get latest CMake and Ninja
        uses: lukka/get-cmake@latest

      - name: Set up JDK 1.8
        uses: actions/setup-java@v1
        with:
          java-version: 1.8

      - name: Set up Android NDK
        uses: nttld/setup-ndk@v1
        id: setup-ndk
        with:
          ndk-version: r25c

      - name: CMake
        run: cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI=${{ matrix.arch }} -DCMAKE_TOOLCHAIN_FILE=${{ steps.setup-ndk.outputs.ndk-path }}/build/cmake/android.toolchain.cmake

      - name: Build
        run: cmake --build build --target recorder --parallel 10

      - name: Upload
        uses: actions/upload-artifact@v3
        with:
          name: recorder_android_${{ matrix.arch }}
          path: build/recorder

```

