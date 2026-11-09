@echo off
setlocal
cd /d "%~dp0.."

if not exist "third_party\gtest\CMakeLists.txt" (
  echo Google Test is not installed.
  echo First run: git submodule update --init --recursive
  exit /b 1
)

where cmake >nul 2>&1
if errorlevel 1 (
  echo CMake not found in PATH. Set the CMake path in CLion or add it to PATH.
  exit /b 1
)

cmake -S . -B build -G Ninja -DBTEST=ON
if errorlevel 1 exit /b 1
cmake --build build
if errorlevel 1 exit /b 1
ctest --test-dir build --output-on-failure
if errorlevel 1 exit /b 1

echo Build and tests succeeded.
exit /b 0
