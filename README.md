
# System Monitor App

A modern C++ Qt6-based desktop application that monitors and displays real-time **system information** such as CPU usage, memory consumption, and running processes — designed with a clean UI and modular backend.

> In development – stay tuned for updates!
---

##  Features (Planned and In Progress)

###  Current (Working)
- Qt6 GUI skeleton with login/start window
- Responsive layout using QBoxLayout
- Modular class-based design (`LogInWindow`, `MainWindow`...)

###  Coming Soon
- Real-time CPU and memory usage visualization
- Network statistics tracking
- Running process list with kill/suspend actions
- Search/filter tasks
- Dark/light theme toggle
- User registration & license key checking system

---

##  Built With

- **C++17**
- **Qt6 Widgets**
- **CMake**
- (Planned) **System APIs** for:
  - macOS: `sysctl`, `task_info`, etc.
  - Linux: `/proc`, `sysinfo`, etc.

---

##  How to Run

### 1. Install Dependencies (macOS example)

```bash
brew install qt cmake
```

### 2. Build the project

```bash
cmake -B build -S .
cmake --build build
./build/YourExecutableName
```

### 3. Optional: Run with Admin Privileges (for full access to system info)

```bash
sudo ./build/YourExecutableName
```

---

---

## Ideas for Future

- Chart visualization (CPU & RAM usage)
- Task killer with confirmation popup
- Session logging
- Cross-platform support (macOS & Linux)
- Qt Quick (QML) UI version
- User system with registration & license validation (offline & online mode)

---

