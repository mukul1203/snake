# Snake Game on Your Terminal

<img src="https://github.com/user-attachments/assets/5d5bdf64-8b3b-4655-9d23-f6232354f579" width="300" alt="Snake Game">

### Step 0: Clone the repository

Run the following command to clone the repository:

```bash
git clone --recursive <url_of_repo> 
```
This will clone the git submodules as well recursively.
However, if you open the repo in github codespaces, you will need to run
```bash
git submodule update --init --recursive
```
to pull the submodules after the fact.

### Step 1: Update Your System

Run the following command to update your system:

```bash
sudo apt update
```

### Step 2: Install Boost Libraries

To install all Boost libraries, run:

```bash
sudo apt install libboost-all-dev
```

### Step 3: Build the Snake Game

1. Create a build directory and navigate into it:

   ```bash
   mkdir build && cd build
   ```

2. Generate the makefile using CMake:

   ```bash
   cmake ..
   ```

3. Build the project:

   ```bash
   make
   ```

4. Run the Snake game:

   ```bash
   ./snake
   ```

5. To debug:
    Install cmake and cmake tools extensions. Then under the extension panel, you will find option to Debug (play button next to it). Just hit it and choose the target snake. Your breakpoints will start hitting.
---


# Emscripten Setup (not yet working)

### Step 1: Install Dependencies

Emscripten requires development tools and Python. Install them by running:

```bash
sudo apt-get update
sudo apt-get install build-essential cmake python3
```

### Step 2: Download and Install Emscripten

Clone the Emscripten SDK repository:

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
```

### Step 3: Install and Activate Emscripten

1. Fetch the latest version of the Emscripten SDK:

   ```bash
   ./emsdk install latest
   ```

2. Activate the latest SDK tools in the current terminal session:

   ```bash
   ./emsdk activate latest
   ```

3. Activate Emscripten for the current terminal session:

   ```bash
   source ./emsdk_env.sh
   ```
