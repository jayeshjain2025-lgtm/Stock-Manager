# Stock Manager (C + WASM)

A menu-driven **Inventory Management System** written in C for a small shop.

## Features

- Add product (`ProductID`, `Name`, `Price`, `Quantity`)
- Update stock for purchase/sale
- Delete a product
- Search by `ProductID`
- Save/load inventory from file
- Low-stock report (items below a threshold)
- Total inventory value `Σ(price × quantity)`

## Required C Concepts Covered

- `switch/case` menu program
- 10+ user-defined functions
- `struct Product`
- File handling (`inventory.txt`)
- Input validation with robust parsing/range checks

## Run Locally (Native)

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o stock_manager
./stock_manager
```

## Run on Windows

### Option 1: MSYS2 + MinGW-w64 GCC (recommended)

1. Install MSYS2 from: https://www.msys2.org/
2. Open **MSYS2 UCRT64** terminal.
3. Install GCC:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc
```

4. Build and run:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o stock_manager.exe
./stock_manager.exe
```

### Option 2: Visual Studio Developer Command Prompt (MSVC)

1. Install **Visual Studio** (or Build Tools) with C++ workload.
2. Open **x64 Native Tools Command Prompt for VS** in this project folder.
3. Build and run:

```bat
cl /W4 /EHsc main.c /Fe:stock_manager.exe
stock_manager.exe
```

## Data File Location

- The app reads/writes `inventory.txt` in the **current working directory**.
- On Windows, run the program from the project folder if you want `inventory.txt` saved there.

## Build for WebAssembly (Emscripten)

```bash
emcc main.c -O2 -sALLOW_MEMORY_GROWTH=1 -sEXPORTED_FUNCTIONS="['_malloc', '_free']" -sEXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" --no-entry -o docs/stock.js
```

Then serve `docs/` with any static server, or enable GitHub Pages from the `gh-pages` artifact via Actions (workflow included below).

## GitHub Pages Deployment (WASM)

This repository includes `.github/workflows/deploy-pages.yml`.

- It installs Emscripten
- Builds `main.c` to WebAssembly output in `docs/`
- Uploads and deploys to GitHub Pages

> After pushing to `main`, enable **Pages** in repository settings to use **GitHub Actions** as the source.
