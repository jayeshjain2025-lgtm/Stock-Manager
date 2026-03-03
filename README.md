# Stock Manager (C + Interactive Web UI + WASM-ready)

Stock Manager now includes:

- A **C implementation** (`main.c`) for course requirements.
- A modern **interactive frontend** (`docs/index.html`) for GitHub Pages demos.
- A CI workflow that also builds the C source to **WebAssembly artifacts** under `docs/wasm/`.

## Inventory Features

- Add product (`ProductID`, `Name`, `Price`, `Quantity`)
- Update stock (purchase/sale)
- Delete a product
- Search by Product ID
- Save/load from file:
  - C app: `inventory.txt`
  - Web UI: JSON import/export + localStorage autosave
- Low-stock report (items below threshold)
- Total inventory value `Σ(price × quantity)`

## C Concepts Covered (in `main.c`)

- Menu-driven app with `switch/case`
- 5+ user-defined functions
- `struct Product`
- File handling (save/load)
- Input validation and range checks

## Run the Interactive Frontend (recommended)

Open `docs/index.html` in a browser, or serve the `docs/` directory:

```bash
python3 -m http.server 8080 --directory docs
```

Then open `http://localhost:8080`.

## Run C Program Locally (Native)

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o stock_manager
./stock_manager
```

## Run on Windows

### Option 1: MSYS2 + MinGW-w64 GCC (recommended)

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc
gcc -std=c11 -Wall -Wextra -pedantic main.c -o stock_manager.exe
./stock_manager.exe
```

### Option 2: Visual Studio Developer Command Prompt (MSVC)

```bat
cl /W4 /EHsc main.c /Fe:stock_manager.exe
stock_manager.exe
```

## WebAssembly Build (manual)

```bash
emcc main.c -O2 -sALLOW_MEMORY_GROWTH=1 -sEXIT_RUNTIME=1 -o docs/wasm/stock.js
```

## GitHub Pages Deployment

Workflow: `.github/workflows/deploy-pages.yml`

- Installs Emscripten
- Builds `main.c` into `docs/wasm/`
- Deploys `docs/` (frontend + wasm artifacts) to GitHub Pages
