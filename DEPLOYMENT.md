# 🚀 Stock Manager - Deployment Guide

## Overview

Stock Manager is a WebAssembly-based inventory management application. The compiled WASM files and HTML are located in the `docs/` directory, ready for deployment to any static hosting service.

## Deployment Options

### Option 1: GitHub Pages (Recommended for Assignments)

1. **Ensure you have Emscripten installed:**
   ```bash
   # Follow: https://emscripten.org/docs/getting_started/downloads.html
   ```

2. **Build the project:**
   - **On Mac/Linux:**
     ```bash
     chmod +x build.sh
     ./build.sh
     ```
   - **On Windows (PowerShell):**
     ```powershell
     Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
     .\build.ps1
     ```

3. **Push to GitHub:**
   ```bash
   git add docs/
   git commit -m "Build: Update WASM and frontend"
   git push origin main
   ```

4. **Enable GitHub Pages:**
   - Go to repository **Settings** → **Pages**
   - Select **Deploy from a branch**
   - Choose **main** branch, `/docs` folder
   - Click Save

5. **Your site will be live at:**
   ```
   https://<your-username>.github.io/<repository-name>
   ```

### Option 2: Netlify (One-Click Deployment)

1. Build the project locally (see Option 1, step 2)
2. Push to GitHub
3. Go to [netlify.com](https://netlify.com)
4. Click "New site from Git"
5. Select your repository
6. Set build command to: (leave empty, files are pre-built)
7. Set publish directory to: `docs`
8. Deploy!

### Option 3: Vercel

1. Push your code to GitHub
2. Go to [vercel.com](https://vercel.com)
3. Click "Import Project"
4. Select your repository
5. Set **Output Directory** to `docs`
6. Deploy!

### Option 4: Traditional Web Hosting (Apache, Nginx, etc.)

1. Build locally using `build.ps1` or `build.sh`
2. Upload the `docs/` folder contents to your web server's public directory
3. Ensure your server serves `.wasm` files with proper MIME type:

   **For Apache (.htaccess):**
   ```apache
   AddType application/wasm .wasm
   ```

   **For Nginx (nginx.conf):**
   ```nginx
   types {
       application/wasm wasm;
   }
   ```

### Option 5: Local Testing

Test the application locally before deployment:

```bash
# Using Python 3
python -m http.server --directory docs 8000

# Using Node.js
npx http-server docs

# Using PHP
php -S localhost:8000 -t docs
```

Then open: `http://localhost:8000`

## Rebuilding After Changes

If you modify `main.c`, rebuild with:

**Windows:**
```powershell
.\build.ps1
```

**Mac/Linux:**
```bash
./build.sh
```

Then commit and push the changes to update your live deployment.

## Troubleshooting

### WASM files fail to load
- Ensure `.wasm` files are served with correct MIME type: `application/wasm`
- Check browser console (F12) for detailed error messages
- Verify CORS headers if hosting on a subdomain

### "WASM Engine not ready" error
- Check if `stock.wasm` is in the same directory as `index.html`
- Check browser console for loading errors
- Ensure files have the correct permissions (readable)

### GitHub Pages shows 404
- Verify `/docs` folder exists and contains `index.html`
- Check repository Settings → Pages configuration
- Wait a few minutes after enabling Pages (first build takes time)

## Production Checklist

- ✅ Run `build.ps1` or `build.sh` to ensure latest build
- ✅ Test locally at `http://localhost:8000`
- ✅ Verify all functions work in browser DevTools Console
- ✅ Commit and push all changes
- ✅ Verify deployment started (check GitHub Actions or hosting platform)
- ✅ Test the live URL in different browsers
- ✅ Check mobile responsiveness (Ctrl+Shift+M in Chrome)

## Browser Compatibility

- ✅ Chrome 74+
- ✅ Firefox 79+
- ✅ Safari 14+
- ✅ Edge 79+

## Security Notes

- The application runs entirely in the browser (client-side)
- No data is sent to external servers
- Inventory data is stored temporarily in browser memory (lost on refresh)
- To persist data, modify `main.c` to use IndexedDB or localStorage

---

**Need help?** Check the main [README.md](../README.md) or open an issue on GitHub!
