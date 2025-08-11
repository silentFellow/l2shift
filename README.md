# l2shift

**l2shift** is a lightweight and fast command-line tool written in c for spoofing Layer 2 MAC addresses on Linux and macOS systems.
It allows you to quickly change the MAC address of a network interface, either to a custom value or a randomly generated one.
Windows support is planned for a future update.

---

## ✨ Features

- Change your MAC address instantly.
- Supports both **Linux** and **macOS**.
- Random MAC generation if no custom MAC is provided.
- Simple and minimal interface (no complex flags).
- Works without additional dependencies on most systems.

---

## 📦 Compatibility

| OS      | Status       |
| ------- | ------------ |
| Linux   | ✅ Supported |
| macOS   | ✅ Supported |
| Windows | 🚧 Planned   |

---

## 📂 Binaries

Precompiled binaries are available in the [`binary/`](binary/) folder.
No installation is required — simply download and run.

---

## 🚀 Usage

### **Basic syntax**

```bash
sudo l2shift <interface_name> [custom_mac]
```

### **Examples**

- Change to a random MAC:

```bash
sudo l2shift wlo1
```

- Change to a custom MAC:

```bash
sudo l2shift wlo1 02:1A:3C:4B:5D:6E
```

- Show help:

```bash
l2shift -h
```

- Show version:

```bash
l2shift -v
```

---

## 📥 Installation

### **1. Run from prebuilt binary**

```bash
# Make it executable
chmod +x binary/l2shift_{{os}}

# Move to a directory in PATH (optional)
sudo mv binary/l2shift_({os)} /usr/bin/l2shift

# Run
sudo l2shift wlo1
```

---

### **2. Build from source**

```bash
# Clone the repo
git clone https://github.com/yourusername/l2shift.git
cd l2shift

# Compile
clang src/l2shift.c -o l2shift

# (Optional) Move binary to PATH
sudo mv l2shift /usr/bin

# Run
sudo l2shift wlo1
```

---

## ⚠️ Notes

- **Root privileges** are required to change MAC addresses.
- On macOS, `ifconfig` is used.
- On linux, native syscalls are used for MAC address changes — no external tools required.
- Changing your MAC address may disconnect you temporarily from the network.
- Some network managers may reset the MAC on reconnect — disable MAC randomization in your network settings if needed.
- Use responsibly; spoofing MAC addresses may violate local laws or network policies.

---

## 📜 License

MIT License — feel free to use and modify.

---

## 🔮 Roadmap

- [ ] Windows support
- [ ] Persistent MAC change option
- [ ] Restore original MAC feature
