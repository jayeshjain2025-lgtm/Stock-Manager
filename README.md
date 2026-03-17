# 📦 Stock Manager

A professional **Inventory Management System** written in C with a beautiful WebAssembly web interface. Perfect for managing products, stock levels, and inventory values.

![Status](https://img.shields.io/badge/status-production%20ready-brightgreen)
![License](https://img.shields.io/badge/license-MIT-blue)
![Platform](https://img.shields.io/badge/built%20with-C%20%2B%20WebAssembly-orange)

## ✨ Features

- ✅ **Add/Edit/Delete Products** - Manage product database with ID, name, price, quantity
- ✅ **Stock Management** - Increase/decrease inventory quantities easily
- ✅ **Real-time Calculations** - Automatic total inventory value calculation
- ✅ **Low Stock Alerts** - Visual warnings for items below threshold (< 5 units)
- ✅ **Search by ID** - Quick product lookup
- ✅ **Responsive Design** - Works on desktop, tablet, and mobile
- ✅ **Input Validation** - Robust error handling and user feedback
- ✅ **Fast Performance** - WebAssembly-based backend for native speed

## 📋 Required C Concepts

- ✓ `switch/case` control structures
- ✓ 10+ user-defined functions
- ✓ `struct Product` - Complex data structure
- ✓ Dynamic arrays and memory management
- ✓ Input validation with robust error handling
- ✓ Total inventory calculations

## 🚀 Quick Start

### Online Demo (No Installation Required)

Visit the live deployment: [GitHub Pages Link](docs/)

Just open `docs/index.html` in your browser!

### Local Development

#### Prerequisites
- Emscripten toolchain
- A C compiler (gcc or clang)
- Node.js or Python (for local server)

#### Build & Run Web Version

**Windows (PowerShell):**
```powershell
.\build.ps1
python -m http.server --directory docs 8000
# Open browser to http://localhost:8000
```

**macOS/Linux:**
```bash
chmod +x build.sh
./build.sh
python3 -m http.server --directory docs 8000
# Open browser to http://localhost:8000
```

#### Run Native Version

```bash
# Linux/macOS
gcc -std=c11 -Wall -Wextra -pedantic main.c -o stock_manager
./stock_manager

# Windows (with MinGW or MSYS2)
gcc -std=c11 -Wall -Wextra -pedantic main.c -o stock_manager.exe
stock_manager.exe

# Windows (Visual Studio Command Prompt)
cl /W4 /EHsc main.c /Fe:stock_manager.exe
stock_manager.exe
```

## 📁 Project Structure

```
Stock-Manager/
├── main.c                      # C implementation with WASM exports
├── index.html                  # Original HTML (for reference)
├── build.sh                    # Linux/macOS build script
├── build.ps1                   # Windows PowerShell build script
├── docs/
│   ├── index.html             # Production HTML (deployed)
│   ├── stock.js               # WebAssembly interface
│   ├── stock.wasm             # Compiled C code
│   └── .nojekyll              # GitHub Pages config
├── README.md                   # This file
├── DEPLOYMENT.md              # Detailed deployment guide
└── inventory.txt              # Data file (auto-generated)
```

## 🌐 Deployment

### GitHub Pages (Recommended)

1. Build the project:
   - Windows: `.\build.ps1`
   - Mac/Linux: `./build.sh`

2. Commit and push:
   ```bash
   git add docs/
   git commit -m "Build: Update WASM and frontend"
   git push origin main
   ```

3. Enable in GitHub:
   - Settings → Pages
   - Source: main branch, /docs folder
   - Save

4. Access your site at: `https://<username>.github.io/<repo-name>`

### Other Hosting Options

- **Netlify** - Connect GitHub repo, set publish dir to `docs`
- **Vercel** - Similar to Netlify
- **Traditional Hosting** - Upload `docs/` folder via FTP/SSH

📖 **See [DEPLOYMENT.md](DEPLOYMENT.md) for detailed instructions**

## 🎨 User Interface

The modern, responsive interface includes:

- 🎨 Professional gradient design
- 📱 Mobile-first responsive layout
- ⚡ Real-time updates
- 🔔 User-friendly notifications
- 🎯 Accessible color scheme
- 🌙 Clear visual hierarchy

### Screenshots

**Add Product Form:**
- Clean, organized input layout
- Real-time validation feedback
- Helpful placeholders and labels

**Inventory Table:**
- Sortable columns
- Low-stock highlighting
- Quick +/- quantity buttons
- Delete functionality

**Statistics Display:**
- Total product count
- Total inventory value
- Live updates

## 💡 Usage Tips

1. **Product ID**: Use unique IDs for each product (e.g., 101, 102, 103)
2. **Stock Operations**: Use +/- buttons to adjust quantities for sales and purchases
3. **Low Stock Alert**: Items with < 5 units are highlighted in yellow
4. **Total Value**: Automatically calculated as Σ(Price × Quantity)
5. **Error Handling**: All errors are displayed with clear messages

## 🔧 Technology Stack

| Component | Technology |
|-----------|------------|
| Backend | C with Emscripten |
| Frontend | HTML5, CSS3, Vanilla JavaScript |
| Runtime | WebAssembly (WASM) |
| Styling | Modern CSS Grid & Flexbox |
| Deployment | Static hosting (GitHub Pages, Netlify, etc.) |

## 📦 Build Commands

### Quick Build
```bash
# Windows
.\build.ps1

# macOS/Linux
./build.sh
```

### Manual Build (if scripts don't work)
```bash
emcc main.c -O2 \
  -sALLOW_MEMORY_GROWTH=1 \
  -sEXPORTED_FUNCTIONS="['_malloc', '_free']" \
  -sEXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" \
  --no-entry \
  -o docs/stock.js

cp index.html docs/index.html
```

## 🐛 Troubleshooting

| Issue | Solution |
|-------|----------|
| "WASM Engine not ready" | Ensure stock.js and stock.wasm are in same directory |
| WASM fails to load | Check browser console (F12) for MIME type errors |
| Build fails | Verify Emscripten is installed: `emcc --version` |
| GitHub Pages 404 | Check Settings → Pages, verify /docs folder exists |

## 🔐 Security & Performance

- ✅ Runs entirely client-side (no server needed)
- ✅ No external API calls
- ✅ No data transmission
- ✅ Fast WebAssembly execution
- ✅ Instant UI responsiveness

**Note:** Inventory data is stored in browser memory. It will be lost on refresh. For persistence, implement IndexedDB or localStorage.

## 📝 Assignment Requirements

This project demonstrates:

1. **C Programming Concepts**
   - Struct-based data structures
   - Array manipulation
   - String handling
   - User input validation
   - Control flow (switch/case)

2. **Web Technology**
   - Responsive web design
   - Modern CSS3 features
   - JavaScript DOM manipulation
   - WebAssembly integration

3. **Software Engineering**
   - Clean code organization
   - Error handling
   - User experience design
   - Documentation
   - Deployment procedures

## 📄 License

MIT License - See [LICENSE](LICENSE) file for details

## 🎓 Educational Use

This project is perfect for:
- Learning C programming fundamentals
- Understanding WebAssembly compilation
- Web development with C backend
- Assignment submissions
- Portfolio projects

## 📞 Support

- **Questions?** Check the [DEPLOYMENT.md](DEPLOYMENT.md) guide
- **Issues?** Open an issue on GitHub
- **Local testing?** See "Quick Start" section above

---

<div align="center">

**Built with ❤️ for students and developers**

[View Live Demo](docs/) | [Source Code](main.c) | [Deployment Guide](DEPLOYMENT.md)

</div>
