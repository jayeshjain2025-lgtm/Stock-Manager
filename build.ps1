# Stock Manager Build Script (PowerShell)
# Builds the C code to WebAssembly

Write-Host "🔨 Building Stock Manager to WebAssembly..." -ForegroundColor Cyan

# Check if emcc is available
$emcc = Get-Command emcc -ErrorAction SilentlyContinue
if ($null -eq $emcc) {
    Write-Host "❌ Error: Emscripten (emcc) not found!" -ForegroundColor Red
    Write-Host "📖 Install Emscripten from: https://emscripten.org/docs/getting_started/downloads.html" -ForegroundColor Yellow
    exit 1
}

# Create docs directory if it doesn't exist
if (-not (Test-Path "docs")) {
    New-Item -ItemType Directory -Path "docs" | Out-Null
}

# Compile C to WebAssembly
Write-Host "⏳ Compiling main.c to WebAssembly..." -ForegroundColor Cyan
$exportedFunctions = "'_malloc', '_free', '_add_product', '_get_product_count', '_get_product_id', '_get_product_name', '_get_product_price', '_get_product_quantity', '_update_product_stock', '_delete_product_by_id', '_get_total_value'"
& emcc main.c `
    -O2 `
    -sALLOW_MEMORY_GROWTH=1 `
    "-sEXPORTED_FUNCTIONS=[$exportedFunctions]" `
    -sEXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" `
    --no-entry `
    -o docs/stock.js

if ($LASTEXITCODE -ne 0) {
    Write-Host "❌ Compilation failed!" -ForegroundColor Red
    exit 1
}

# Copy the updated HTML files
Write-Host "📋 Copying HTML files..." -ForegroundColor Cyan
Copy-Item index.html docs/index.html -Force
Copy-Item owner.html docs/owner.html -Force
Copy-Item cashier.html docs/cashier.html -Force

Write-Host "✅ Build complete!" -ForegroundColor Green
Write-Host "📁 Output directory: ./docs" -ForegroundColor Green
Write-Host "🌐 Ready to deploy to GitHub Pages or any static host" -ForegroundColor Green
Write-Host ""
Write-Host "📝 To test locally, serve the docs folder:" -ForegroundColor Yellow
Write-Host "   python -m http.server --directory docs 8000" -ForegroundColor Yellow
Write-Host "   Or use: npx http-server docs" -ForegroundColor Yellow
