cmake_minimum_required(VERSION 3.14) # Catch2 requires at least 3.10+
project(FiguresProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Define your source files (Excluding main.cpp) ---
set(SOURCE_FILES
        Figures.cpp
        Figures.h
        AbstractFactory.cpp
        AbstractFactory.h
        figure_factory.cpp
        figure_factory.h
        string_to_figure.cpp
        string_to_figure.h
)

# --- 2. Your Main Application ---
add_executable(run_app main.cpp ${SOURCE_FILES})

# --- 3. Pull in Catch2 (Modern FetchContent) ---
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2 # Use a specific tag for reproducibility
)
FetchContent_MakeAvailable(Catch2)

# --- 4. The Test Executable ---
add_executable(run_tests test.cpp ${SOURCE_FILES})

# Link Catch2. "Catch2WithMain" provides a default main(), so you don't have to write one.
target_link_libraries(run_tests PRIVATE Catch2::Catch2WithMain)

# Enable CTest (Optional, allows running tests via `ctest` command)
include(CTest)
include(Catch)
catch_discover_tests(run_tests)