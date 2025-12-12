@echo off
echo Compiling project...
g++ -std=c++17 -I include src/*.cpp -o smartcampus.exe
if %errorlevel%==0 (
    echo Compilation successful. Running program...
    smartcampus.exe
) else (
    echo Compilation failed. Check errors above.
)
pause