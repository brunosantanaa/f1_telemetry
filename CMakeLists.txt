cmake_minimum_required(VERSION 3.10)
project(f1_telemetry C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add source directory
add_subdirectory(src)

# Enable testing
enable_testing()
