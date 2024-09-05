@ECHO Off
SET COMPILER_DIR=..\..\Compiler
SET PATH=%COMPILER_DIR%\WINDOWS\Other Utilities;%COMPILER_DIR%\WINDOWS\bin;%PATH%
REM uncomment and update path to auto-build your palettes etc:
REM perl "path-to\tga_tools.pl" --p "path-to-project\joengine-master\Projects\demo - HSL color calc" --in_image IMAGENAME
make re
