cmake_minimum_required(VERSION 3.0)
project(Sprouthon)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(Sprouthon src/main.cpp src/scoreboard.cpp src/python.cpp src/grid.cpp src/game.cpp src/apple.cpp)

# Link SFML
target_link_libraries(Sprouthon sfml-graphics sfml-window sfml-system)