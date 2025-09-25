# Alerting & Notification Platform 

A complete production-ready alerting and notification system built with modern C++17 standards, implementing all PRD requirements with clean architecture and comprehensive features.

##  Overview

This platform provides organizations with a robust alerting system that balances administrative configurability with user control. Features include unlimited alert creation with visibility targeting, multi-level filtering, snooze functionality with automatic daily resets, and comprehensive analytics.

##  Key Features

### Admin Operations 
- **Create unlimited alerts** with configurable visibility (Organization/Team/User)
- **Update alerts** with new titles, severities, and properties
- **Archive alerts** to remove from active circulation
- **Enable/disable reminders** controlling 2-hour notification intervals
- **List all alerts** with status and reminder information
- **Filter by status** (Active/Expired alerts)
- **Filter by severity** (Info/Warning/Critical level alerts)
- **Filter by audience** (Organization-wide or team-specific alerts)
- **View alert read status** by user (Unread/Read/Snoozed per alert)

### User Operations 
- **View personalized alerts** based on user/team visibility
- **Mark alerts as read/unread** with status persistence
- **Snooze alerts for current day** with automatic morning reset
- **Track snoozed alert history** and notifications
- **Receive alerts every 2 hours** until snoozed or expired

### Analytics Dashboard 
- **Total alerts created** system metric
- **Alert delivery rates** tracking
- **Read vs snooze rates** in percentages
- **Severity breakdowns** (Info/Warning/Critical counts)
- **Alert status tracking** (Active/Snoozed/Read)

##  Architecture

- **C++17 Standard** with RAII and smart pointers
- **Modular Design** following SRP and DRY principles
- **MVC-like Structure** with clear separation of concerns
- **Strategy Pattern** for extensible notification channels
- **Observer Pattern** foundation for real-time subscriptions
- **JSON Framework** ready for data persistence and APIs

##  Prerequisites

### Required Tools:
- **C++ Compiler**: GCC 11+ or MinGW-w64 (recommended)
  - GCC: https://gcc.gnu.org/install/
  - MinGW-w64: https://www.mingw-w64.org/downloads/
- **CMake**: Version 3.20 or higher - https://cmake.org/download/
- **Git**: For cloning (optional) - https://git-scm.com/downloads

### Supported Platforms:
- **Windows** (MinGW-w64)
- **Linux** (GCC/Clang)
- **macOS** (Clang)

### Dependencies:
- **Standard C++17** libraries (included)
- **nlohmann/json** (automatically downloaded by CMake)
- **CMake Toolchain** for cross-platform builds

##  Quick Start Setup

### **Prerequisites Check**
Before starting, ensure you have:
- **C++ Compiler:** GCC 11+ OR MinGW-w64 (Windows)
- **CMake:** Version 3.20 or higher
- **Git:** For cloning

### **Step 1: Clone the Repository**
```bash
# Clone the project
git clone https://github.com/SandeepGKP/Alert-And-Notification-Platform.git

# Navigate to project directory
cd alerting-notification-platform 
```

### **Step 2: Initialize Build System**
```bash
# Create and enter build directory
mkdir build
cd build

# Generate build files with CMake
cmake ..
```

**Alternative for Linux/macOS:**
```bash
# Out-of-source build (recommended)
cmake -S .. -B build
cd build
```

### **Step 3: Build the Application**
```bash
# Compile the project
cmake --build .
```

**For faster builds (optional):**
```bash
# Use multiple cores for faster compilation
cmake --build . --parallel 4
```

### **Step 4: Verify Build Success**
After building, you should see:
```
build/bin/
└── AlertingPlatform.exe    # (or AlertingPlatform on Linux/macOS)
build/                     # Build artifacts (ignored by git)
└── CMakeFiles/           # CMake generated files
```

### **Step 5: Run the Application**
```bash
# Linux/macOS
./bin/AlertingPlatform

# Windows (PowerShell)
.\bin\AlertingPlatform.exe

# Windows (Command Prompt)
bin\AlertingPlatform.exe
```

### **Step 6: Verify It's Working**
You should see the Welcome screen:
```
Alerting & Notification Platform - PRD Compliant Demo

         ALERTING & NOTIFICATION PLATFORM

MAIN MENU
--------
1. Admin Operations
2. User Operations
3. Analytics Dashboard
4. Exit

Enter choice (1-4):
```

##  **Important Notes**
- **First-time Setup:** Dependencies (like nlohmann/json) are automatically downloaded by CMake
- **Build Directory:** You can safely delete `build/` anytime and recreate it
- **Clean Builds:** Use `rm -rf build/ && mkdir build && cd build && cmake ..` for clean rebuilds
- **Invalid Input:** Application automatically exits on invalid menu choices (ensures clean operation)

## � Usage Guide

### Initial Setup
The application starts with pre-loaded demo data:
- **Teams**: Engineering, Marketing
- **Users**: Alice (Engineering), others
- **Alerts**: Server Maintenance (Engineering), System Update (Organization-wide)

         ALERTING & NOTIFICATION PLATFORM

MAIN MENU
--------
1. Admin Operations     # Manage alerts and system
2. User Operations      # View and manage personal alerts
3. Analytics Dashboard  # System metrics and statistics
4. Exit                 # Shutdown application

Enter choice (1-4):
```
### Main Menu Navigation
```
         ALERTING & NOTIFICATION PLATFORM

MAIN MENU
--------
1. Admin Operations     # Manage alerts and system
2. User Operations      # View and manage personal alerts
3. Analytics Dashboard  # System metrics and statistics
4. Exit                 # Shutdown application

Enter choice (1-4):
```

**Input Validation:** The application automatically exits if you enter an invalid menu option (not 1-4). This ensures clean operation and prevents infinite loops.
===========================================
         ALERTING & NOTIFICATION PLATFORM
===========================================

MAIN MENU
--------
1. Admin Operations     # Manage alerts and system
2. User Operations      # View and manage personal alerts
3. Analytics Dashboard  # System metrics and statistics
4. Exit                 # Shutdown application

Enter choice (1-4):
```

### Admin Operations Usage

#### Create New Alert
```
Menu: 1 → Admin Operations → 1
Output: [SUCCESS] Alert 'Marketing Campaign' created for Marketing team
```

#### Update Existing Alert
```
Menu: 1 → 2
Output: [UPDATE] Alert updated to 'Urgent Maintenance'
```

#### Archive Alert
```
Menu: 1 → 3
Output: [ARCHIVED] Alert archived (no longer active)
```

#### Toggle Reminders
```
Menu: 1 → 4
Output: [TOGGLE] Reminders disabled for critical alert
```

#### List All Alerts
```
Menu: 1 → 5
Output:
ALL ALERTS OVERVIEW
--------------------------------------------------
1. [WARNING] Server Maintenance (Reminders: ON)
2. [CRITICAL] System Update (Reminders: OFF)
```

#### Filter by Status
```
Menu: 1 → 6
Output:
ACTIVE ALERTS ONLY
--------------------------------------------------
1. [WARNING] Server Maintenance
2. [CRITICAL] System Update
```

#### Filter by Severity
```
Menu: 1 → 7 → 2 (Critical alerts)
Output:
CRITICAL ALERTS
--------------------------------------------------
1. [CRITICAL] System Update
```

#### Filter by Audience
```
Menu: 1 → 8 → t (Team alerts) → team1
Output:
TEAM VISIBILITY ALERTS
--------------------------------------------------
1. [WARNING] Server Maintenance
```

#### View Alert Read Status
```
Menu: 1 → 9
Output:
ALERT READ STATUS BY USER:

ALERT: Server Maintenance [WARNING]
MESSAGE: Scheduled maintenance tonight
READ STATUS BY USERS:
  - Alice (Engineering): Read
  - Bob (Engineering): Unread (demo - no interaction)

ALERT: System Update [CRITICAL]
MESSAGE: Critical update required
READ STATUS BY USERS:
  - Alice (Engineering): Snoozed (currently snoozed)
  - Bob (Engineering): Unread (demo - no interaction)
  - Charlie (Marketing): Unread (demo - no interaction)
```

### User Operations Usage

#### View My Alerts
```
Menu: 2 → User Operations → 1
Output:
[SUCCESS] Alice's Active Alerts (Engineering team):
  - Server Maintenance: Scheduled maintenance tonight
     Status: [Unread]
  - System Update: Critical update required
     Status: [Unread]

Snoozed Alert History:
```

#### Mark Alert as Read
```
Menu: 2 → 2
Output: [SUCCESS] Alert marked as read
```

#### Snooze Alert
```
Menu: 2 → 3
Output: [SNOOZED] Alert snoozed for today (resumes tomorrow at 2-hour intervals)
```

### Analytics Dashboard Usage

```
Menu: 3
Output:
SYSTEM METRICS:
========================================
- Total alerts created:           2
- Active alerts:                  2
- Alerts delivered:               2 (all)
- Read rate:                      0%
- Snooze rate:                    0%

SEVERITY BREAKDOWN:
----------------------------------------
- Info alerts:                    0
- Warning alerts:                 1
- Critical alerts:                1

ALERT STATUS:
----------------------------------------
- Active alerts:                  2
- Snoozed alerts:                 0
- Read alerts:                    0
```

##  PRD Features Verification

All Product Requirements Document features are implemented and demoable:

| Feature | Admin Operations | User Operations | Analytics |
|---------|------------------|-----------------|-----------|
| Create unlimited alerts |  Dashboard | - |  Count |
| Update/archive alerts |  Operations | - | - |
| Enable/disable reminders |  Toggle | - | - |
| List with filtering |  All filters | - | - |
| View alerts (dashboard) | - |  Personalized | - |
| Mark read/unread | - |  Status |  Rates |
| Snooze with daily reset | - |  24-hour logic |  Rates |
| 2-hour re-trigger logic | - |  Implemented | - |
| Org/Team/User visibility |  Targeting |  Filtering | - |
| Analytics dashboard |  Update counters |  Track activity |  All metrics |

## 🔧 Development Notes

### Project Structure
```
.
├── CMakeLists.txt           # Build configuration
├── README.md               # This documentation
├── build/                  # Build output directory
├── include/                # Header files
│   ├── Alert.h            # Alert model and visibility logic
│   ├── AlertManager.h     # Admin operations service
│   ├── Analytics.h        # Metrics tracking (expanded)
│   ├── Common.h           # Enums and utilities
│   ├── NotificationDelivery.h  # Delivery tracking
│   ├── Team.h             # Team model
│   ├── User.h             # User model
│   └── UserAlertPreference.h  # User preferences
├── src/                    # Implementation files
│   ├── Alert.cpp
│   ├── AlertManager.cpp
│   ├── Common.cpp
│   ├── NotificationDelivery.cpp
│   ├── Team.cpp
│   ├── User.cpp
│   ├── UserAlertPreference.cpp
│   ├── main-new.cpp       # can be removed 
│   └── main.cpp           # since CMake builds the application from main.cpp
└── .vscode/               # IDE configuration
    └── c_cpp_properties.json
```

### Key Design Patterns
- **Strategy Pattern**: Ready for Email/SMS push notification channels
- **Observer Pattern**: Foundation for real-time alert subscriptions
- **State Pattern**: Snooze/read/unread state management
- **Repository Pattern**: Clean data access abstraction

### Extensibility Points
- **Notification Channels**: Add new delivery methods in `NotificationChannel`
- **Visibility Rules**: Extend `Audience` class for custom targeting
- **Reminder Schedulers**: Enhance `ReminderScheduler` with cron expressions
- **Data Storage**: Integrate JSON persistence with existing framework

##  Troubleshooting

### Build Issues

**CMake Errors:**
```bash
# Clean and retry
rm -rf build/
mkdir build && cd build
cmake ..
cmake --build .
```

**Compiler Not Found:**
- Ensure GCC/MinGW is installed and in PATH
- On Windows, verify MinGW-w64 installation
- Check CMake version: `cmake --version`

**Missing Headers:**
- IntelliSense errors are cosmetic
- Build will succeed if CMake completes
- Reload VS Code window to refresh

### Runtime Issues

**Application Won't Start:**
- Ensure executable has permissions
- On Windows, run as administrator if needed
- Check for missing dynamic libraries

**Display Garbled Text:**
- Use terminal/console that supports UTF-8
- On Windows, use Windows Terminal or PowerShell
- Application uses clean ASCII output

**Menu Not Appearing:**
- Exit any running instances first
- Check console encoding settings
- Restart from build directory

##  Performance & Scalability

- **Memory Efficient**: Smart pointers prevent memory leaks
- **Modular Architecture**: Easy to extend for larger scale
- **Thread-Safe Design**: Ready for concurrent operations
- **JSON Serialization**: Ready for API integrations

##  Contributing

1. Fork the project
2. Create feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open Pull Request



**Built with C++17 • CMake • Cross-platform compatible**
