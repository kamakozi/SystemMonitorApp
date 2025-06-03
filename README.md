# System Monitor App

A modern C++ Qt6-based desktop application that monitors and displays real-time **system information** such as CPU usage, memory consumption, and running processes — designed with a clean UI and modular backend.

> In development – stay tuned for updates!
---

##  Features (Planned and In Progress)

### Current (Working)
- Qt6 GUI with login and register functionality
- User system with secure registration & login (hashed passwords using **bcrypt**)
- PostgreSQL database integration via **libpqxx**
- Responsive layout using `QBoxLayout`
- Modular design: `LoginWindow`, `RegisterWindow`, `MainWindow`, `User` class, etc.
- Singleton-based DB connection with `.env` reader
- Tables auto-load from SQL file (`Tables.sql`) on app start

### In Progress
- Real-time system usage monitoring (CPU, RAM, GPU, Network)
- Main window layout with sidebar buttons for switching graphs
- Graph plotting per module (CPU, RAM, etc.) using separate widgets
- Folder/module structure for each system section (`CPUWidget`, `RAMWidget`, ...)

### Coming Soon
- Running process list with kill/suspend buttons
- Search/filter tasks
- Dark/light theme toggle
- License key checking (offline mode)
- Session logging

---

##  Built With

- **C++17**
- **Qt6 Widgets**
- **CMake**
- **PostgreSQL + libpqxx**
- **bcrypt** (C++ header-only version)
- (Planned) System APIs for:
  - macOS: `sysctl`, `task_info`, etc.
  - Linux: `/proc`, `sysinfo`, etc.

---

##  How to Run

### 1. Install Dependencies (macOS example)

```bash
brew install qt cmake libpqxx openssl
```

### 2. Build the project

```bash
cmake -B build -S .
cmake --build build
./build/SystemMonitorApp
```

### 3. Optional: Run with Admin Privileges (for full access to system info)

```bash
sudo ./build/SystemMonitorApp
```

---

## Project Structure

```
SystemMonitorApp/
├── FrontEnd/
│   ├── LogInWindow/
│   ├── RegisterWindow/
│   ├── MainWindowUser/
│   ├── CPU/ (planned)
│   ├── RAM/ (planned)
│   └── ...
├── BackEnd/
│   ├── Auth/ (Login, Register, User, bcrypt)
│   ├── Tables/ (SQL loader)
│   └── PQXXConnection/ (singleton + env reader)
└── CMakeLists.txt
```

---

## Ideas for Future

- Chart visualization (CPU & RAM usage)
- Task killer with confirmation popup
- Session logging
- Cross-platform support (macOS & Linux)
- Qt Quick (QML) UI version
- User system with registration & license validation (offline & online mode)

---

_Last updated: 03.06.2025_
