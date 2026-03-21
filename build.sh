#!/bin/bash
# Stock Manager Build Script
# Builds the C code to WebAssembly

set -e

echo "🔨 Building Stock Manager to WebAssembly..."

# Check if emcc is available
if ! command -v emcc &> /dev/null; then
    echo "❌ Error: Emscripten (emcc) not found!"
    echo "📖 Install Emscripten from: https://emscripten.org/docs/getting_started/downloads.html"
    exit 1
fi

# Create docs directory if it doesn't exist
mkdir -p docs

# Compile C to WebAssembly
emcc main.c \
    -O2 \
    -sALLOW_MEMORY_GROWTH=1 \
    -sEXPORTED_FUNCTIONS="['_malloc', '_free', '_add_product', '_get_product_count', '_get_product_id', '_get_product_name', '_get_product_price', '_get_product_quantity', '_update_product_stock', '_delete_product_by_id', '_get_total_value']" \
    -sEXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" \
    --no-entry \
    -o docs/stock.js

# Copy the updated HTML
cp index.html docs/index.html

echo "✅ Build complete!"
echo "📁 Output directory: ./docs"
echo "🌐 Ready to deploy to GitHub Pages or any static host"
echo ""
echo "📝 To test locally, serve the docs folder:"
echo "   python -m http.server --directory docs 8000"
echo "   Or use: npx http-server docs"
