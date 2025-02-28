@echo off

clear

SET local=%1

if "%local%" == "local" (
  SET apiKey=h3y83ej3917mcblxpxiij62bu6jzixj1oflcz32meic17t44wa
) else (
  SET apiKey=0
)

if "%apiKey%" == "0" (
  echo apiKey not assigned
  exit
)

if "%local%" == "local" (
  SET server=https://localhost:7086/api/Wasm/Upload/
  ) else (
  SET server=https://www.d1ag0n.com/api/Wasm/Upload/
)

REM echo Building...
REM -fno-inline -nostdlib -nostdlibinc -nostdinc -nostdinc++  -fno-builtin
clang main.c -fno-inline -I header --target=wasm32-unknown-unknown -Wl,-z,stack-size=65536 ^
--optimize=3 -nostdlib -nostdlibinc -nostdinc -nostdinc++  -fno-builtin ^
-Wl,--no-entry -Wl,--export-all -Wl,--error-limit=0 ^
-Wl,--allow-undefined --wasm-opt --output main.wasm

if %ERRORLEVEL% == 0 (
  REM echo Uploading...
  if "%local%" == "local" (
    curl -k --fail -F "data=@./main.wasm" "%server%%apiKey%%"
    ) else (
    curl --fail -F "data=@./main.wasm" "%server%%apiKey%%"
  )
  ) else (
  echo Build failed
  exit
)

if %ERRORLEVEL% == 0 (
  echo.
  echo main.wasm uploaded to %server%
  rm main.wasm
) else (
  echo main.wasm upload failed
)
