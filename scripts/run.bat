@echo off
setlocal
set "CMAKE=cmake"
where cmake.exe >nul 2>&1
if errorlevel 1 (
    for /f "delims=" %%I in ('where clion.exe 2^>nul') do (
        if exist "%%~dpIcmake\win\x64\bin\cmake.exe" set "CMAKE=%%~dpIcmake\win\x64\bin\cmake.exe"
    )
)

cd /d "%~dp0.." || exit /b 1
if not exist build mkdir build || exit /b 1
pushd build || exit /b 1
"%CMAKE%" -G "Visual Studio 18 2026" -DBTEST=ON .. || goto :failed
"%CMAKE%" --build . --config Debug || goto :failed
start "" "%CD%\DataStructure.slnx" || goto :failed
popd
exit /b 0

:failed
popd
exit /b 1
