# Launch Break

A timer app for the Novation Launchpad X, designed for work breaks.

## Usage

Windows only for now.

Run from root (commands using a bash terminal emulator [cmder](https://cmder.net/)):

```bash
# Create build folder
mkdir build
cd build

# Generate files
cmake ..

# Build
cmake --build .
```

```bash
# Running
./Debug/launch-break.exe <long timer (mins)> <short timer (mins)> <long break (mins)> <short break (secs)>
```
