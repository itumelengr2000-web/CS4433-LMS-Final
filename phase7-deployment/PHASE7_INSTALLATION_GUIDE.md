# Phase 7 Installation and Deployment Guide

## 1. Deployment target

The Moderated Learning Management System is a local C++17 console application. It runs on one school computer or a Windows computer using WSL2 Ubuntu. The runtime does not require a web server, cloud service, or internet connection.

The deployment package contains:

- `src/` and `include/` source directories
- `schema.sql`
- `CMakeLists.txt`
- GoogleTest test sources
- OpenSSL and SQLite integration
- Build and user documentation

A local SQLite database is created at first startup. Database files must not be committed to Git because they can contain assessment and personal data.

## 2. Windows installation using WSL2 Ubuntu

### 2.1 Install or verify WSL2

Open PowerShell as Administrator and run:

```powershell
wsl --install
wsl --set-default-version 2
```

Restart Windows if requested. Open Ubuntu from the Start menu and create an Ubuntu username and password.

### 2.2 Install development dependencies

Inside Ubuntu, run:

```bash
sudo apt update
sudo apt install -y build-essential cmake ninja-build sqlite3 libsqlite3-dev \
  libssl-dev libgtest-dev cppcheck gcovr git
```

Verify the tools:

```bash
c++ --version
cmake --version
ninja --version
sqlite3 --version
openssl version
cppcheck --version
git --version
```

The compiler must support C++17.

## 3. Obtain the project

### Option A: Clone from GitHub

```bash
mkdir -p ~/projects
cd ~/projects
git clone https://github.com/itumelengr2000-web/CS4433-LMS-Phase4.git lms-phase4
cd lms-phase4
```

### Option B: Copy an extracted archive

Extract the project into:

```text
~/projects/lms-phase4
```

Then enter it:

```bash
cd ~/projects/lms-phase4
```

Always run the application from the project root because it loads `schema.sql` using a relative path.

## 4. Build and verify the deployment

Configure and build:

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Run the automated tests:

```bash
ctest --test-dir build --output-on-failure
```

A valid release installation should report:

```text
100% tests passed, 0 tests failed out of 37
```

## 5. Create the first database and administrator

Create a new database and initial administrator:

```bash
./build/lms_app school-lms.db --create-admin
```

Enter an administrator username and password when prompted. Password characters are intentionally hidden while typing. The password is stored as a salted PBKDF2-HMAC-SHA256 hash and is never stored as plaintext.

Start the application:

```bash
./build/lms_app school-lms.db
```

The same database filename must be supplied on every launch. If a different filename is used, SQLite will create a different database.

## 6. Backup and recovery

Stop the application with `Ctrl+C`, then copy the database while it is not running:

```bash
cp school-lms.db backups/school-lms-$(date +%Y%m%d-%H%M%S).db
```

Create the backup directory first if needed:

```bash
mkdir -p backups
```

To restore a backup:

```bash
cp backups/school-lms-YYYYMMDD-HHMMSS.db school-lms-restored.db
./build/lms_app school-lms-restored.db
```

Never commit the database or backups to Git. Check with:

```bash
git ls-files '*.db' '*.db-wal' '*.db-shm'
```

The command should produce no output.

## 7. Troubleshooting

### `Cannot open schema.sql`

Run the application from the project root:

```bash
cd ~/projects/lms-phase4
./build/lms_app school-lms.db
```

### Login says the password is incorrect

Confirm that the same database file is being used, including exact username capitalisation:

```bash
ls -lh *.db
./build/lms_app school-lms.db
```

Password input is invisible by design. Type the password and press Enter.

### `no such table`

The command was probably run against a new empty database or before the LMS initialised the schema. Use the database filename passed to the application and start the LMS once from the project root.

### Build errors

Reconfigure from a clean build directory:

```bash
rm -rf build
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## 8. Deployment acceptance checklist

- [ ] WSL2/Ubuntu or supported Linux system installed.
- [ ] C++17 compiler, CMake, Ninja, SQLite, OpenSSL and Git available.
- [ ] Repository cloned or extracted.
- [ ] Release build completed.
- [ ] 37 automated tests passed.
- [ ] First administrator created.
- [ ] Database backup procedure tested.
- [ ] Database file excluded from Git.
- [ ] Login and all four role dashboards tested.
