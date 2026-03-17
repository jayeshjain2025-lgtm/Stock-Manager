# 📚 Quick Start Guide

## For Assignment Submission

### Option A: Local Testing (Recommended First)

1. **Prerequisites**
   - Any modern browser (Chrome, Firefox, Safari, Edge)
   - Python 3 installed (or Node.js)

2. **Run Locally**
   ```bash
   # Navigate to project folder
   cd Stock-Manager
   
   # Start a local server
   python -m http.server --directory docs 8000
   # Or if using Node.js:
   # npx http-server docs
   ```

3. **Open in Browser**
   ```
   http://localhost:8000
   ```

4. **Test the App**
   - Add a product (ID: 101, Name: "Laptop", Price: 999.99, Quantity: 5)
   - Click the +/- buttons to adjust stock
   - Watch the total value update in real-time
   - Delete a product
   - Refresh the browser (data resets - this is normal for development version)

### Option B: Deploy to GitHub Pages

1. **Install Emscripten** (if not already installed)
   - Visit: https://emscripten.org/docs/getting_started/downloads.html
   - Follow the installation guide for your OS

2. **Build the Project**
   ```bash
   # Windows (PowerShell)
   .\build.ps1
   
   # macOS/Linux
   chmod +x build.sh
   ./build.sh
   ```

3. **Commit and Push**
   ```bash
   git add docs/
   git commit -m "Build: Updated frontend and WASM"
   git push origin main
   ```

4. **Enable GitHub Pages**
   - Go to your repository on GitHub
   - Settings → Pages
   - Source: Deploy from a branch
   - Branch: main, Folder: /docs
   - Click Save
   - Wait 1-2 minutes for deployment

5. **Visit Your Live Site**
   ```
   https://<your-username>.github.io/<repository-name>
   ```

## Troubleshooting

### Problem: "WASM Engine not ready"
**Solution:** 
- Ensure you're running from a web server (http://localhost:8000), not a file:// URL
- Check browser console (F12 → Console tab) for errors

### Problem: "Cannot find stock.wasm"
**Solution:**
- Verify docs/ folder contains stock.wasm file
- Check that index.html is in the same docs/ folder

### Problem: Build fails with "emcc: command not found"
**Solution:**
- Emscripten is not installed or not in PATH
- Run: `emcc --version` to verify installation
- If not installed, follow https://emscripten.org/docs/getting_started/downloads.html

### Problem: GitHub Pages shows "404"
**Solution:**
- Wait 2-3 minutes after enabling Pages (first deployment takes time)
- Verify /docs folder exists and contains index.html
- Check Settings → Pages is enabled and correct branch/folder selected

## What's New

### Frontend Improvements
- ✨ Modern gradient design (purple/blue theme)
- 📱 Fully responsive (mobile, tablet, desktop)
- 🎨 Professional styling with better spacing
- ⚡ Real-time form validation
- 🔔 User-friendly notification system
- 📊 Enhanced statistics display
- 🎯 Better visual hierarchy
- ♿ Improved accessibility

### New Features
- Low stock warning badges
- Form validation with error highlights
- Success/error/warning messages
- Product count in header
- Total inventory value in statistics
- Improved table layout with full calculations
- Better quantity control buttons

### Code Quality
- Cleaner JavaScript with better error handling
- Responsive design that works on all devices
- Professional color scheme
- Smooth animations and transitions
- Better mobile experience

## File Structure

```
docs/                    ← Deploy this folder!
├── index.html          ← Web interface
├── stock.js            ← WASM interface
├── stock.wasm          ← Compiled C code
└── .nojekyll           ← GitHub Pages config
```

## Tips for Success

1. **Test Locally First**
   - Always test with `python -m http.server` before pushing
   - Check browser console (F12) for any errors

2. **Clear Browser Cache**
   - If updates don't show, press Ctrl+Shift+Delete (Windows) or Cmd+Shift+Delete (Mac)
   - Or use Ctrl+F5 (Windows) / Cmd+Shift+R (Mac)

3. **Mobile Testing**
   - Press F12 in Chrome/Firefox
   - Click the device icon to view mobile layout
   - Test on actual phone if possible

4. **Assignment Checklist**
   - ✅ Code compiles without errors
   - ✅ Web interface works in browser
   - ✅ All CRUD operations work (Add, Update, Delete)
   - ✅ Responsive design works on mobile
   - ✅ No console errors (F12 → Console)
   - ✅ Deployed to GitHub Pages
   - ✅ README.md is clear and comprehensive

## Next Steps

1. Read [DEPLOYMENT.md](../DEPLOYMENT.md) for advanced deployment options
2. Check [README.md](../README.md) for full project documentation
3. Review [main.c](../main.c) to understand the C implementation

---

**Good luck with your assignment! 🎉**
