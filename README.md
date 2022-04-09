# Connect-4 The Game

## Demo

![Connect4Demo](https://user-images.githubusercontent.com/44625252/162564921-b8d80428-7bd8-446b-8e78-0ffb9b9520d4.gif)

## Clone this project along with submodules
$ git clone --recursive https://github.com/rupamdebnath/Connect4.git

## Go to project root
$ cd Connect4-Clone

## Pull SFML as submodule (if you cloned without --recursive flag)
$ git submodule update --init

## Create a folder for build
$ mkdir build

## Go to build folder
$ cd build

## Generate project files
$ cmake ..

## This will generate project files using default cmake generator for your platform. For example:
On Windows with Visual Studio installed, it will generate a .sln
On Linux with make installed, it will generate a Makefile
On Mac with xcode installed, it will generate a .xcodeproj

## If you are using gitBash or any terminal on Windows then run this next

$ cmake --build .

### Finally run the executable using Visual studio .sln file or directly from bin\Debug folder and double clicking (run) the .exe file

