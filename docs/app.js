const KEY = "stock_manager_inventory_v1";
let inventory = [];
let selectedProductId = null;
let threshold = 5;

const el = (id) => document.getElementById(id);
const money = (n) => `$${n.toFixed(2)}`;

function showToast(message, good = true) {
  const t = el("toast");
  t.textContent = message;
  t.style.borderColor = good ? "#10b981" : "#ef4444";
  t.classList.add("show");
  setTimeout(() => t.classList.remove("show"), 1800);
}

function saveLocal() {
  localStorage.setItem(KEY, JSON.stringify(inventory));
}

function loadLocal() {
  try {
    const data = JSON.parse(localStorage.getItem(KEY) || "[]");
    if (Array.isArray(data)) inventory = data;
  } catch {
    inventory = [];
  }
}

function findIndex(productId) {
  return inventory.findIndex((p) => p.productId === productId);
}

function validateProduct(productId, name, price, quantity) {
  if (!Number.isInteger(productId) || productId < 1) return "Invalid Product ID.";
  if (!name.trim()) return "Name is required.";
  if (!Number.isFinite(price) || price <= 0) return "Price must be > 0.";
  if (!Number.isInteger(quantity) || quantity < 0) return "Quantity must be >= 0.";
  return null;
}

function renderStats() {
  const totalUnits = inventory.reduce((a, p) => a + p.quantity, 0);
  const totalValue = inventory.reduce((a, p) => a + p.quantity * p.price, 0);
  const low = inventory.filter((p) => p.quantity < threshold).length;

  el("statCount").textContent = String(inventory.length);
  el("statUnits").textContent = String(totalUnits);
  el("statValue").textContent = money(totalValue);
  el("statLow").textContent = String(low);
}

function renderTable() {
  const body = el("inventoryBody");
  body.innerHTML = "";

  const sorted = [...inventory].sort((a, b) => a.productId - b.productId);
  for (const p of sorted) {
    const tr = document.createElement("tr");
    tr.innerHTML = `
      <td>${p.productId}</td>
      <td>${p.name}</td>
      <td>${money(p.price)}</td>
      <td>${p.quantity}</td>
      <td>${money(p.price * p.quantity)}</td>
    `;
    body.appendChild(tr);
  }
}

function renderLowStock() {
  const list = el("lowList");
  list.innerHTML = "";
  const lowItems = inventory.filter((p) => p.quantity < threshold);
  if (!lowItems.length) {
    const li = document.createElement("li");
    li.textContent = "No low-stock items.";
    li.className = "muted";
    list.appendChild(li);
    return;
  }

  for (const p of lowItems) {
    const li = document.createElement("li");
    li.textContent = `ID ${p.productId} - ${p.name} (Qty ${p.quantity})`;
    list.appendChild(li);
  }
}

function renderAll() {
  saveLocal();
  renderStats();
  renderTable();
  renderLowStock();
}

el("addForm").addEventListener("submit", (e) => {
  e.preventDefault();
  const productId = Number(el("productId").value);
  const name = el("productName").value;
  const price = Number(el("productPrice").value);
  const quantity = Number(el("productQty").value);

  const error = validateProduct(productId, name, price, quantity);
  if (error) return showToast(error, false);
  if (findIndex(productId) !== -1) return showToast("Product ID already exists.", false);

  inventory.push({ productId, name: name.trim(), price, quantity });
  e.target.reset();
  renderAll();
  showToast("Product added.");
});

el("stockForm").addEventListener("submit", (e) => {
  e.preventDefault();
  const productId = Number(el("stockProductId").value);
  const type = el("stockType").value;
  const amount = Number(el("stockAmount").value);

  if (!Number.isInteger(productId) || productId < 1) return showToast("Invalid Product ID.", false);
  if (!Number.isInteger(amount) || amount < 1) return showToast("Amount must be >= 1.", false);

  const idx = findIndex(productId);
  if (idx === -1) return showToast("Product not found.", false);

  if (type === "purchase") {
    inventory[idx].quantity += amount;
  } else {
    if (inventory[idx].quantity < amount) return showToast("Sale exceeds stock.", false);
    inventory[idx].quantity -= amount;
  }

  renderAll();
  showToast("Stock updated.");
});

el("searchForm").addEventListener("submit", (e) => {
  e.preventDefault();
  const productId = Number(el("searchId").value);
  const idx = findIndex(productId);
  if (idx === -1) {
    selectedProductId = null;
    el("searchResult").textContent = "Product not found.";
    return showToast("Product not found.", false);
  }

  selectedProductId = productId;
  const p = inventory[idx];
  el("searchResult").textContent = `Found: ID=${p.productId}, ${p.name}, Price=${money(p.price)}, Qty=${p.quantity}`;
  showToast("Product found.");
});

el("deleteBtn").addEventListener("click", () => {
  if (selectedProductId == null) return showToast("Search a product first.", false);
  const idx = findIndex(selectedProductId);
  if (idx === -1) return showToast("Product no longer exists.", false);

  const [removed] = inventory.splice(idx, 1);
  selectedProductId = null;
  el("searchResult").textContent = "No product selected.";
  renderAll();
  showToast(`Deleted ${removed.name}.`);
});

el("lowForm").addEventListener("submit", (e) => {
  e.preventDefault();
  const value = Number(el("threshold").value);
  if (!Number.isInteger(value) || value < 0) return showToast("Threshold must be >= 0.", false);
  threshold = value;
  renderAll();
  showToast("Threshold updated.");
});

el("saveFileBtn").addEventListener("click", () => {
  const blob = new Blob([JSON.stringify(inventory, null, 2)], { type: "application/json" });
  const url = URL.createObjectURL(blob);
  const a = document.createElement("a");
  a.href = url;
  a.download = "inventory.json";
  a.click();
  URL.revokeObjectURL(url);
  showToast("Exported inventory.json");
});

el("loadFileInput").addEventListener("change", async (e) => {
  const file = e.target.files?.[0];
  if (!file) return;
  try {
    const text = await file.text();
    const data = JSON.parse(text);
    if (!Array.isArray(data)) throw new Error("Invalid format");
    for (const p of data) {
      const err = validateProduct(p.productId, p.name, p.price, p.quantity);
      if (err) throw new Error(err);
    }
    inventory = data;
    renderAll();
    showToast("Inventory imported.");
  } catch (err) {
    showToast(`Import failed: ${err.message}`, false);
  } finally {
    e.target.value = "";
  }
});

el("resetBtn").addEventListener("click", () => {
  if (!confirm("Clear all inventory data?")) return;
  inventory = [];
  selectedProductId = null;
  renderAll();
  showToast("Inventory reset.");
});

loadLocal();
renderAll();
