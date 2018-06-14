cmake_minimum_required(VERSION 3.9)
project(untitled C)

set(CMAKE_C_STANDARD 99)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

add_executable(LunarRover main.c)
add_executable(GTKButtonDemo GTXDemos/GTKButtonDemo.c)
add_executable(MenuBarDemo GTXDemos/MenuBarDemo.c)
add_executable(RoverGUI GTXDemos/RoverControlGUIFrame.c)

# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(GTKButtonDemo ${GTK3_LIBRARIES})
TARGET_LINK_LIBRARIES(MenuBarDemo ${GTK3_LIBRARIES})
TARGET_LINK_LIBRARIES(RoverGUI ${GTK3_LIBRARIES})