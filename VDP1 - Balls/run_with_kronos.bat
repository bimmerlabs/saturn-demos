@ECHO Off
where /q kronos.exe
IF ERRORLEVEL 1 (
    echo "Using project kronos installation!"
    SET KRONOS=../../emulators/kronos/kronos.exe
) else (
    echo "Using system's kronos installation!"
    SET KRONOS=../../emulators/kronos/kronos.exe
)

if not exist ./BuildDrop/*.cue (
    echo "CUE/ISO missing, please build first."
) else (
    @REM Finding first cue file and running it on kronos
    FOR %%F IN (./BuildDrop/*.cue) DO (
        start %KRONOS% ./BuildDrop/%%F
        exit /b
    )
)