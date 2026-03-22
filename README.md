# 📦 Stock Manager

A professional **Multi-Role Inventory Management System** written in C with a beautiful WebAssembly web interface. Designed for supermarkets and retail chains with separate dashboards for Owners and Cashiers.

![Status](https://img.shields.io/badge/status-production%20ready-brightgreen)
![License](https://img.shields.io/badge/license-MIT-blue)
![Platform](https://img.shields.io/badge/built%20with-C%20%2B%20WebAssembly-orange)

### 🚀 [Live Demo on Vercel](https://stock-manager.vercel.app/)
*(Note: If you are deploying yourself, replace this URL with your actual Vercel project link)*

## ✨ Features

### 👑 Owner Dashboard
- ✅ **Multi-Shop Management** - Control inventory across multiple locations
- ✅ **Profit Analytics** - Track revenue and performance per shop
- ✅ **Bulk Ordering** - Place orders for restocking across locations
- ✅ **Expired Item Removal** - System-wide expired product management
- ✅ **Comprehensive Reports** - Detailed analytics and business insights
- ✅ **Real-time Alerts** - Low stock and expiration notifications

### 🛒 Cashier Terminal
- ✅ **Point-of-Sale System** - Fast checkout with barcode scanning
- ✅ **Real-time Stock Updates** - Automatic inventory reduction on sales
- ✅ **Receipt Generation** - Professional itemized receipts
- ✅ **Product Search** - Quick lookup by name or barcode
- ✅ **Sales Tracking** - Transaction history and reporting

### 🔧 Core Features
- ✅ **Add/Edit/Delete Products** - Complete product database management
- ✅ **Stock Management** - Increase/decrease inventory quantities
- ✅ **Real-time Calculations** - Automatic total value computation
- ✅ **Low Stock Alerts** - Visual warnings for items below threshold
- ✅ **Responsive Design** - Works on desktop, tablet, and mobile
- ✅ **Input Validation** - Robust error handling and user feedback
- ✅ **Role-Based Access** - Separate interfaces for different user types

## 🌍 Deployment Options

### Option 1: Vercel (Recommended)
1. Push your code to GitHub.
2. Go to vercel.com and click **Import Project**.
3. Select your repository.
4. Set **Output Directory** to `docs`.
5. Deploy!

### Option 2: GitHub Pages
1. Build the project locally and push to your main branch.
2. Go to your repository **Settings** → **Pages**.
3. Select **Deploy from a branch**.
4. Choose the **main** branch, and the `/docs` folder.
5. Click Save. Your site will be live in 1-2 minutes!

## 🚀 Local Development Quick Start

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
├── index.html                  # Role selection page
├── owner.html                  # Owner dashboard interface
├── cashier.html                # Cashier POS interface
├── build.sh                    # Linux/macOS build script
├── build.ps1                   # Windows PowerShell build script
├── QUICK_START.md              # Quick start guide
├── docs/
│   ├── index.html             # Production HTML (legacy)
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

### For Owners
1. **Daily Operations**: Check alerts, review profit summaries, place bulk orders
2. **Multi-Shop Management**: Switch between locations to manage inventory
3. **Analytics**: Use reports to track performance and make business decisions
4. **Stock Control**: Remove expired items and monitor low-stock alerts

### For Cashiers
1. **Quick Checkout**: Use barcode scanning or product search for fast transactions
2. **Stock Awareness**: Check available quantities during sales
3. **Receipts**: Generate professional receipts for customers
4. **Accuracy**: System automatically updates stock levels after each sale

### General Tips
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

## 📝 Project Features

This project demonstrates:

### 👑 Owner Dashboard Features
1. **Multi-Shop Inventory Management**
   - Cross-location inventory visibility
   - Shop-specific stock tracking
   - Bulk operations across locations

2. **Business Analytics**
   - Profit tracking per shop
   - Performance metrics
   - Sales analytics and reporting

3. **Advanced Operations**
   - Bulk ordering system
   - Expired item management
   - Alert system for critical issues

### 🛒 Cashier Terminal Features
1. **Point-of-Sale System**
   - Product search and selection
   - Barcode scanning support
   - Real-time cart management

2. **Transaction Processing**
   - Automatic stock updates
   - Receipt generation
   - Payment processing interface

### 🔧 Technical Implementation
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
   - Role-based user interfaces

3. **Software Engineering**
   - Clean code organization
   - Error handling
   - User experience design
   - Multi-role system architecture
   - Documentation

## 📄 License

MIT License - See [LICENSE](LICENSE) file for details

## 🎓 Use Cases

This project is perfect for:
- **Supermarket Chains** - Multi-location inventory management
- **Retail Stores** - Point-of-sale and stock tracking
- **Small Businesses** - Complete inventory control system
- **Educational Projects** - Learning C, WebAssembly, and web development
- **Portfolio Projects** - Showcasing full-stack development skills

### Target Users
- **Business Owners**: Comprehensive business management tools
- **Store Managers**: Daily operations and analytics
- **Cashiers**: Efficient point-of-sale operations
- **Students**: Learning enterprise software development
- **Developers**: Understanding WebAssembly and role-based systems

## 📞 Support

- **Questions?** Check the [DEPLOYMENT.md](DEPLOYMENT.md) guide
- **Issues?** Open an issue on GitHub
- **Local testing?** See "Quick Start" section above

---

<div align="center">

**Built with ❤️ for students and developers**

[View Live Demo](docs/) | [Source Code](main.c) | [Deployment Guide](DEPLOYMENT.md)

</div>
