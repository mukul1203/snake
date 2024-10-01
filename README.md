# snake
Play the snake game on your terminal


sudo apt update

sudo apt install libboost-all-dev

mkdir build && cd build
cmake ..
make

./snake


# To install emsdk and finally emcmake:

Install Dependencies: Emscripten requires some common development tools and Python. Run the following to install them:

sudo apt-get update
sudo apt-get install build-essential cmake python3

Download and Install Emscripten: Download the Emscripten SDK by cloning its Git repository:

git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

Install and Activate Emscripten: After cloning, use the following commands to install and activate Emscripten:

## Fetch the latest version of the Emscripten SDK
./emsdk install latest

## Activate the latest SDK tools in the current terminal session
./emsdk activate latest

## Activate Emscripten for the current terminal session
source ./emsdk_env.sh
